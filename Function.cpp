#include <Arduino.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include "Global.h"
#include "Function.h"

extern unsigned char ucUARTBufferBlRx[64];
extern unsigned char ucUARTBufferSccRx[2];//--> bo nho dem SCC
extern bool have_data;
extern char NameFloor[20];
                 
//Config bluetooth
const int BLUETOOTH_TX = 4;
const int BLUETOOTH_RX = 3;

SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);
void vConfigBluetooth(unsigned int baurate) {
  bluetooth.begin(baurate);
}

//read data from BLUTOOTH
void vReadDataBlutooth(void) {
  if (bluetooth.available()) {
    byte j = 0;
    while (bluetooth.available()) {
      ucUARTBufferBlRx[j++] = bluetooth.read();
    }
  }
}
//write eeprom
void writeEeprom(byte Floor, char *pData) {
  unsigned int Addr;
  char data = 0;
  Addr = ((Floor * MAX_MESG) - MAX_MESG) + AddStartEeprom;
  for (byte i = 0; i < MAX_MESG; i++) {
    data = *pData;
    EEPROM.write(Addr + i, data); //ghi vao vi dieu khien
    //eeprom.write_1_byte(Addr + i, data); //ghi vao 24c64
    pData++;
    delay(10);
  }
}
//read eeprom
void readEeprom(byte Floor) {
  unsigned int Addr;
  Addr = ((Floor * MAX_MESG) - MAX_MESG) + AddStartEeprom;
  for (byte i = 0; i < MAX_MESG; i++) {
    NameFloor[i] = EEPROM.read(Addr + i); //ghi vao vi dieu khien
    //NameFloor[i] = eeprom.read_1_byte(Addr + i); //ghi vao 24c64
    delay(10);
  }
}
