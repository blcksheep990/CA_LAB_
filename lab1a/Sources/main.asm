
; Labor 1 - Problem 2.2
; Incrementing a value once per second and binary output to LEDs
;
; Computerarchitektur
; (C) 2019-2022 J. Friedrich, W. Zimmermann, R. Keller
; Hochschule Esslingen
;
; Author: R. Keller, HS-Esslingen
; (based on code provided by J. Friedrich, W. Zimmermann)
; Modified: -
;

; export symbols
        XDEF Entry, main

; import symbols
        XREF __SEG_END_SSTACK ; End of stack

; include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; Defines
        SPEED: EQU $FFFF ; Change this number to change counting speed

; RAM: Variable data section
.data: SECTION
var1: DS.W 1 ; one 16 bit variable
; one 8 bit variable

; ROM: Constant data
.const: SECTION

; ROM: Code section
.init: SECTION

main: ; Begin of the program
Entry:
        LDS #__SEG_END_SSTACK ; Initialize stack pointer
        CLI ; Enable interrupts, needed for debugger


        BSET DDRJ, #2
        BCLR PTJ, #2
        MOVB #$FF, DDRB
        MOVB #$FF, PORTB

reset:
        CLRA
        CLRB
        MOVW #0, var1
        BRA loop

loop:
        LDD var1
        ADDD #2
        CPD #63
        BGT reset
        STD var1
        JSR lightOn
        JSR delay_0_5sec
        BRA loop

lightOn:
;LDD var1
;EORB #$FF
        STAB PORTB
        RTS

delay_0_5sec:
        LDX #$000D ; Set the number of iterations for the delay
        JSR delay_loop
        RTS
delay_loop:
        DEX
        LDY #$FFFF
        CPX #0
        BNE delay_loop_2
        RTS
delay_loop_2:
        DEY
        BNE delay_loop_2
        BRA delay_loop