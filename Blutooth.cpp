/*
 PHAN VAN HOANG
 6/2020
*/ 
#include <Arduino.h> 
#include <SoftwareSerial.h>
#include "Blutooth.h"

const int BLUETOOTH_TX = A1;
const int BLUETOOTH_RX = A2;
SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);

char stringData[18];
bool have_data;

//Config BLUTOOTH 
void vConfigBlutooth(unsigned long BAUD_RATE){
  bluetooth.begin(BAUD_RATE);
}
//read data from BLUTOOTH
void vReadDataBlutooth(void){
 if(bluetooth.available()){
   delay(50);
   for (int i=0; i<18; i++){
    if(strstr((char *)g_ui8BuffRead, "TITLE") != NULL){
        
    }
    stringData[i] = bluetooth.read();
   }
   have_data = 1;
   while(bluetooth.available()){bluetooth.read();}
  } 
 }
