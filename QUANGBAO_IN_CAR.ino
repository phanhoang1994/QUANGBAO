#include <Arduino.h>
//#include <avr/wdt.h>
#include <TimerOne.h>
#include "Global.h"
#include "TimeLib.h"
#include "DS1307RTC.h"
#include "Function.h"
//matrix
#include <MD_MAX72xx.h>
#include <MD_Parola.h>

//Khởi tạo kiểu quét led
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICE    40
#define MAX_ZONE      4

//Định nghĩa chân I/O
#define CS1_PIN    10

//Điều khiển chân truyền nhận RS485
const int DIR = 2;

//Biến đối tượng màn hình led
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS1_PIN, MAX_DEVICE); //2 hàng led, mỗi hàng 20 led

// Biến đối tượng thời gian thực
extern tmElements_t tm;
unsigned char _upHour, _upMinute, _upSecond, _upWday, _upDay, _upMonth, _upYear;

//Biến sử dụng trong ngắt timer1
volatile unsigned long ulTimer1s;
volatile unsigned long ulTimerInitLed = 200;

//Mảng chứa data mã kí tự của đối tượng màn hình led
char zoneInformationL[41]={};
char zoneInformationH[41]={};
char zoneFLARL[4] = {};
char zoneFLARH[4]={};
char Floor1To5[10] = {26, SPACE2, '1', SPACE2, '2', SPACE2, '3', SPACE2, '4', '\0'};
char Floor6To9[10]  = {'5', SPACE2, '6', SPACE2, '7', SPACE2, '8', SPACE2, '9', '\0'};
char Floor10To13[8] = {11, SPACE1, 12, SPACE1, 13, SPACE1, 14, '\0'};
unsigned char countScroll;
unsigned char g_ucScandLed = 0;

//Biến lưu thông tin đọc từ Eeprom
unsigned char NameFloor[MAX_MESG];
bool g_bEnableReadEeprom;

//Bộ nhớ đệm bluetooth and Giao tiếp buffer SCC210
unsigned char ucUARTBufferBlRx[64]; //--> bo nho dem bluetooth
unsigned char ucUARTBufferSccRx[2]; //--> bo nho dem SCC
bool have_data;                     //Scc gửi dữ liệu mới

//Biến thang máy
unsigned char g_ucLiftStatus;       //Trạng thái vận hành
unsigned char g_ucCurrentFloor;     //Tầng hiện tại
unsigned char g_ucDirection;        //Hướng chạy
unsigned char g_ucRunStop;          //Trạng thái chạy

//Bảng tra
const xLookupTable xCode[NUM_LEDCODE] =
{
  {0x3F, 0},  //G
  {0x06, 1},  //1
  {0x5B, 2},  //2
  {0x4F, 3},  //3
  {0x66, 4},  //4
  {0x6D, 5},  //5
  {0x7D, 6},  //6
  {0x07, 7},  //7
  {0x7F, 8},  //8
  {0x6F, 9},  //9
  {0xBF, 10},  //10
  {0x86, 11},  //11
  {0xDB, 12},  //12
  {0xCF, 13},  //13
  {0xE6, 14},  //14
  {0xED, 15},  //15
  {0x49, 16},//"Pr" ok
  {0x64, 17},//"Ins" ok
  {0x76, 18},//"Reset" ok
  {0x77, 19},//"Rescue" //ok 
  {0x79, 20},//"Error" //ok
  {0x3B, 21},//"Ovl" //new
  {0x4A, 22},//"Fire" //new
};
char* Mode4Strings[] = {
  "Safety Drive",   // PR
  "Out!Of!Service",  // INS
  "RESET",          // PARKING
  "RESCUE",         // UPS
  "Fault",          // ERROR
  "Over Load",      // OVELOAD
  "Fire!Operation" // FIRE
};

void vCreateHString(char *pH, const char *pL);
void vReadDataScc(void);
void vFloorUpdate(void);
void vArrowUpdate(void);

