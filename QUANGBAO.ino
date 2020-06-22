
#include "Global.h"
#include "TimeLib.h"
#include "DS1307RTC.h"
#include "Function.h"
//matrix
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include "Font_Data.h"

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, 40);
//Bien toan cuc
extern tmElements_t tm;
unsigned long preMillis, preMillis1;
bool b_gSetTime;  //--> cho phep cai dat thoi gian
byte AddrEepromFloor; //--> dia chi bat dau cua moi tang
unsigned int g_ui8CallLift;//--> vi tri tang hien tai
extern unsigned char ucUART4BufferBlRx[40]; //--> bo nho dem bluetooth
extern unsigned char ucUART4BufferRx[6];
byte _upHour, _upMinute, _upSecond, _upWday, _upDay, _upMonth, _upYear;

//vung nho data hien thi len man hinh

unsigned char zoneDisplayFloor1[10] = {'1', '|', '2', '|', '3', '|', '4', '|', '5', '\0'};
unsigned char zoneDisplayFloor2[8] =  {'6', '|', '7', '|', '8', '|', '9', '\0'};
unsigned char zoneDisplayFloor3[8] =  {34 , '!', 35 , '!', 36 , '!', 37 , '\0'};
unsigned char Arrow_Floor[4];
unsigned char BuffDataDisplay[21]; // bo nho dem thong tin tang
unsigned char NameFloor[15][20]; //bang du lieu luu thong tin tang
byte mode_display;
byte Stop_floor;
byte countScroll;

//nguyen mau ham
void display(void);

void setup() {
  //DATA DEBUG
  mode_display = 1;
  Stop_floor = 1;
  //---------------------------------------------------------------------
  BuffDataDisplay[20] = '\0';
  Arrow_Floor[3] = '\0';
  Serial.begin(9600);
  vConfigBluetooth(9600);
  delay(50);
  //matrix
  P.begin(4);
  P.setZone(0, 0, 13); //name + time
  P.setZone(1, 20, 33); //name + time
  P.setZone(2, 14, 19); //floor
  P.setZone(3, 34, 39); //floor

  P.setFont(0, BigFontLower);
  P.setFont(1, BigFontUpper);
  P.setFont(2, BigFontLower);
  P.setFont(3, BigFontUpper);

  P.displayZoneText(0, (char*)BuffDataDisplay, PA_CENTER, 24, PAUSE_TIME, PA_PRINT, PA_NO_EFFECT);
  P.displayZoneText(1, (char*)BuffDataDisplay, PA_CENTER, 25, PAUSE_TIME, PA_PRINT, PA_NO_EFFECT);
  P.displayZoneText(2, (char*)Arrow_Floor, PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_PRINT, PA_NO_EFFECT);
  P.displayZoneText(3, (char*)Arrow_Floor, PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_PRINT, PA_NO_EFFECT);
  for (byte i = 0; i < MAX_FLOOR; i++) {
    readEeprom(i);
  }
}

