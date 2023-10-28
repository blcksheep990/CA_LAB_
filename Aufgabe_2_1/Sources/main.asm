;   Labor 1 - Vorbereitungsaufgabe 2.1
;   Convert a zero-terminated ASCIIZ string to lower characters

;# done by Florian

; export symbols
        XDEF Entry, main

; import symbols
        XREF __SEG_END_SSTACK           ; End of stack
        XREF toLower, strCpy            ; Referenced from other object file

; include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; Defines

; RAM: Variable data section
.data:  SECTION
Vtext:  DS.B    80                      ; Please store String here

; ROM: Constant data
.const: SECTION
Ctext:  DC.B  "Test 12345 *!? ABCDE abcde zZ", 0

; ROM: Code section
.init:  SECTION

main:                                   ; Begin of the program
Entry:
        LDS  #__SEG_END_SSTACK          ; Initialize stack pointer
        CLI                             ; Enable interrupts, needed for debugger
        
        LDX #0                          ; Store Addresses of Ctext and Vtext to X and Y
        LDY #0                          ;
        LEAX Ctext, X                   ;
        LEAY Vtext, Y                   ;

        TFR Y, D                        ; Store Address of Vtext also to D

        JSR strCpy                      ; execute strCpy
        JSR toLower                     ; execute toLower
Finish_loop:
        BRA Finish_loop                 ; Wie Beendet man das Programm ????
