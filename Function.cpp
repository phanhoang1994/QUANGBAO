#include <Arduino.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include "Global.h"
#include "Function.h"


const xLookupTable xCode[20] =
{
  {0x3F, 0, 1, ucScanData},  //G
  {0x06, 1, 1, ucScanData},  //1
  {0x5B, 2, 1, ucScanData},  //2
  {0x4F, 3, 1, ucScanData},  //3
  {0x66, 4, 1, ucScanData},  //4
  {0x6D, 5, 1, ucScanData},  //5
  {0x7D, 6, 1, ucScanData},  //6
  {0x07, 7, 1, ucScanData},  //7
  {0x7F, 8, 1, ucScanData},  //8
  {0x6F, 9, 1, ucScanData},  //9
  {0xBF, 10, 1, ucScanData},  //10
  {0x86, 11, 1, ucScanData},  //11
  {0xDB, 12, 1, ucScanData},  //12
  {0xCF, 13, 1, ucScanData},  //13
  {0xE6, 14, 1, ucScanData},  //14
  {0x49, 15, 0, ucScanStatus},//"Stop"
  {0x64, 16, 0, ucScanStatus},//"Inspection"
  {0x76, 17, 0, ucScanStatus},//"Reset"
  {0x77, 18, 0, ucScanStatus},//"Rescue"
  {0x79, 19, 0, ucScanStatus},//"Error"
};

unsigned char ucUART4BufferBlRx[40];
unsigned char ucUART4BufferRx[6];
extern char NameFloor[15][20];

//Config bluetooth
const int BLUETOOTH_TX = A1;
const int BLUETOOTH_RX = A2;
SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);
void vConfigBluetooth(unsigned int baurate) {
  bluetooth.begin(baurate);
}
//read data from BLUTOOTH
void vReadDataBlutooth(void) {
  if (bluetooth.available()) {
    delay(5);
    byte i = 0;
    while (bluetooth.available()) {
      ucUART4BufferBlRx[i++] = bluetooth.read();
    }
  }
}
//read data from SCC Buffer
bool vReadDataScc(void) {
  unsigned char bcc;
  if (Serial.available() == 0) {
    return  false;
  }
  else {
    if ((Serial.read() == 'A')) {
      Serial.print("have");
      byte i = 1;
      while (Serial.available()) {
        ucUART4BufferRx[i++] = Serial.read();
      }
      bcc = 0;
      for (byte j = 1; j < 5; j++) {
        bcc += ucUART4BufferRx[j]; //checksum
      }
      if (bcc !=
          ucUART4BufferRx[5]) {
        return false;
      }
    }
  }
  return true;
}
//write eeprom
void writeEeprom(byte Floor, char *pData) {
  unsigned int Addr;
  char data = 0;
  Addr = ((Floor * MAX_MESG) - MAX_MESG) + AddStartEeprom;
  for (byte i = 0; i < MAX_MESG; i++) {
    data = *pData;
    EEPROM.write(Addr + i, data);
    pData++;
    delay(5);
  }
}
//read eeprom
void readEeprom(byte Floor) {
  unsigned int Addr;
  Addr = ((Floor * MAX_MESG) - MAX_MESG) + AddStartEeprom;
  for (byte i = 0; i < MAX_MESG; i++) {
    NameFloor[Floor][i] = EEPROM.read(Addr + i); delay(5);
  }
}
//
unsigned char ucScanData(void){
  return 1;
}
unsigned char ucScanStatus(void){
 return 1;
}
