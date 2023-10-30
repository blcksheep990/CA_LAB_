;
;   Labor 1 - 

;# done by Tim and Florian

; Export symbols
        XDEF Entry, main

; Import symbols
        XREF __SEG_END_SSTACK                   ; End of stack
        XREF initLCD, writeLine, delay_10ms     ; LCD functions
        XREF delay_0_5sec, decToASCII, hexToASCII
        XREF initLED, setLED, getLED, toggleLED

; Include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; Defines

; RAM: Variable data section
.data:  SECTION
dec_string: DS.B 7
hex_string: DS.B 7
i:      DS.w 1

; ROM: Constant data
.const: SECTION

; ROM: Code section
.init:  SECTION

main:
Entry:
        LDS  #__SEG_END_SSTACK          ; Initialize stack pointer
        CLI                             ; Enable interrupts, needed for debugger

        JSR delay_10ms                  ; Delay 20ms during power up
        JSR delay_10ms                  ; by Jump-Subroutine (use step-over)

        JSR initLCD                     ; Initialize the LCD
        JSR initLED                     ; Execute Subroutine initLED

        MOVB #$00, DDRH

        LDX #0
        STX i
Loop:   
        LDX #0                          ; Store Addresses of val into X
        LEAX dec_string, X              ;
        LDD i
        JSR decToASCII
        LDAB #0
        JSR writeLine

        LDX #0
        LEAX hex_string, X
        LDD i
        JSR hexToASCII
        LDAB #1
        JSR writeLine

        LDD i
        JSR setLED                      ; Jump to subroutine setLED
        BRSET PTH, #$01, butten0pressed
        BRSET PTH, #$02, butten1pressed
        BRSET PTH, #$04, butten2pressed
        BRSET PTH, #$08, butten3pressed
        ADDD #1
        

        ;BRCLR

GoOn:
        STD i

        JSR delay_0_5sec

        BRA Loop

butten0pressed:
        ADDD #16
        BRA GoOn

butten1pressed:
        ADDD #10
        BRA GoOn

butten2pressed:
        SUBD #16
        BRA GoOn

butten3pressed:
        SUBD #10
        BRA GoOn


