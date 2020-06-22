/*
 PHAN VAN HOANG
 6/2020
*/ 

#include <Wire.h>
#include "Global.h"
#include "DS1307RTC.h"
#define DS1307_CTRL_ID 0x68

//CAI DAT THOI GIAN
tmElements_t tm;
void SetRTC(uint8_t _hour, uint8_t _minute, uint8_t _second, uint8_t _wday, uint8_t _day, uint8_t _month, uint8_t _year){
  tm.Hour   =  _hour;
  tm.Minute =  _minute;
  tm.Second =  _second;
  tm.Wday   =  _wday;
  tm.Day    =  _day;
  tm.Month  =  _month;
  tm.Year   =  _year;
  RTC.write(tm);
}
//DOC THOI GIAN
//ReadTime
bool ReadRTC(void){
  if(RTC.read(tm)){
   return true;
  }
  else{
    return false; 
  }
}
//****************************************************************************************************************
DS1307RTC::DS1307RTC()
{
  Wire.begin();
}
  
// PUBLIC FUNCTIONS
time_t DS1307RTC::get()   // Aquire data from buffer and convert to time_t
{
  tmElements_t tm;
  if (read(tm) == false) return 0;
  return(makeTime(tm));
}

bool DS1307RTC::set(time_t t)
{
  tmElements_t tm;
  breakTime(t, tm);
  return write(tm); 
}

// Aquire data from the RTC chip in BCD format
bool DS1307RTC::read(tmElements_t &tm)
{
  uint8_t sec;
  Wire.beginTransmission(DS1307_CTRL_ID);
  Wire.write((uint8_t)0x00); 
  if (Wire.endTransmission() != 0) {
    exists = false;
    return false;
  }
  exists = true;
// request the 7 data fields   (secs, min, hr, dow, date, mth, yr)
  Wire.requestFrom(DS1307_CTRL_ID, tmNbrFields);
  if (Wire.available() < tmNbrFields) return false;
  sec = Wire.read();
  tm.Second = bcd2dec(sec & 0x7f);   
  tm.Minute = bcd2dec(Wire.read() & 0x7f );
  tm.Hour =   bcd2dec(Wire.read() & 0x3f);  // mask assumes 24hr clock
  tm.Wday = bcd2dec(Wire.read()& 0x07 );
  tm.Day = bcd2dec(Wire.read() &0x1f);
  tm.Month = bcd2dec(Wire.read() );
  tm.Year = y2kYearToTm((bcd2dec(Wire.read())));
  if (sec & 0x80) return false; // clock is halted
  return true;
}

bool DS1307RTC::write(tmElements_t &tm)
{
  Wire.beginTransmission(DS1307_CTRL_ID);
  Wire.write((uint8_t)0x00); // reset register pointer  
  Wire.write((uint8_t)0x80); // Stop the clock. The seconds will be written last
  Wire.write(dec2bcd(tm.Minute));
  Wire.write(dec2bcd(tm.Hour));      // sets 24 hour format
  Wire.write(dec2bcd(tm.Wday));   
  Wire.write(dec2bcd(tm.Day));
  Wire.write(dec2bcd(tm.Month));
  Wire.write(dec2bcd(tmYearToY2k(tm.Year))); 
  if (Wire.endTransmission() != 0) {
    exists = false;
    return false;
  }
  exists = true;

// Now go back and set the seconds, starting the clock back up as a side effect
  Wire.beginTransmission(DS1307_CTRL_ID);
  Wire.write((uint8_t)0x00); // reset register pointer  
  Wire.write(dec2bcd(tm.Second)); // write the seconds, with the stop bit clear to restart
  if (Wire.endTransmission() != 0) {
    exists = false;
    return false;
  }
  exists = true;
  return true;
}

/*unsigned char DS1307RTC::isRunning()
{
  Wire.beginTransmission(DS1307_CTRL_ID);
  Wire.write((uint8_t)0x00); 
  Wire.endTransmission();
  // Just fetch the seconds register and check the top bit
  Wire.requestFrom(DS1307_CTRL_ID, 1);
  return !(Wire.read() & 0x80);
}

void DS1307RTC::setCalibration(char calValue)
{
  unsigned char calReg = abs(calValue) & 0x1f;
  if (calValue >= 0) calReg |= 0x20; // S bit is positive to speed up the clock
  Wire.beginTransmission(DS1307_CTRL_ID);
  Wire.write((uint8_t)0x07); // Point to calibration register
  Wire.write(calReg);
  Wire.endTransmission();  
}

char DS1307RTC::getCalibration()
{
  Wire.beginTransmission(DS1307_CTRL_ID);
  Wire.write((uint8_t)0x07); 
  Wire.endTransmission();
  Wire.requestFrom(DS1307_CTRL_ID, 1);
  unsigned char calReg = Wire.read();
  char out = calReg & 0x1f;
  if (!(calReg & 0x20)) out = -out; // S bit clear means a negative value
  return out;
}*/

// PRIVATE FUNCTIONS

// Convert Decimal to Binary Coded Decimal (BCD)
uint8_t DS1307RTC::dec2bcd(uint8_t num)
{
  return ((num/10 * 16) + (num % 10));
}

// Convert Binary Coded Decimal (BCD) to Decimal
uint8_t DS1307RTC::bcd2dec(uint8_t num)
{
  return ((num/16 * 10) + (num % 16));
}

bool DS1307RTC::exists = false;

DS1307RTC RTC = DS1307RTC(); // create an instance for the user
