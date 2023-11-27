#ifndef writeLine_h
#define writeLine_h

#include <hidef.h>                              // Common defines

char outputString[] = "                ";

// Prototypes and wrapper functions for writeLine
void writeLine(void);

// Public interface function: writeLine_Wrapper
// Description: Wrapper function to call the writeLine function.
//              Takes a text pointer and a line number as parameters.

// Parameters:
//   text: Pointer to the text string
//   line: Line number

// Return: None

// Registers: X, B registers modified

void writeLine_Wrapper(char *text, char line)
{   asm
    {	
        LDX  text
        LDAB line
        JSR  writeLine
    }
}

// Prototypes and wrapper functions for LEDs
void toggleLED(void);

// Public interface function: toggleLED_Wrapper
// Description: Wrapper function to call the toggleLED function.
//              Takes an LED mask as a parameter.

// Parameters:
//   ledmask: LED mask value

// Return: None

// Registers: B register modified

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

// Public interface function: decToASCII_Wrapper
// Description: Wrapper function to call the decToASCII function.
//              Takes a pointer to the output string and an unsigned short value.

// Parameters:
//   pOutString: Pointer to the output string
//   value: Unsigned short value to convert

// Return: None

// Registers: X, D registers modified

void decToASCII_Wrapper(char * pOutString, unsigned short value){
    asm{
        LDX pOutString
        LDD value
        JSR decToASCII
    }
}

// Prototypes of LED
void initLED(void);


#endif