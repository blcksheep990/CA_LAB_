#ifndef writeLine_h
#define writeLine_h

#include <hidef.h>                              // Common defines

char outputString[] = "                ";

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

// Prototypes of LED
void initLED(void);


#endif