void loop() {
  P.synchZoneStart();
  P.displayAnimate();
  if ((mode_display == 1) || (mode_display == 2)) {
    P.setTextEffect(0, PA_PRINT, PA_NO_EFFECT);
    P.setTextEffect(1, PA_PRINT, PA_NO_EFFECT);
    P.displayReset(0);
    P.displayReset(1);
  }
  else {
    if ((P.getZoneStatus(0)) || (P.getZoneStatus(1))) {
      P.setTextEffect(0, PA_SCROLL_LEFT, PA_SCROLL_LEFT); P.displayClear(0);
      P.setTextEffect(1, PA_SCROLL_LEFT, PA_SCROLL_LEFT); P.displayClear(1);
      P.displayReset(0);
      P.displayReset(1);
      if (countScroll++ >= 1) {
        countScroll = 0;
        mode_display = 1;
      }
    }
  }
  P.displayReset(2);
  P.displayReset(3);
  //0.READ DATA FROM SCC---------------------------------------------------------------------------------------------*/
  if (vReadDataScc() == true) {
  
  }
  /*1.UPDATE DISPLAY ZONE TIME AND INFOR FLOOR------------------------------------------------------------------------*/
  switch (mode_display)
  {
    case 1://time------------------------------------
      {
        BuffDataDisplay[0] = 'T';
        BuffDataDisplay[1] = 'i';
        BuffDataDisplay[2] = 'm';
        BuffDataDisplay[3] = 'e';
        BuffDataDisplay[4] = ':';
        BuffDataDisplay[5] = tm.Hour / 10 + 48;
        BuffDataDisplay[6] = tm.Hour % 10 + 48;
        if (millis() - preMillis1 > 1000) {
          BuffDataDisplay[7] = ':';
        }
        if (millis() - preMillis1 > 2000) {
          BuffDataDisplay[7] = ' ';
          preMillis1 = millis();
        }
        BuffDataDisplay[8] = tm.Minute / 10 + 48;
        BuffDataDisplay[9] = tm.Minute % 10 + 48;
        BuffDataDisplay[10] = 0;
        break;
      }
    case 2://status run------------------------------
      {
        if (Stop_floor < 6) {
          for (byte i = 0; i < 10; i++) {
            BuffDataDisplay[i] = zoneDisplayFloor1[i];
          }
          switch (Stop_floor)
          {
            case 1: BuffDataDisplay[0] = Stop_floor + 20; break;
            case 2: BuffDataDisplay[2] = Stop_floor + 20; break;
            case 3: BuffDataDisplay[4] = Stop_floor + 20; break;
            case 4: BuffDataDisplay[6] = Stop_floor + 20; break;
            case 5: BuffDataDisplay[8] = Stop_floor + 20; break;
          }
        }
        else if ((Stop_floor >= 6) && (Stop_floor < 10)) {
          for (byte i = 0; i < 8; i++) {
            BuffDataDisplay[i] = zoneDisplayFloor2[i];
          }
          switch (Stop_floor)
          {
            case 6: BuffDataDisplay[0] = Stop_floor + 20; break;
            case 7: BuffDataDisplay[2] = Stop_floor + 20; break;
            case 8: BuffDataDisplay[4] = Stop_floor + 20; break;
            case 9: BuffDataDisplay[6] = Stop_floor + 20; break;
          }
        }
        else {
          for (byte i = 0; i < 8; i++) {
            BuffDataDisplay[i] = zoneDisplayFloor3[i];
          }
          switch (Stop_floor)
          {
            case 10: BuffDataDisplay[0] =  38; break;
            case 11: BuffDataDisplay[2] =  39; break;
            case 12: BuffDataDisplay[4] =  40; break;
            case 13: BuffDataDisplay[6] =  41; break;
          }
        }
        break;
      }
    case 3://data------------------------------------
      {
        for (byte i = 0; i < MAX_MESG; i++) {
          BuffDataDisplay[i] = NameFloor[Stop_floor][i];
        }
        break;
      }
    default: {
        break;
      }
  }
  //2.READ DATA FROM BLUETOOTH---------------------------------------------------------------------------------------------*/
  vReadDataBlutooth();
  //3.WRITE RTC------------------------------------------------------------------------------------------------------------*/
  if (strstr((char *)ucUART4BufferBlRx, "TIME") != NULL) {
    _upHour   =  ((ucUART4BufferBlRx[4] - 48) * 10 + (ucUART4BufferBlRx[5] - 48));
    _upMinute =  ((ucUART4BufferBlRx[6] - 48) * 10 + (ucUART4BufferBlRx[7] - 48));
    _upSecond =  ((ucUART4BufferBlRx[8] - 48) * 10 + (ucUART4BufferBlRx[9] - 48));
    _upWday   =  (ucUART4BufferBlRx[10] - 48); if (_upWday > 7) {
      _upWday = 1;
    }
    _upDay    =  ((ucUART4BufferBlRx[11] - 48) * 10 + (ucUART4BufferBlRx[12] - 48));
    _upMonth  =  ((ucUART4BufferBlRx[13] - 48) * 10 + (ucUART4BufferBlRx[14] - 48));
    _upYear   =  ((ucUART4BufferBlRx[15] - 48) * 10 + (ucUART4BufferBlRx[16] - 48));
    b_gSetTime = 1;
    for (byte i = 0; i < 40; i++) {
      ucUART4BufferBlRx[i] = 0;
    }
  }
  if (b_gSetTime == 1) {
    SetRTC(_upHour, _upMinute, _upSecond, _upWday, _upDay, _upMonth, _upYear);
    b_gSetTime = 0;
  }

  //4.READ RTC----------------------------------------------------------------------------------------------------*/
  if (millis() - preMillis > 1000) {
    ReadRTC();
    preMillis = millis();
  }
  //5.UPDATE DATA FLOOR----------------------------------------------------------------------------------------------------*/
  if (strstr((char *)ucUART4BufferBlRx, "FLOOR") != NULL) {
    byte FloorNo = ((ucUART4BufferBlRx[5] - 48) * 10) + (ucUART4BufferBlRx[6] - 48);
    char BuftNameFloor[20];
    Serial.print(FloorNo, DEC);
    for (byte i = 0; i < MAX_MESG; i++) {
      BuftNameFloor[i] = ucUART4BufferBlRx[i + 8];
    }
    writeEeprom(FloorNo, BuftNameFloor);
    delay(20);
    readEeprom(FloorNo);
    for (byte i = 0; i < 40; i++) {
      ucUART4BufferBlRx[i] = 0; //delete buff bluetooth
    }
  }

  //6. DEBUG --------------------------------------------------------------------------------------------------------------*/
  if (strstr((char *)ucUART4BufferBlRx, "SET") != NULL) {
    if (strstr((char *)ucUART4BufferBlRx, "Call") != NULL) {
      Stop_floor = ((ucUART4BufferBlRx[8] - 48) * 10 + (ucUART4BufferBlRx[9] - 48));
    }
    else if (strstr((char *)ucUART4BufferBlRx, "RUNUP") != NULL) {
    }
    else if (strstr((char *)ucUART4BufferBlRx, "RUNDOW") != NULL) {
    }
    else if (strstr((char *)ucUART4BufferBlRx, "STOP") != NULL) {
    }
    else if (strstr((char *)ucUART4BufferBlRx, "MODE2") != NULL) {
      mode_display = 2;
    }
    else if (strstr((char *)ucUART4BufferBlRx, "MODE3") != NULL) {
      mode_display = 3;
    }
    for (byte i = 0; i < 40; i++) {
      ucUART4BufferBlRx[i] = 0;
    }
  }
  //end loop------------------------------------------------------------------------------------------------------------------
}
