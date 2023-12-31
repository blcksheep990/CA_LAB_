/*  Radio signal clock - C Main Program

    Computerarchitektur 3
    (C) 2018 J. Friedrich, W. Zimmermann Hochschule Esslingen

    Author:   W.Zimmermann, Jun  10, 2016
    Modified: 

*/

#include <hidef.h>                              // Common defines
#include <mc9s12dp256.h>                        // CPU specific defines

#include "led.h"
#include "lcd.h"
#include "clock.h"
#include "dcf77.h"
#include "ticker.h"

#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"

// ****************************************************************************
// Public interface function: main
// 
// Description:
// Initializes various modules and enters an endless loop to handle events and update displays.
// Monitors a button on port H to toggle the timeZone variable.
// Processes clock events and updates the clock display.
// Processes DCF77 events and updates the date display.
// 
// Parameters:
// None
// 
// Return:
// None
// 
// Registers:
// Various registers may be modified based on function calls.

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Florian Fink Tim Mencin
void main(void)
{   EnableInterrupts;                           // Allow interrupts

    initLED();                                  // Initialize LEDs on port B
    initLCD();                                  // Initialize LCD display
    initClock();                                // Initialize Clock module
    initDCF77();                                // Initialize DCF77 module
    initTicker();                               // Initialize the time ticker
    DDRH &= 0x08;

    for(;;)                                     // Endless loop
    { 
        if (~PTH & 0x08){
            if (timeZone){
              timeZone = 0;
            } else {
              timeZone = 1;
            }
        }
        if (clockEvent != NOCLOCKEVENT)         // Process clock event
        {   processEventsClock(clockEvent);

            displayTimeClock();

            clockEvent=NOCLOCKEVENT;            // Reset clock event
        }

        if (dcf77Event != NODCF77EVENT)         // Process DCF77 events
        {   processEventsDCF77(dcf77Event);

            displayDateDcf77();

            dcf77Event = NODCF77EVENT;          // Reset dcf77 event
        }
    }
}



