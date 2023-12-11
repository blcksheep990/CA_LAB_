/*  Header for DCF77 module

    Computerarchitektur 3
    (C) 2018 J. Friedrich, W. Zimmermann Hochschule Esslingen

    Author:   W.Zimmermann, Jun  10, 2016
    Modified: -
*/


// Data type for DCF77 signal events
typedef enum { NODCF77EVENT, VALIDZERO, VALIDONE, VALIDSECOND, VALIDMINUTE, INVALID } DCF77EVENT;

// Global variable holding the last DCF77 event
extern DCF77EVENT dcf77Event;

// Global variable holding time Zone "DE" = 0 and "US" = 1
extern char timeZone;

// Modul internal global variables
static int  dcf77Year=2017, dcf77Month=1, dcf77Day=1, dcf77Hour=0, dcf77Minute=0, dcf77WeekDay=1;       //dcf77 Date and time as integer values


// Public functions, for details see dcf77.c
void initDCF77(void);
void displayDateDcf77(void);
DCF77EVENT sampleSignalDCF77(int currentTime);
void processEventsDCF77(DCF77EVENT event);




