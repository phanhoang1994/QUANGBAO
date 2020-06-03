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
  int BuffTime[7];
  String str = "";
  //debug thoi gian thuc
  if(Serial.available()){
    for(i=0;i<7;i++){BuffTime[i] = Serial.read();}
    while(Serial.available()){Serial.read();}
    if((BuffTime[0]=='S')&&(BuffTime[1]=='E')&&(BuffTime[2]=='T')){b_gSetTime=1;}
   }
  //Write RTC
  if(b_gSetTime){SetRTC(13,18,0,3,6,2020);b_gSetTime=0;}
  //Read RTC
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
      Serial.print(stringData[i]);
      Serial.print('-');
      have_data = 0;
     }
     Serial.println();
  }
}
