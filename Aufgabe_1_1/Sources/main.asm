; Labor 1 - Aufgabe 1.1
; Incrementing a value once per second and binary output to LEDs

;# done by Tim:

; export symbols
        XDEF Entry, main

; import symbols
        XREF __SEG_END_SSTACK           ; End of stack

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

        BSET DDRJ, #2                   ; Set Port J.1 as output
        BCLR PTJ, #2                    ; Clear J.1 -> activate LEDs
        MOVB #$FF, DDRB                 ; Set Ports B 0-7 (LED-Ports) as outputs
        MOVB #$FF, PORTB                ; Turn on every LED

reset:
        CLRA                            ; Write $00 to A
        CLRB                            ; Write $00 to B
        MOVW #0, var1                   ; Write $0000 to var1
        BRA loop                        ; Branch always to loop

loop:
        LDD var1                        ; load var1 value in D
        ADDD #2                         ; D = D + 2
        CPD #63                         ; compare D with 63
        BGT reset                       ; if D > 63 then branch to reset
        STD var1                        ; save D to var1
        JSR lightOn                     ; Jump to lightOn
        JSR delay_0_5sec                ; Jump to delay_0_5sec
        BRA loop                        ; do loop part again

lightOn:
        STAB PORTB                      ; Store B to PORTB
        RTS                             ; Return from Subroutine

;# done by Tim and Florian:

delay_0_5sec:
        LDX #$000D                      ; Set the number of iterations for the delay in X (iterations = X - 1)
        JSR delay_loop                  ; Jump to subroutine
        RTS                             ; Return
delay_loop:
        DEX                             ; X--
        LDY #$FFFF                      ; Y = $FFFF
        CPX #0                          ; Compare X with 0
        BNE delay_loop_2                ; if X != 0 then branch to delay_loop_2
        RTS                             ; Return
delay_loop_2:
        DEY                             ; Y--
        BNE delay_loop_2                ; while Y != 0 decrement again
        BRA delay_loop                  ; Branch to delay_loop
