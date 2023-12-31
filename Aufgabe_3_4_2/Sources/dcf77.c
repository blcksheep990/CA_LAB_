/*  Radio signal clock - DCF77 Module

    Computerarchitektur 3
    (C) 2018 J. Friedrich, W. Zimmermann Hochschule Esslingen

    Author:   W.Zimmermann, Jun  10, 2016
    Modified: -
*/

#include <hidef.h>                                      // Common defines
#include <mc9s12dp256.h>                                // CPU specific defines
#include <stdio.h>

#include "dcf77.h"
#include "led.h"
#include "clock.h"
#include "lcd.h"

// Global variable holding the last DCF77 event
DCF77EVENT dcf77Event = NODCF77EVENT;

// Global variable holding the last DCF77 signal
char currentSignal = 1;

// Global variable holding the time until the last negative edge
int lastNegEdgeTime = -1000;

// Global variable holding the 59 databits transmitted each minute
char dataBits[59];
char bitCount = 0;
enum {DATAINVALID, WAITFORPOSEDGE, WAITFORNEGEDGE} decoderState = DATAINVALID;

// Prototypes of functions simulation DCF77 signals, when testing without
// a DCF77 radio signal receiver
//void initializePortSim(void);                   // Use instead of initializePort() for testing
//char readPortSim(void);                         // Use instead of readPort() for testing

// ****************************************************************************
// Initalize the hardware port on which the DCF77 signal is connected as input
// Parameter:   -
// Returns:     -
void initializePort(void)
{
    DDRH = 0;
}

// ****************************************************************************
// Read the hardware port on which the DCF77 signal is connected as input
// Parameter:   -
// Returns:     0 if signal is Low, >0 if signal is High
char readPort(void)
{
    
    return PTH & 0x01;
}

// ****************************************************************************
//  Initialize DCF77 module
//  Called once before using the module
void initDCF77(void)
{   setClock((char) dcf77Hour, (char) dcf77Minute, 0);
    displayDateDcf77();

    initializePort();
}

// ****************************************************************************
// Display the date derived from the DCF77 signal on the LCD display, line 1
// Parameter:   -
// Returns:     -
void displayDateDcf77(void)
{   char datum[32];
    char weekday[4];
    switch(dcf77WeekDay) {
      case 1:
        sprintf(weekday, "%s", "Mon");
        break;
      case 2:
        sprintf(weekday, "%s", "Tue");
        break;
      case 3:
        sprintf(weekday, "%s", "Wed");
        break;
      case 4:
        sprintf(weekday, "%s", "Thu");
        break;
      case 5:
        sprintf(weekday, "%s", "Fri");
        break;
      case 6:
        sprintf(weekday, "%s", "Sat");
        break;
      case 7:
        sprintf(weekday, "%s", "Sun");
        break;
    }

    (void) sprintf(datum, "%s %02d.%02d.%04d", weekday, dcf77Day, dcf77Month, dcf77Year);
    writeLine(datum, 1);
}

// ****************************************************************************
//  Read and evaluate DCF77 signal and detect events
//  Must be called by user every 10ms
//  Parameter:  Current CPU time base in milliseconds
//  Returns:    DCF77 event, i.e. second pulse, 0 or 1 data bit or minute marker
DCF77EVENT sampleSignalDCF77(int currentTime)
{
    char temp[10] = {0};
    int T_Pulse, T_Low;
    char lastSignal = currentSignal;
    currentSignal = readPort();
    if (currentSignal) setLED(0x02);
    else clrLED(0x02); 
    if (currentSignal < lastSignal){ // negative edge
        T_Pulse = currentTime - lastNegEdgeTime;
        lastNegEdgeTime = currentTime;
        if (900 <= T_Pulse && T_Pulse <= 1100) return VALIDSECOND;
        if (1900 <= T_Pulse && T_Pulse <= 2100) return VALIDMINUTE;
        return INVALID;
    }
    if (currentSignal > lastSignal){ // positive edge
        T_Low = currentTime - lastNegEdgeTime;
        if (70 <= T_Low && T_Low <= 130) return VALIDZERO;
        if (170 <= T_Low && T_Low <= 230) return VALIDONE;
        return INVALID;
    }
    if (currentTime - lastNegEdgeTime > 2100) return INVALID;

    return NODCF77EVENT; // no change
}
//****************************************************************************
// Public interface function: processDataBits
// 
// Description:
// Processes the received data bits from the DCF77 module and extracts relevant information.
// Updates global variables dcf77Hour, dcf77Minute, dcf77Day, dcf77WeekDay, dcf77Month, dcf77Year.
// Sets the clock based on the extracted time information.
// 
// Parameters:
// None
// 
// Return:
// 0: Successful processing of data bits.
// 1: Error during processing, indicating invalid or inconsistent data.

