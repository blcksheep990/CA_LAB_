;   Labor 1 - Vorbereitungsaufgabe 2.2
;   convert a 16 bit hexadecimal value into a NUL-terminated ASCII-string

;# done by Tim and Florian:

; export symbols
        XDEF Entry, main

; import symbols
        XREF __SEG_END_SSTACK           ; End of stack
        XREF hexToASCII                 ; Referenced from other object file

; include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; Defines

; RAM: Variable data section
.data:  SECTION
val: DC.W 1
string: DC.B 7

; ROM: Constant data
.const: SECTION

; ROM: Code section
.init:  SECTION

main:                                   ; Begin of the program
Entry:
        LDS  #__SEG_END_SSTACK          ; Initialize stack pointer
        CLI                             ; Enable interrupts, needed for debugger

        LDX #0                          ; Store Addresses of Ctext and Vtext to X and Y
        LEAX string, X                  ;

        LDY #0
Loop:
        STY val
        LDD val
        JSR hexToASCII
        INY
        BRA Loop


        
