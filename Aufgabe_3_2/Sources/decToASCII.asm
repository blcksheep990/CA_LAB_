;# done by Florian and Tim:

; export symbols
        XDEF decToASCII

; Defines

; RAM: Variable data section
.data: SECTION

; ROM: Constant data
.const: SECTION

; ROM: Code section
.init: SECTION

decToASCII:
        PSHX
        PSHY
        PSHD

        TFR X,Y
        TFR D,X
        BPL First_else
        LDAA #$2D
        BRA First_end_if
First_else:
        LDAA #$20
First_end_if:
        STAA Y
        INY
        TFR X,D

        LDX #10000
        IDIVS
        EXG D, X
        BPL Pos_value
        EORA #$FF
        EORB #$FF
        ADDD #1
Pos_value:
        ADDD #$30
        STAB Y
        TFR X, D
        INY

        LDX #1000
        IDIVS
        EXG D, X
        BPL Pos_value_2
        EORA #$FF
        EORB #$FF
        ADDD #1
Pos_value_2:
        ADDD #$30
        STAB Y
        TFR X, D
        INY

        LDX #100
        IDIVS
        EXG D, X
        BPL Pos_value_3
        EORA #$FF
        EORB #$FF
        ADDD #1
Pos_value_3:
        ADDD #$30
        STAB Y
        TFR X, D
        INY

        LDX #10
        IDIVS
        EXG D, X
        BPL Pos_value_4
        EORA #$FF
        EORB #$FF
        ADDD #1
Pos_value_4:
        ADDD #$30
        STAB Y
        TFR X, D
        INY

        LDX #1
        IDIVS
        EXG D, X
        BPL Pos_value_5
        EORA #$FF
        EORB #$FF
        ADDD #1
Pos_value_5:
        ADDD #$30
        STAB Y
        TFR X, D
        INY

        LDAB #0
        STAB Y

        PULD
        PULY
        PULX
        RTS
