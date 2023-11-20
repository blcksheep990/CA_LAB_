/*  Lab 2 - Main C file for Clock program

    Computerarchitektur 3
    (C) 2018 J. Friedrich, W. Zimmermann
    Hochschule Esslingen

    Author:  W.Zimmermann, July 19, 2017
*/

#include <hidef.h>                              // Common defines
#include <mc9s12dp256.h>                        // CPU specific defines
#include "clock.c"
#include "thermometer.c"

#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"


// PLEASE NOTE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:
// Files lcd.asm and ticker.asm do contain SOFTWARE BUGS. Please overwrite them
// with the lcd.asm file, which you bug fixed in lab 1, and with file ticker.asm
// which you bug fixed in prep task 2.1 of this lab 2.
//
// To use decToASCII you must insert file decToASCII from the first lab into
// this project
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


// ****************************************************************************
// Function prototype(s)
// Note: Only void Fcn(void) assembler functions can be called from C directly.
//       For non-void functions a C wrapper function is required.
void initTicker(void);

// Prototypes and wrapper functions for LCD driver (from lab 1)
void initLCD(void);

// ****************************************************************************
// Global variables
unsigned char clockEvent = 0;
unsigned char count = 19;

// ****************************************************************************
void main(void) 
{   EnableInterrupts;                           // Global interrupt enable

    initLCD();                    	        	// Initialize the LCD
    initClock();
    initThermo();
    initTicker();                               // Initialize the time ticker

    for(;;)                                     // Endless loop
    {   
        if (clockEvent){
            clockEvent = 0;
            tickClock();
            updateThermo();

            if (count == 19){
                writeLine_Wrapper("F.Fink T.Mencin ", 0);
                count = 0;
            } else {
                count++;
            }
            if (count == 10){
                writeLine_Wrapper("C IT WS2023/2024", 0);
            }

            writeLine_Wrapper(outputString, 1);
    	}
    }
}
