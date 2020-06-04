#include <Wire.h>
#include "Global.h"
#include "TimeLib.h"
#include "DS1307RTC.h"
#include "Blutooth.h"

bool b_gSetTime;
unsigned long preMillis;
extern tmElements_t tm;

void setup() {
  Serial.begin(9600);
  vConfigBlutooth(9600);
  delay(200);
}

void loop() {
  uint8_t i;
  byte BuffUpdateTime[24];
  byte _upHour,_upMinute,_upSecond,_upWday,_upDay,_upMonth,_upYear; 
  String str = "";
  char *p;

  //Update TimeData-----------
  //Format:"TIME:hhmmss/DATE:tddmmyy" 24byte 
  //01-23-45-6-78-910-1112
  //hh-mm-ss-t-dd-mm-yy
  if(strstr((char *)ucUART4BufferBlRx, "TIME:") != NULL){
   //hh
   BuffUpdateTime[0]=ucUART4BufferBlRx[5]-48;
   BuffUpdateTime[1]=ucUART4BufferBlRx[6]-48;
   //mm
   BuffUpdateTime[2]=ucUART4BufferBlRx[7]-48;
   BuffUpdateTime[3]=ucUART4BufferBlRx[8]-48;
   //ss
   BuffUpdateTime[4]=ucUART4BufferBlRx[9]-48;
   BuffUpdateTime[5]=ucUART4BufferBlRx[10]-48;
   //t
   BuffUpdateTime[6]=ucUART4BufferBlRx[17]-48;
   //dd
   BuffUpdateTime[7]=ucUART4BufferBlRx[18]-48;
   BuffUpdateTime[8]=ucUART4BufferBlRx[19]-48;
   //mm
   BuffUpdateTime[9]=ucUART4BufferBlRx[20]-48;
   BuffUpdateTime[10]=ucUART4BufferBlRx[21]-48;
   //yy
   BuffUpdateTime[11]=ucUART4BufferBlRx[22]-48;
   BuffUpdateTime[12]=ucUART4BufferBlRx[23]-48;
    /*decode*/
    _upHour   =  BuffUpdateTime[0]*10 + BuffUpdateTime[1];
    _upMinute =  BuffUpdateTime[2]*10 + BuffUpdateTime[3];
    _upSecond =  BuffUpdateTime[4]*10 + BuffUpdateTime[5];
    _upWday   =  BuffUpdateTime[6];if(_upWday>7){_upWday=1;}
    _upDay    =  BuffUpdateTime[7]*10 + BuffUpdateTime[8];
    _upMonth  =  BuffUpdateTime[9]*10 + BuffUpdateTime[10];
    _upYear   =  BuffUpdateTime[11]*10 + BuffUpdateTime[12];
    Serial.println("decode");
    Serial.print(_upHour);Serial.print('-');
    Serial.print(_upMinute);Serial.print('-');
    Serial.print(_upSecond);Serial.print('-');
    Serial.print(_upWday);Serial.print('-');
    Serial.print(_upDay);Serial.print('/');
    Serial.print(_upMonth);Serial.print('/');
    Serial.print(_upYear);Serial.print('/');
    Serial.println("end");
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
   //debug time
   Serial.print(tm.Hour);
   Serial.write(':');
   Serial.print(tm.Minute);
   Serial.write(':'); 
   Serial.print(tm.Second);
   Serial.println();
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
