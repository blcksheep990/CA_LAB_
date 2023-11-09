;# done by Tim and Florian:
; export symbols
        XDEF initLED,setLED,getLED,toggleLED
        
; include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; RAM: Variable data section
.data: SECTION
temp:   ds.b 1
.const: SECTION

.vect: SECTION

; ROM: Constant data


; ROM: Code section
.init: SECTION

initLED:
        BSET DDRJ, #2                   ; Set Port J.1 as output
        BCLR PTJ, #2                    ; Clear J.1 -> activate LEDs
        MOVB #$FF, DDRB                 ; Set Ports B 0-7 (LED-Ports) as outputs
        MOVB #$FF, PORTB                ; Turn on every LED
        RTS                             ; Return from subroutine

setLED:
        STAB PORTB                      ; Store B to PORTB
        RTS                             ; Return from subroutine

;# done by Tim: 
getLED:
        LDAB PORTB                      ; Load B from PORTB
        RTS                             ; Return from subroutine

toggleLED:
        STAB temp
        JSR  getLED                     ; Run Subroutine getLED
        EORB temp                       ; B =^ X
        JSR  setLED                     ; Run Subroutine setLED
        RTS                             ; Return form subroutine
