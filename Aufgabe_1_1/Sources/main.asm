; Labor 1 - Aufgabe 1.1
; Incrementing a value once per second and binary output to LEDs

; export symbols
        XDEF Entry, main

; import symbols
        XREF __SEG_END_SSTACK ; End of stack

; include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; RAM: Variable data section
.data: SECTION
var1: DS.W 1 ; one 16 bit variable

; ROM: Constant data
.const: SECTION

; ROM: Code section
.init: SECTION

main: ; Begin of the program
Entry:
        LDS #__SEG_END_SSTACK           ; Initialize stack pointer
        CLI                             ; Enable interrupts, needed for debugger

        BSET DDRJ, #2                   ; Set Port J.1 as output
        BCLR PTJ, #2                    ; Clear J.1 -> activate LEDs
        MOVB #$FF, DDRB                 ; Set Ports B 0-7 (LED-Ports) as outputs
        MOVB #$FF, PORTB                ; Turn on every LED

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
        STAB PORTB
        RTS

delay_0_5sec:
        LDX #$000D ; Set the number of iterations for the delay
        JSR delay_loop ; Jump to subroutine
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
