; Labor 1 - Aufgabe 1.2
; Incrementing a value once per second and binary output to LEDs

;# done by Tim:

; export symbols
        XDEF Entry, main

; import symbols
        XREF __SEG_END_SSTACK           ; End of stack
        XREF initLED, setLED, getLED, delay_0_5sec, toggleLED

; include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; RAM: Variable data section
.data: SECTION
var1: DS.W 1                            ; one 16 bit variable

; ROM: Constant data
.const: SECTION

; ROM: Code section
.init: SECTION

main:                                   ; Begin of the program
Entry:
        LDS #__SEG_END_SSTACK           ; Initialize stack pointer
        CLI                             ; Enable interrupts, needed for debugger

        JSR initLED                     ; Execute Subroutine initLED

reset:
        CLRA                            ; Clear bits in register A
        CLRB                            ; Clear bits in register B
        MOVW #0, var1                   ; set bits in var1 to zero
        BRA loop                        ; Branch to Subroutine loop

loop:
        LDD var1                        ; Load var1 into register D
        ADDD #2                         ; Increment var1 which is loaded in register D with 2
        CPD #63                         ; Compare value of register D with the value of 63 (0-63=64)
        BGT reset                       ; If the value in D is greater than 63 branch back to subroutine reset
        STD var1                        ; Store the incremented value of register D back to var1
        JSR setLED                      ; Jump to subroutine setLED
        JSR delay_0_5sec                ; Jump to subroutine delay_0_5sec
        JSR toggleLED                   ; Jump to subroutine toggleLED
        BRA loop                        ; Branch back to subroutine loop
