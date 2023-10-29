;
;   Labor 1 - Test program for LCD driver

;# Done by Tim and Florian

; Export symbols
        XDEF Entry, main

; Import symbols
        XREF __SEG_END_SSTACK                   ; End of stack
        XREF initLCD, writeLine, delay_10ms     ; LCD functions

; Include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; Defines

; RAM: Variable data section
.data:  SECTION

; ROM: Constant data
.const: SECTION
MSG1:   dc.b " Mach mal eine",0
MSG2:   dc.b " kleine Pause", 0
msgA: DC.B "ABCDEFGHIJKLMnopqrstuvwxyz1234567890", 0
msgB: DC.B "is this OK?", 0
msgC: DC.B "Keep texts short!", 0
msgD: DC.B "Oh yeah!", 0

; ROM: Code section
.init:  SECTION

main:
Entry:
        LDS  #__SEG_END_SSTACK          ; Initialize stack pointer
        CLI                             ; Enable interrupts, needed for debugger

        JSR  delay_10ms                 ; Delay 20ms during power up
        JSR  delay_10ms                 ; by Jump-Subroutine (use step-over)

        JSR  initLCD                    ; Initialize the LCD

        LDX  #MSG1                      ; MSG1 for line 0, X points to MSG1
        LDAB #0                         ; Write to line 0
        JSR  writeLine

        LDX  #MSG2                      ; MSG2 for line 1, X points to MSG2
        LDAB #1                         ; Write to line 1
        JSR  writeLine

        JSR delay_10ms
        
        LDX  #msgA                      ; MSG1 for line 0, X points to MSG1
        LDAB #0                         ; Write to line 0
        JSR  writeLine

        LDX  #msgB                      ; MSG2 for line 1, X points to MSG2
        LDAB #1                         ; Write to line 1
        JSR  writeLine  

        JSR delay_10ms
        
        LDX  #msgC                      ; MSG1 for line 0, X points to MSG1
        LDAB #0                         ; Write to line 0
        JSR  writeLine

        LDX  #msgD                      ; MSG2 for line 1, X points to MSG2
        LDAB #1                         ; Write to line 1
        JSR  writeLine   

back:   BRA back

