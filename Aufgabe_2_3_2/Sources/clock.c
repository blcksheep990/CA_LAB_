#include <hidef.h>                              // Common defines

// Global variables
struct time_t{
    char hour;
    char minute;
    char second;
} time;

enum clockMode_t {NORMAL, SET};
enum clockMode_t clockMode = NORMAL;

// Prototypes and wrapper functions for LEDs
void toggleLED(void);

void toggleLED_Wrapper(unsigned char ledmask)
{
    asm
    {
        LDAB ledmask
        JSR toggleLED
    }
}

// Prototypes and wrapper functions for decToASCII

void decToASCII(void);

void decToASCII_Wrapper(char * pOutString, unsigned short value){
    asm{
        LDX pOutString
        LDD value
        JSR decToASCII
    }
}

// Prototypes and wrapper functions for writeLine
void writeLine(void);

void writeLine_Wrapper(char *text, char line)
{   asm
    {	
        LDX  text
        LDAB line
        JSR  writeLine
    }
}

// Prototypes of LED
void initLED(void);

// clock help functions

void timeToString(char * outputTimeString){
    char temp[7];
    decToASCII_Wrapper(temp, time.hour);
    outputTimeString[0] = temp[4];
    outputTimeString[1] = temp[5];
    outputTimeString[2] = ':';
    decToASCII_Wrapper(temp, time.minute);
    outputTimeString[3] = temp[4];
    outputTimeString[4] = temp[5];
    outputTimeString[5] = ':';
    decToASCII_Wrapper(temp, time.second);
    outputTimeString[6] = temp[4];
    outputTimeString[7] = temp[5];
    outputTimeString[8] = 0;
}

void increaseHour(){
    if(time.hour == 23){
        time.hour = 0;
    } else {
        time.hour++;
    }
}

void increaseMinute(){
    if(time.minute == 59){
        time.minute = 0;
        increaseHour();
    } else {
        time.minute++;
    }
}

void increaseSecond(){
    if(time.second == 59){
        time.second = 0;
        increaseMinute();
    } else {
        time.second++;
    }
}

void toggleClockMode(void){
    if (clockMode == NORMAL){
        clockMode = SET;
    } else {
        clockMode = NORMAL;
    }
    toggleLED_Wrapper(0x80);
}

// clock core functions

void initClock(){
    time.hour = 11;
    time.minute = 59;
    time.second = 30;
    initLED();
}

void tickClock(){
    char timeString[9];

    if(PTH & 0x04) toggleClockMode();
    if (clockMode == NORMAL){
        increaseSecond();
        toggleLED_Wrapper(0x1);
    } else {
        if(PTH & 0x08) increaseHour();
        if(PTH & 0x10) increaseMinute();
        if(PTH & 0x20) increaseSecond();
    }

    timeToString(timeString);
    writeLine_Wrapper(timeString, 1);
}