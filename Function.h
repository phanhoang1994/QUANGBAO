#ifndef _FUNCTION_h
#define _FUNCTION_h

typedef struct 
{
  unsigned char ucLed7Seg;
  unsigned char ucData;
} xLookupTable;


void writeEeprom(byte Floor, char *pData);
void readEeprom(byte Floor);
void vReadDataBlutooth(void);
//void vReadDataScc(void);
void vConfigBluetooth(unsigned int baurate);
#endif 