char processDataBits(){
    if (!dataBits[20]) return 1;
    if ((dataBits[21] + dataBits[22] + dataBits[23] + dataBits[24] + dataBits[25] + dataBits[26] + dataBits[27] + dataBits[28]) % 2) return 1;
    if ((dataBits[29] + dataBits[30] + dataBits[31] + dataBits[32] + dataBits[33] + dataBits[34] + dataBits[35]) % 2) return 1;
    if ((dataBits[36] + dataBits[37] + dataBits[38] + dataBits[39] + dataBits[40] + dataBits[41] + dataBits[42] + dataBits[43] + \
         dataBits[44] + dataBits[45] + dataBits[46] + dataBits[47] + dataBits[48] + dataBits[49] + dataBits[50] + dataBits[51] + \
         dataBits[52] + dataBits[53] + dataBits[54] + dataBits[55] + dataBits[56] + dataBits[57] + dataBits[58]) % 2) return 1;
    dcf77Minute = dataBits[21] + 2 * dataBits[22] + 4 * dataBits[23] + 8 * dataBits[24] + 10 * dataBits[25] + 20 * dataBits[26] + 40 * dataBits[27];
    if (dcf77Minute > 59) return 1;
    dcf77Hour = dataBits[29] + 2 * dataBits[30] + 4 * dataBits[31] + 8 * dataBits[32] + 10 * dataBits[33] + 20 * dataBits[34];
    if (dcf77Hour > 23) return 1;
    setClock((char) dcf77Hour, (char) dcf77Minute, 0);
    dcf77Day = dataBits[36] + 2 * dataBits[37] + 4 * dataBits[38] + 8 * dataBits[39] + 10 * dataBits[40] + 20 * dataBits[41];
    if (dcf77Day > 31 || dcf77Day == 0) return 1;
    dcf77WeekDay = dataBits[42] + 2 * dataBits[43] + 4 * dataBits[44];
    dcf77Month = dataBits[45] + 2 * dataBits[46] + 4 * dataBits[47] + 8 * dataBits[48] + 10 * dataBits[49];
    if (dcf77Month > 12 || dcf77Month == 0) return 1;
    dcf77Year = 2000 + dataBits[50] + 2 * dataBits[51] + 4 * dataBits[52] + 8 * dataBits[53] + 10 * dataBits[54] + 20 * dataBits[55] + 40 * dataBits[56] + 80 * dataBits[57];
    return 0;
}

// ****************************************************************************
// Process the DCF77 events
// Contains the DCF77 state machine
// Parameter:   Result of sampleSignalDCF77 as parameter
// Returns:     -
void processEventsDCF77(DCF77EVENT event)
{
    switch(decoderState){
        case DATAINVALID:
            if(event == VALIDMINUTE){
                bitCount = 0;
                decoderState = WAITFORPOSEDGE;
            }
            break;
        case WAITFORPOSEDGE:
            if (event == VALIDONE){
                dataBits[bitCount] = 1;
                bitCount ++;
                decoderState = WAITFORNEGEDGE;
            } else if (event == VALIDZERO){
                dataBits[bitCount] = 0;
                bitCount ++;
                decoderState = WAITFORNEGEDGE;
            } else {
                decoderState = DATAINVALID;
                setLED(0x04);
                clrLED(0x08); 
            }
            break;
        case WAITFORNEGEDGE:
            if (event == VALIDSECOND && bitCount < 59){
                decoderState = WAITFORPOSEDGE;
            } else if (event == VALIDMINUTE && bitCount == 59){
                if (processDataBits()){
                    decoderState = DATAINVALID;
                    setLED(0x04);
                    clrLED(0x08); 
                } else {
                    bitCount = 0;
                    decoderState = WAITFORPOSEDGE;
                    clrLED(0x04);
                    setLED(0x08); 
                                       
                }
            } else {
                decoderState = DATAINVALID;
                setLED(0x04);
                clrLED(0x08); 
            }
            break;
    }
}

