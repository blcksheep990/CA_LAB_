        XDEF initLED, setLED, getLED, toggleLED
        
        INCLUDE 'mc9s12dp256.inc'

.data: SECTION
var1: DS.B 1

.vect: SECTION

.const: SECTION

.init: SECTION



initLED:
        
        BSET DDRJ, #2
        BCLR PTJ, #2
        MOVB #$FF, DDRB
        MOVB #$FF, PORTB
        RTS
        
setLED:
        STAB PORTB
        RTS

getLED:
        
        LDAB PORTB
;toggleLED:
