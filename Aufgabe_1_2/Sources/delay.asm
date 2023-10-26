        XDEF delay_0_5sec

.data: SECTION

.vect: SECTION

.const: SECTION

.init: SECTION

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