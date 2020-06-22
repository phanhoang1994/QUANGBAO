/*
 PHAN VAN HOANG
 6/2020
*/     
#ifndef __GLOBAL_h
#define SPEED_TIME  20
#define PAUSE_TIME  0

#define MAX_FLOOR  15
#define MAX_MESG  20
#define AddStartEeprom 10

#define LC_NONE    0x00  // Khong hien thi     
#define LC_STOP   0x49  //0-Stop
#define LC_INS    0x64  //1-Inspection
#define LC_RESET  0x76  //2-Reset
#define LC_RESCUE 0x77  //3-Rescue
#define LC_ERROR  0x79  //4-Error
#define LC_B    0x7C  //5-B
#define LC_L    0x38  //6-L
#define LC_M    0x37  //7-M
#define LC_B1   0x0E  //8-B1
#define LC_B2   0x0F  //9-B2
#define LC_M1   0x10  //10-M1
#define LC_M2   0x11  //11-M2
#define LC_H1   0x12  //12-H1
#define LC_H2   0x13  //13-H2
#define LC_B3   0x14  //14-B3
#define LC_B4   0x15  //15-B4
#define LC_B5   0x16  //16-B5
#define LC_3A   0x17  //17-3A
#define LC_12A    0x18  //18-12A
#define LC_14A    0x19  //19-14A
#define LC_E0   0x1A  //20-E0
#define LC_E1   0x1B  //21-E1
#define LC_E2   0x1C  //22-E2
#define LC_E3   0x1D  //23-E3
#define LC_E4   0x1E  //24-E4
#define LC_E5   0x1F  //25-E5
#define LC_E6   0x20  //26-E6
#define LC_E7   0x21  //27-E7
#define LC_G    0x3F  //28-G
#define LC_1    0x06  //29-1
#define LC_2    0x5B  //30-2
#define LC_3    0x4F  //31-3
#define LC_4    0x66  //32-4
#define LC_5    0x6D  //33-5  
#define LC_6    0x7D  //34-6
#define LC_7    0x07  //35-7
#define LC_8    0x7F  //36-8
#define LC_9    0x6F  //37-9
#define LC_10   0xBF  //38-10
#define LC_11   0x86  //39-11
#define LC_12   0xDB  //40-12
#define LC_13   0xCF  //41-13
#define LC_14   0xE6  //42-14
#define LC_15   0xED  //43-15
#define LC_16   0xFD  //44-16
#define LC_17   0x87  //45-17
#define LC_18   0xff  //46-18
#define LC_19   0xEF  //47-19 
#define LC_20   0x22  //48-20
#define LC_21   0x23  //49-21
#define LC_22   0x24  //50-22
#define LC_23   0x25  //51-23
#define LC_24   0x26  //52-24
#define LC_25   0x27  //53-25
#define LC_26   0x28  //54-26
#define LC_27   0x29  //55-27
#define LC_28   0x2A  //56-28
#define LC_29   0x2B  //57-29
#define LC_30   0x2C  //58-30
#define LC_31   0x2D  //59-31
#define LC_32   0x2E  //60-32
#define LC_33   0x2F  //61-33
#define LC_34   0x30  //62-34
#define LC_35   0x31  //63-35
#define LC_36   0x32  //64-36
#define LC_37   0x33  //65-37
#define LC_38   0x34  //66-38
#define LC_39   0x35  //67-39 
#define LC_12B  0x36  //68-12B
#define LC_R    0x39  //69-R
#define LC_T    0x3A  //75-T
#define LC_B6   0x40  //70-B6
#define LC_B7   0x41  //71-B7
#define LC_M3   0x42  //72-M3
#define LC_GL   0x43  //73-GL                           
#define LC_3B   0x44  //74-3B
#define LC_14B    0x45  //75-14B
#define LC_H    0x3B
#define LC_4A   0x4A
#define LC_L4   0x47
#define LC_L5   0x48

const char strIns[] PROGMEM ="Inspection";  //kiem tra
const char strStop[] PROGMEM ="Stop";  //kiem tra
    

/*/debug time
Serial.print(tm.Hour);
Serial.write(':');
Serial.print(tm.Minute);
Serial.write(':'); 
Serial.print(tm.Second);
Serial.println();*/


#endif
