/*
 PHAN VAN HOANG
 6/2020
*/ 

#ifndef DS1307RTC_h
#define DS1307RTC_h

#include "TimeLib.h"

void SetRTC(uint8_t _hour, uint8_t _minute, uint8_t _second, uint8_t _wday, uint8_t _day, uint8_t _month, uint8_t _year);
bool ReadRTC(void);

// library interface description
class DS1307RTC
{
  // user-accessible "public" interface
  public:
    DS1307RTC();
    static time_t get();
    static bool set(time_t t);
    static bool read(tmElements_t &tm);
    static bool write(tmElements_t &tm);
    static bool chipPresent() { return exists; }
    static unsigned char isRunning();
    static void setCalibration(char calValue);
    static char getCalibration();

  private:
    static bool exists;
    static uint8_t dec2bcd(uint8_t num);
    static uint8_t bcd2dec(uint8_t num);
};

#ifdef RTC
#undef RTC
#endif

extern DS1307RTC RTC;

#endif
 