void setup() {
  
  //Cấu hình ngắt Timer1
  vConfigInterruptTimer();
  
  //Cấu hình nhận RS485 
  Serial.begin(9600, SERIAL_8E1);
  pinMode(DIR, OUTPUT);
  digitalWrite(DIR, LOW);;
  delay(30);

  //Cấu hình nhận Bluetooth
  vConfigBluetooth(9600);
  //Cấu hình màn hình led
  P.begin(MAX_ZONE);
        P.setZone(0, 0, 13);   
        P.setZone(1, 20, 33);  
        P.setZone(2, 14, 19);   
        P.setZone(3, 34, 39);  
        
        P.setFont(0, NULL);
        P.setFont(1, NULL);
        P.setFont(2, NULL);
        P.setFont(3, NULL);
        
        P.displayZoneText(0,zoneInformationL,PA_CENTER,1, 0, PA_PRINT, PA_NO_EFFECT);
        P.displayZoneText(1,zoneInformationH,PA_CENTER,1, 0, PA_PRINT, PA_NO_EFFECT);
        P.displayZoneText(2,zoneFLARL, PA_CENTER,14, 0, PA_PRINT, PA_NO_EFFECT);
        P.displayZoneText(3,zoneFLARH, PA_CENTER,14, 0, PA_PRINT, PA_NO_EFFECT);
        g_ucScandLed = 1;
}
//main
void loop() {
  //wdt_reset();
  //TASK1: CẬP NHẬT DỮ LIỆU TỪ MẠCH ĐỆM----------------------------------------------------------------------------------------------1*/
  if(g_ucScandLed == 2){vReadDataScc();}
  //nếu nhận đúng dữ liệu
  if(have_data == 1){
    byte k = 0;
    while ((ucUARTBufferSccRx[0] != xCode[k].ucLed7Seg) & (k < NUM_LEDCODE)) {
      k++; //Tra bảng
    }
    //Chế độ thang đang AUTO
    if (xCode[k].ucData < 16) {
      g_ucCurrentFloor = xCode[k].ucData;
      //Chọn chế độ hiển thị
      if ((g_ucLiftStatus == 4) && ((ucUARTBufferSccRx[1] & 0x40) == 0)) { //Nếu chuyển từ chế độ INS và thang đang dừng --> hiển thị thời gian
        g_ucLiftStatus = 1;
      }
      if ((g_ucLiftStatus == 4) && (ucUARTBufferSccRx[1] & 0x40)) { //Nếu ở chế độ INS và có lệnh chạy --> hiển thị chế độ chạy
        g_ucLiftStatus = 2;
      }
      if ((g_ucLiftStatus == 1) && (ucUARTBufferSccRx[1] & 0x40)) { //Nếu đang hiển thị thời gian và có lệnh run --> hiển thị chế độ chạy
        g_ucLiftStatus = 2;
      }
      if ((g_ucLiftStatus == 2) && ((ucUARTBufferSccRx[1] & 0x40) == 0)) { //Nếu đang ở chế độ chạy và sau đó thang dừng --> hiển thị thông tin
        g_bEnableReadEeprom = true;
        g_ucLiftStatus = 3;
      }
      if ((g_ucLiftStatus == 3) && (ucUARTBufferSccRx[1] & 0x40)) { //Nếu ở chế độ hiển thị và có lệnh chạy --> hiển thị chế độ chạy
        g_ucLiftStatus = 2;
      }
    }
    //Chế độ thang khác AUTO
    else {
      g_ucLiftStatus = 4;
      strcpy((char*)zoneInformationL, Mode4Strings[xCode[k].ucData - 16]);
    }
    //Chiều mũi tên
    if (ucUARTBufferSccRx[1] & 0x10) {
      g_ucDirection = UP; //LÊN
    }
    else if (ucUARTBufferSccRx[1] & 0x20) {
      g_ucDirection = DOWN; //XUỐNG
    }
    else{
      g_ucDirection = 0; //KHÔNG HIỂN THỊ
    }
    //Trạng thái chạy hoặc dừng
    if (ucUARTBufferSccRx[1] & 0x40) {
      g_ucRunStop = RUN; //CHẠY
    }
    else{
      g_ucRunStop = STOP;//DỪNG
    }   
    have_data = 0;
  }
  //TASK2: CẬP NHẬT MÃ KÍ TỰ CHO MÀN HÌNH--------------------------------------------------------------------------------------------2*/
  vArrowUpdate();
  vFloorUpdate();
  switch (g_ucLiftStatus)
  {
    case 1://Chế độ auto, thang đang dừng --> hiển thị tầng và thời gian
      {
        //Hiển thị thời gian
        if (ulTimer1s == 0) {
          ReadRTC();
          ulTimer1s = 1000; //
          zoneInformationL[0] = 'T';
          zoneInformationL[1] = 'i';
          zoneInformationL[2] = 'm';
          zoneInformationL[3] = 'e';
          zoneInformationL[4] = ':';
          zoneInformationL[5] = tm.Hour / 10 + 48;
          zoneInformationL[6] = tm.Hour % 10 + 48;
          zoneInformationL[8] = tm.Minute / 10 + 48;
          zoneInformationL[9] = tm.Minute % 10 + 48;
          zoneInformationL[10] = 0;
          if(zoneInformationL[7]== ' '){zoneInformationL[7] = ':';}
          else {zoneInformationL[7] = ' ' ;}
        }
        break;
      }
    case 2: //Chế độ auto, thang đang chạy --> hiển thị mũi tên và khoảng tầng
      {
        //Hiển thị khoảng tầng lúc đang chạy
        //Khoảng tầng từ 1 - 5
        if (g_ucCurrentFloor < 5) {
          for (byte i = 0; i < 10; i++) {
            zoneInformationL[i] = Floor1To5[i];
          }
          switch (g_ucCurrentFloor)
          {
            case 0: zoneInformationL[0] = 26; break;
            case 1: zoneInformationL[2] = g_ucCurrentFloor+1; break;
            case 2: zoneInformationL[4] = g_ucCurrentFloor+1; break;
            case 3: zoneInformationL[6] = g_ucCurrentFloor+1; break;
            case 4: zoneInformationL[8] = g_ucCurrentFloor+1; break;
            default : break;
          }
        }
        //Khoảng tầng từ 6- 9
        else if ((g_ucCurrentFloor >= 5) && (g_ucCurrentFloor < 10)) {
          for (byte i = 0; i < 10; i++) {
            zoneInformationL[i] = Floor6To9[i];
          }
          switch (g_ucCurrentFloor)
          {
            case 5: zoneInformationL[0] = g_ucCurrentFloor+1; break;
            case 6: zoneInformationL[2] = g_ucCurrentFloor+1; break;
            case 7: zoneInformationL[4] = g_ucCurrentFloor+1; break;
            case 8: zoneInformationL[6] = g_ucCurrentFloor+1; break;
            case 9: zoneInformationL[8] = g_ucCurrentFloor+1; break;
            default : break;
          }
        }
        //Khoảng tầng từ 10 trở lên
        else {
          for (byte i = 0; i < 8; i++) {
            zoneInformationL[i] = Floor10To13[i];
          }
          switch (g_ucCurrentFloor)
          {
            case 10: zoneInformationL[0] =  15; break;
            case 11: zoneInformationL[2] =  16; break;
            case 12: zoneInformationL[4] =  17; break;
            case 13: zoneInformationL[6] =  18; break;
          }
        }
        break;
      }
    case 3: //Thang vừa mới dừng --> Hiển thị tầng và thông tin tầng
      {
        //Đọc thông tin trong bộ nhớ
        if (g_bEnableReadEeprom == true) {
          for (byte j = 0; j < MAX_MESG; j++) {
            zoneInformationL[j] = ' '; //xoa bo nhớ đệm zone 1
          }
          readEeprom(g_ucCurrentFloor);
          for (byte i = 0; i < MAX_MESG; i++) {
            zoneInformationL[i] = NameFloor[i];
          }
          g_bEnableReadEeprom = false;
        }
        break;
      }
    case 4://hiển thị cho các chế độ khác auto
      {
        ;
        break;
      }
    default: {
        g_ucLiftStatus = 1;
        break;
      }
  }
  //TASK3: ĐỌC DỮ LIỆU TỪ BLUETOOTH--------------------------------------------------------------------------------------------------3*/
  vReadDataBlutooth();
  //TAS4: CẬP NHẬT THỜI GIAN THỰC----------------------------------------------------------------------------------------------------4*/
  //Frame: TIME:hhmmsstddmmyy //ví dụ: TIME:1005034040720 <=>10 giờ 05 phút 03 giây, thứ 4, ngày 04 tháng 07, năm 20
  if (strstr((char *)ucUARTBufferBlRx, "TIME:") != NULL) {
    _upHour   =  ((ucUARTBufferBlRx[5] - 48) * 10 + (ucUARTBufferBlRx[6] - 48));
    _upMinute =  ((ucUARTBufferBlRx[7] - 48) * 10 + (ucUARTBufferBlRx[8] - 48));
    _upSecond =  ((ucUARTBufferBlRx[9] - 48) * 10 + (ucUARTBufferBlRx[10] - 48));
    _upWday   =  (ucUARTBufferBlRx[11] - 48); if (_upWday > 7) {
      _upWday = 1;
    }
    _upDay    =  ((ucUARTBufferBlRx[12] - 48) * 10 + (ucUARTBufferBlRx[13] - 48));
    _upMonth  =  ((ucUARTBufferBlRx[14] - 48) * 10 + (ucUARTBufferBlRx[15] - 48));
    _upYear   =  ((ucUARTBufferBlRx[16] - 48) * 10 + (ucUARTBufferBlRx[17] - 48));
    SetRTC(_upHour, _upMinute, _upSecond, _upWday, _upDay, _upMonth, _upYear);
    for (byte i = 0; i < 64; i++) {
      ucUARTBufferBlRx[i] = 0;
    }
  }
  //TASK5: CẬP NHẬP TÊN TẦNG---------------------------------------------------------------------------------------------------------5*/
  //Frame: FLOORxx:data //xx là số tầng //data là thông tin tầng tối đa 40 kí tự
  if (strstr((char *)ucUARTBufferBlRx, "FLOOR") != NULL) {
    byte FloorNo = ((ucUARTBufferBlRx[5] - 48) * 10) + (ucUARTBufferBlRx[6] - 48);
    char BuftNameFloor[MAX_MESG];
    for (byte i = 0; i < MAX_MESG; i++) {
      BuftNameFloor[i] = ucUARTBufferBlRx[i + 8];
    }
    writeEeprom(FloorNo, BuftNameFloor);
    delay(20);
    readEeprom(FloorNo);
    for (byte i = 0; i < 64; i++) {
      ucUARTBufferBlRx[i] = 0; //delete buff bluetooth
    }
  }
//Scand led
 if(g_ucScandLed == 2){
  zoneInformationL[40] = '\0';
  zoneFLARL[3] = '\0';
  vCreateHString(zoneInformationH,zoneInformationL);
  vCreateHString(zoneFLARH,zoneFLARL);
  P.displayAnimate();
      //Zone1
      if(g_ucLiftStatus==3){
        if (P.getZoneStatus(0) || P.getZoneStatus(1)){
          P.setTextEffect(0, PA_SCROLL_LEFT, PA_SCROLL_LEFT); P.displayClear(0);
          P.setTextEffect(1, PA_SCROLL_LEFT, PA_SCROLL_LEFT); P.displayClear(1);
          P.displayReset(0);
          P.displayReset(1);
          P.synchZoneStart();
          if((g_ucLiftStatus==3)&&(countScroll++ >=1)) {countScroll = 0;g_ucLiftStatus = 1;}
        }
      }
      else{
          P.setTextEffect(0, PA_PRINT, PA_NO_EFFECT); 
          P.setTextEffect(1, PA_PRINT, PA_NO_EFFECT);
          P.displayReset(0);
          P.displayReset(1);
          countScroll = 0;
      }
      if(g_ucLiftStatus==2){
          if(g_ucDirection == UP){
            if ((P.getZoneStatus(2)) || (P.getZoneStatus(3))){
              P.setTextEffect(2, PA_SCROLL_UP, PA_SCROLL_UP);P.displayClear(2); 
              P.setTextEffect(3, PA_SCROLL_UP, PA_SCROLL_UP);P.displayClear(3);
              P.displayReset(2);
              P.displayReset(3);
            }
          }
          else{
            if ((P.getZoneStatus(2)) || (P.getZoneStatus(3))){
              P.setTextEffect(2, PA_SCROLL_DOWN, PA_SCROLL_DOWN); P.displayClear(2);
              P.setTextEffect(3, PA_SCROLL_DOWN, PA_SCROLL_DOWN); P.displayClear(3);
              P.displayReset(2);
              P.displayReset(3);
            }
          }
      }
      else {
        P.setTextEffect(2, PA_PRINT, PA_NO_EFFECT); 
        P.setTextEffect(3, PA_PRINT, PA_NO_EFFECT); 
        P.displayReset(2);
        P.displayReset(3);
      }
 }
/*end loop---------------------------------------------------------------------------------------------------------------------------------------------------END*/
}
/*end loop---------------------------------------------------------------------------------------------------------------------------------------------------END*/
//Hàm lấy nữa kí tự trên 
void vCreateHString(char *pH, char *pL)
{
  for(;*pL != '\0';pL++){*pH++ = *pL | 0x80;}
  *pH = '\0';
}

