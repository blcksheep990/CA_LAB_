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


// Public interface function: timeToString
// Description: Converts the current time into a formatted string for display.
//             The resulting string represents the hour, minute, and second, and
//             optionally includes an AM/PM indicator if SELECT12HOURS is defined.

// Parameters: None

// Return: None

// Registers: Unchanged (when function returns)
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

// Public interface function: toggle_AM_PM
// Description: Toggles between AM and PM in a time representation.
//              If the current time representation is AM, it will be changed to PM,
//              and vice versa.

// Parameters: None

// Return: None

// Registers: am_or_pm register modified

void toggle_AM_PM(){
    if(am_or_pm == AM){
	am_or_pm = PM;
    } else {
	am_or_pm = AM;
    }
}

// Public interface function: increaseHour
// Description: Increases the hour value of the current time.
//              If SELECT12HOURS is defined, it also handles the toggle
//              between AM and PM when reaching 12 o'clock.

// Parameters: None

// Return: None

// Registers: time register modified

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

// Public interface function: increaseMinute
// Description: Increases the minute value of the current time.
//              If the minute reaches 59, it resets to 0 and increments the hour.

// Parameters: None

// Return: None

// Registers: time register modified

void increaseMinute(){
    if(time.minute == 59){
        time.minute = 0;
        increaseHour();
    } else {
        time.minute++;
    }
}

// Public interface function: increaseSecond
// Description: Increases the second value of the current time.
//              If the second reaches 59, it resets to 0 and increments the minute.

// Parameters: None

// Return: None

// Registers: time register modified

void increaseSecond(){
    if(time.second == 59){
        time.second = 0;
        increaseMinute();
    } else {
        time.second++;
    }
}

// Public interface function: toggleClockMode
// Description: Toggles between NORMAL and SET clock modes.
//              If the current clock mode is NORMAL, it switches to SET mode,
//              and vice versa. Additionally, it toggles an LED using the
//              toggleLED_Wrapper function.

// Parameters: None

// Return: None

// Registers: clockMode register modified

void toggleClockMode(void){
    if (clockMode == NORMAL){
        clockMode = SET;
    } else {
        clockMode = NORMAL;
    }
    toggleLED_Wrapper(0x80);
}

// clock core functions


// Public interface function: initClock
// Description: Initializes the clock with default values.
//              Sets the initial time to 11:59:30 PM and initializes
//              an LED using the initLED function.

// Parameters: None

// Return: None

// Registers: time and am_or_pm registers modified

void initClock(){
    time.hour = 11;
    time.minute = 59;
    time.second = 30;
    am_or_pm = PM;
    initLED();
}

// Public interface function: tickClock
// Description: Updates the clock based on button inputs and clock mode.
//              Toggles the clock mode if the first button is pressed.
//              In NORMAL mode, it increases the second, toggles an LED, 
//              and updates the time string.
//              In SET mode, it checks button inputs to adjust the hour, minute, and second.

// Parameters: None

// Return: None

// Registers: clockMode register modified, time register modified

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
