// Program to demonstrate the MD_Parola library
// - Optional use of DS1307 module for time and DHT11 sensor for temp and humidity
// - DHT11 library (DHT11) found at https://github.com/RobTillaart/Arduino
// - DS1307 library (MD_DS1307) found at https://github.com/MajicDesigns/DS1307
// NOTE: MD_MAX72xx library must be installed and configured for the LED
// matrix type being used. Refer documentation included in the MD_MAX72xx
// library or see this link:
// https://github.com/MajicDesigns/MD_Parola
// https://github.com/MajicDesigns/MD_MAX72XX

//https://www.youtube.com/channel/UCCC8DuqicBtP3A_aC53HYDQ/videos

// Use the DS1307 clock module
#define USE_DS1307 0
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "Font_Data.h"
#include <MD_DS1307.h>
#include <Wire.h>


// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

// HARDWARE SPI
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, 16);
// SOFTWARE SPI
//MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

#define SPEED_TIME  80
#define PAUSE_TIME  10
#define MAX_MESG  20

// Global variables
char szTime[9];    // mm:ss\0
char szData[20];  
char szMesg[MAX_MESG+1] = "";
char szsecond[4];    // ss


char *mon2str(uint8_t mon, char *psz, uint8_t len)
// Get a label from PROGMEM into a char array
{
  static const char str[][4] PROGMEM =
  {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };

  *psz = '\0';
  mon--;
  if (mon < 12)
  {
    strncpy_P(psz, str[mon], len);
    psz[len] = '\0';
  }

  return(psz);
}

char *dow2str(uint8_t code, char *psz, uint8_t len)
{
  static const char str[][10] PROGMEM =
  {
    "Sunday", "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday"
  };

  *psz = '\0';
  code--;
  if (code < 7)
  {
    strncpy_P(psz, str[code], len);
    psz[len] = '\0';
  }

  return(psz);
}
void getTime(char *psz, bool f = true)
// Code for reading clock time
{
  sprintf(psz, "%02d%c%02d", RTC.h, (f ? ':' : ' '), RTC.m);
}
void getsecond(char *psz)
// Code for reading clock date
{
  char  szBuf[10];
  sprintf(psz, "%02d", RTC.s);
}
void getDate(char *psz)
// Code for reading clock date
{
  char  szBuf[10];
  sprintf(psz, "%d %s %04d", RTC.dd, mon2str(RTC.mm, szBuf, sizeof(szBuf)-1), RTC.yyyy);
}
void setup(void)
{
// initialise the LED display
  P.begin(4);
  // Set up zones for 4 halves of the display
  // Each zone gets a different font, making up the top
  // and bottom half of each letter
  P.setZone(0, 0, 1);
  P.setZone(1, 2, 7);
  P.setZone(2, 10, 15);
  P.setZone(3, 8, 9);
  
      P.setFont(0, NULL);
      P.setFont(1, BigFontLower);
      P.setFont(2, BigFontUpper);
      P.setFont(3, NULL);
  P.displayZoneText(0, szsecond, PA_CENTER, SPEED_TIME, PAUSE_TIME, PA_PRINT, PA_NO_EFFECT);
  P.displayZoneText(1, szTime, PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  P.displayZoneText(2, szTime, PA_LEFT, SPEED_TIME, PAUSE_TIME, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  P.displayZoneText(3, szMesg, PA_CENTER, SPEED_TIME, PAUSE_TIME, PA_PRINT, PA_NO_EFFECT);
  RTC.control(DS1307_CLOCK_HALT, DS1307_OFF);
  RTC.control(DS1307_12H, DS1307_OFF);
  RTC.readTime();
}

void loop(void)
{
  static uint32_t lastTime = 0; // millis() memory
  static uint8_t  display = 0;  // current display mode
  static bool flasher = false;  // seconds passing flasher
  P.displayAnimate();
  if (P.getZoneStatus(3))
  {
    switch (display)
    {
      case 0: // day of week
        P.setTextEffect(3, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        for(int i=0;i<21;i++)
        {
          szMesg[i]='A'+i;
        }
        break;
    }
    P.displayReset(3);
  }
  
  if (P.getZoneStatus(1)){
    P.setTextEffect(1, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
    /*szData[0]='D';
    szData[1]='i';
    szData[2]='a';
    szData[3]='m';
    szData[4]='o';
    szData[5]='n';
    szData[6]='P';
    szData[7]='l';
    szData[8]='z';
    szData[9]='\0';*/
    P.displayReset(1);
  }
  if(P.getZoneStatus(2))
  {
    P.setTextEffect(2, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
    /*szData[0]='D';
    szData[1]='i';
    szData[2]='a';
    szData[3]='m';
    szData[4]='o';
    szData[5]='n';
    szData[6]='P';
    szData[7]='l';
    szData[8]='z';
    szData[9]='\0';*/
    P.displayReset(2);
  }

  // Finally, adjust the time string if we have to
  if (millis() - lastTime >= 1000)
  {
    RTC.readTime();
    lastTime = millis();
    getsecond(szsecond);
    flasher = !flasher;
    P.displayReset(0);
  }
 }
