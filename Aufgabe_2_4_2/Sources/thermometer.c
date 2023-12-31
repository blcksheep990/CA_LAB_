#include <hidef.h>                              // Common defines
#include "wrappers.h"

// Public interface function: initThermo
// Description: Initializes the thermal sensor (analog-to-digital converter).
//              Configures the necessary control registers for the ATD module.

// Parameters: None

// Return: None

// Registers: ATD0CTL2, ATD0CTL3, ATD0CTL4 registers modified

void initThermo(){
    ATD0CTL2 = 0xC0;
    ATD0CTL3 = 0x80;
    ATD0CTL4 = 0x05;
}

// Public interface function: updateThermo
// Description: Updates the temperature reading from the thermal sensor.
//              Converts the temperature to ASCII characters and updates
//              the outputString with the temperature in degrees Celsius.

// Parameters: None

// Return: None

// Registers: ATD0CTL5, ATD0STAT0, ATD0DR0, temperature register modified
//            temp array register modified, outputString register modified

void updateThermo(){
    char temperature;
    char temp[9];

    ATD0CTL5 = 0x87;

    while (ATD0STAT0 & 0x80 == 0x00){}
    //ATD0DR0 = 1024;
    temperature = ATD0DR0 * 50 / 511 - 30;
    decToASCII_Wrapper(temp, temperature);
    if (temperature < 0){
        outputString[11] = '-';
    } else {
        outputString[11] = ' ';
    }
    outputString[12] = temp[4];
    if (outputString[12] == '0'){
        outputString[12] = ' ';
    }
    outputString[13] = temp[5];
    outputString[14] = 'o';
    outputString[15] = 'C';
    outputString[16] = 0;
}
