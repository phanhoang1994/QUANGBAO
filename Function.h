#ifndef _FUNCTION_h
#define _FUNCTION_h

typedef struct 
{
  unsigned char ucLed7Seg;
  unsigned char ucCode;
  bool bDataTypes; //0==>string//1==>number
  unsigned char (*pucBlock1)(void);
} xLookupTable;


void writeEeprom(byte Floor, char *pData);
void readEeprom(byte Floor);
void vReadDataBlutooth(void);
void vConfigBluetooth(unsigned int baurate);
bool vReadDataScc(void);
unsigned char ucScanData(void);
unsigned char ucScanStatus(void);
#endif 
