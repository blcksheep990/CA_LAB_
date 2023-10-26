        XDEF initLED
        INCLUDE 'mc9s12dp256.inc'

initLED:
        
        BSET DDRJ, #2
        BCLR PTJ, #2
        MOVB #$FF, DDRB
        MOVB #$FF, PORTB
        RTS
        
;setLED:

;getLED:

;toggleLED:
