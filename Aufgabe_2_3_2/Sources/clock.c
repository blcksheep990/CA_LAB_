#include <hidef.h>                              // Common defines
#include "wrappers.h"

#define SELECT12HOURS

// Global variables
struct time_t{
    char hour;
    char minute;
    char second;
} time;

enum clockMode_t {NORMAL, SET};
enum clockMode_t clockMode = NORMAL;
enum am_or_pm_t {AM, PM} am_or_pm;

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
    #ifdef SELECT12HOURS
	if(am_or_pm == AM){
	    outputString[8] = 'a';
	} else {
	    outputString[8] = 'p';
	}
	outputString[9] = 'm';
    #endif
}

void toggle_AM_PM(){
    if(am_or_pm == AM){
	am_or_pm = PM;
    } else {
	am_or_pm = AM;
    }
}

void increaseHour(){
    #ifdef SELECT12HOURS
    if(time.hour == 11){
        toggle_AM_PM();
    }
    if(time.hour == 12){
	time.hour = 1;
    } else {
        time.hour++;
    }
    #else
    if(time.hour == 23){
        time.hour = 0;
    } else {
        time.hour++;
    }
    #endif
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
    am_or_pm = PM;
    initLED();
}

void tickClock(){
    if(~PTH & 0x01) toggleClockMode();
    if (clockMode == NORMAL){
        increaseSecond();
        toggleLED_Wrapper(0x1);
    } else {
        if(~PTH & 0x02) increaseHour();
        if(~PTH & 0x04) increaseMinute();
        if(~PTH & 0x08) increaseSecond();
    }

    timeToString();
}
