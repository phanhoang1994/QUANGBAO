#include <Wire.h>
#include "Global.h"
#include "TimeLib.h"
#include "DS1307RTC.h"
#include "Blutooth.h"
//matrix
#include <SPI.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include "Font_Data.h"

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

// HARDWARE SPI
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, 16);
// SOFTWARE SPI
//MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
char szTime[6]; //mm:ss\0
char szArrow[2];

bool b_gSetTime;
unsigned long preMillis;
unsigned long preMillis1;
extern tmElements_t tm;

void setup() {
  Serial.begin(9600);
  vConfigBlutooth(9600);
  delay(200);
  //matrix
  P.begin(4);
  P.setZone(0, 2, 7); //zone low for quang bao and time
  P.setZone(1, 10, 15);//zone high for quang qao and time
  P.setZone(2, 0, 1); //zone low for arrow
  P.setZone(3, 8, 9);//zone high for arrow
      P.setFont(0, BigFontLower);
      P.setFont(1, BigFontUpper);
      P.setFont(2, BigFontLower);
      P.setFont(3, BigFontUpper);
  P.displayZoneText(0,szTime, PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_PRINT,PA_NO_EFFECT);
  P.displayZoneText(1,szTime, PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_PRINT,PA_NO_EFFECT);
  P.displayZoneText(2,szArrow, PA_CENTER, SPEED_TIME, PAUSE_TIME, PA_PRINT,PA_NO_EFFECT);
  P.displayZoneText(3,szArrow, PA_CENTER, SPEED_TIME, PAUSE_TIME, PA_PRINT,PA_NO_EFFECT);
}

void loop() {
  uint8_t i;
  byte BuffUpdateTime[24];
  byte _upHour,_upMinute,_upSecond,_upWday,_upDay,_upMonth,_upYear; 
  String str = "";
  char *p;
  //Matrix 16x16
  P.displayAnimate();
  P.displayReset(0);
  P.displayReset(1);
  P.displayReset(2);
  P.displayReset(3);
  /*if (P.getZoneStatus(3)){
    P.setTextEffect(3, PA_SCROLL_UP, PA_SCROLL_UP);
    P.displayReset(3);
  }
  if (P.getZoneStatus(2)){
    P.setTextEffect(2, PA_SCROLL_UP, PA_SCROLL_UP);
    P.displayReset(2);
  }*/
  //Update TimeData-----------
  //Format:"TIME:hhmmss/DATE:tddmmyy" 24byte 
  //01-23-45-6-78-910-1112
  //hh-mm-ss-t-dd-mm-yy
  if(strstr((char *)ucUART4BufferBlRx, "TIME") != NULL){
   //hh
   BuffUpdateTime[0]=ucUART4BufferBlRx[4]-48;
   BuffUpdateTime[1]=ucUART4BufferBlRx[5]-48;
   //mm
   BuffUpdateTime[2]=ucUART4BufferBlRx[6]-48;
   BuffUpdateTime[3]=ucUART4BufferBlRx[7]-48;
   //ss
   BuffUpdateTime[4]=ucUART4BufferBlRx[8]-48;
   BuffUpdateTime[5]=ucUART4BufferBlRx[9]-48;
   //t
   BuffUpdateTime[6]=ucUART4BufferBlRx[10]-48;
   //dd
   BuffUpdateTime[7]=ucUART4BufferBlRx[11]-48;
   BuffUpdateTime[8]=ucUART4BufferBlRx[12]-48;
   //mm
   BuffUpdateTime[9]=ucUART4BufferBlRx[13]-48;
   BuffUpdateTime[10]=ucUART4BufferBlRx[14]-48;
   //yy
   BuffUpdateTime[11]=ucUART4BufferBlRx[15]-48;
   BuffUpdateTime[12]=ucUART4BufferBlRx[16]-48;
    /*decode*/
    _upHour   =  BuffUpdateTime[0]*10 + BuffUpdateTime[1];
    _upMinute =  BuffUpdateTime[2]*10 + BuffUpdateTime[3];
    _upSecond =  BuffUpdateTime[4]*10 + BuffUpdateTime[5];
    _upWday   =  BuffUpdateTime[6];if(_upWday>7){_upWday=1;}
    _upDay    =  BuffUpdateTime[7]*10 + BuffUpdateTime[8];
    _upMonth  =  BuffUpdateTime[9]*10 + BuffUpdateTime[10];
    _upYear   =  BuffUpdateTime[11]*10 + BuffUpdateTime[12];
    /*end decode*/
     b_gSetTime=1;
     for(i=0;i<64;i++){ucUART4BufferBlRx[i]=0;}
  }
   //Write RTC----------------
    if(b_gSetTime){
      SetRTC(_upHour,_upMinute,_upSecond,_upWday,_upDay,_upMonth,_upYear);
      b_gSetTime=0;
    }
   
  //Read RTC------------------
  if(millis() - preMillis>1000){
   ReadRTC();
   preMillis = millis();
   szTime[0]=tm.Hour/10+48;
   szTime[1]=tm.Hour%10+48;
   szTime[3]=tm.Minute/10+48;
   szTime[4]=tm.Minute%10+48;
   if(millis() - preMillis1>1000){szTime[2]=':';}
   if(millis() - preMillis1>2000){szTime[2]=' ';preMillis1=millis();}
   szTime[5]='\0';
   szArrow[0]=94;
   szArrow[1]='\0';
  }
  //Blutooth
  vReadDataBlutooth();
  if(have_data){
   for (int i=0; i<18; i++){
    Serial.print(ucUART4BufferBlRx[i]);
    Serial.print('-');
    have_data = 0;
   }
   Serial.println();
  }
}