//Cấu hình ngắt timer 1ms
void vConfigInterruptTimer(void){
  Timer1.initialize(1000); 
  Timer1.attachInterrupt(vSysTickTimerExpired); // blinkLED to run every 0.1 seconds
}
//Chương trình ngắt
void vSysTickTimerExpired(void){
  if(ulTimer1s > 0){--ulTimer1s;}
  if(ulTimerInitLed > 0){--ulTimerInitLed;}
  
  //Scanled once when power on
  if((ulTimerInitLed==0)&&(g_ucScandLed==1)){
      zoneInformationL[40] = '\0';
      zoneFLARL[3] = '\0';
      vCreateHString(zoneInformationH,zoneInformationL);
      vCreateHString(zoneFLARH,zoneFLARL);
      P.displayAnimate();
      P.displayReset();
      g_ucScandLed = 2;
   }
 }
 //rs485
 void vReadDataScc(void){
  static unsigned char buff[8];
  unsigned char checksum,i;
  if(Serial.available()>=6){
    buff[0] = Serial.read();
    buff[1] = Serial.read();
    buff[2] = Serial.read();
    buff[3] = Serial.read();
    buff[4] = Serial.read();
    buff[5] = Serial.read();
    while(Serial.available()){Serial.read();}
    if((buff[0]==0x99)&&(buff[1]==0x01)&& (buff[2]==0x28)){
      checksum = 0;
      for(i=1;i<5;i++){checksum += buff[i];}
      if(checksum == buff[5]){
        have_data = true;
        ucUARTBufferSccRx[0]= buff[3];
        ucUARTBufferSccRx[1]= buff[4];
      }
    }
  }
}
//Arrow 
void vArrowUpdate(void){
  if(g_ucLiftStatus == 2){
    if(g_ucDirection == UP){zoneFLARL[0] = ASCII_UP_RUN;}
    else if(g_ucDirection == DOWN){zoneFLARL[0] = ASCII_DOWN_RUN;}
    else{zoneFLARL[0] = ASCII_HIDE_AR;}
  }
  else{
    if(g_ucDirection == UP){zoneFLARL[0] = ASCII_UP;}
    else if(g_ucDirection == DOWN){zoneFLARL[0] = ASCII_DOWN;}
    else{zoneFLARL[0] = ASCII_HIDE_AR;}
  }
}
//FloorUpdate
void vFloorUpdate(void){
  if((g_ucLiftStatus == 1)||(g_ucLiftStatus == 3)){
    if(g_ucCurrentFloor<10){
      zoneFLARL[1]= ASCII_HIDE_FL; //hang chuc
      zoneFLARL[2] = g_ucCurrentFloor % 10 + 48;//hang don vi
    }
    else{
      zoneFLARL[1] = g_ucCurrentFloor / 10 + 48; //hang chuc// hang don vi
      zoneFLARL[2] = g_ucCurrentFloor % 10 + 48;
    }
  }
  else if(g_ucLiftStatus == 2){
    zoneFLARL[1] = ASCII_HIDE_FL; //hang chuc
    zoneFLARL[2] = ASCII_HIDE_FL;//hang don vi
  }
  else{
    zoneFLARL[1] = ASCII_SYMBOL_STOP;//hang don vi
    zoneFLARL[2] = ASCII_HIDE_FL;//hang don vi
  }
}
