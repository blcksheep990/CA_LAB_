#include <hidef.h>                              // Common defines
#include "wrappers.h"

// Global variables
struct time_t{
    char hour;
    char minute;
    char second;
} time;

enum clockMode_t {NORMAL, SET};
enum clockMode_t clockMode = NORMAL;

// clock help functions

void timeToString(){
    char temp[7];
    decToASCII_Wrapper(temp, time.hour);
    outputString[0] = temp[4];
    outputString[1] = temp[5];
    outputString[2] = ':';
    decToASCII_Wrapper(temp, time.minute);
    outputString[3] = temp[4];
    outputString[4] = temp[5];
    outputString[5] = ':';
    decToASCII_Wrapper(temp, time.second);
    outputString[6] = temp[4];
    outputString[7] = temp[5];
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
    if(PTH & 0x04) toggleClockMode();
    if (clockMode == NORMAL){
        increaseSecond();
        toggleLED_Wrapper(0x1);
    } else {
        if(PTH & 0x08) increaseHour();
        if(PTH & 0x10) increaseMinute();
        if(PTH & 0x20) increaseSecond();
    }

    timeToString();
}