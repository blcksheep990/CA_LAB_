;#done by Tim and Florian:

; export symbols
        XDEF hexToASCII

; Defines

; RAM: Variable data section
.data: SECTION

; ROM: Constant data
.const: SECTION
H2A: DC.B "0123456789ABCDEF"

; ROM: Code section
.init: SECTION

hexToASCII:
        PSHX
        PSHY
        TFR D, Y
        LDAA #$30
        STAA X
        INX
        LDAA #$78
        STAA X
        INX
        PSHX
        TFR Y, D
        LDX #12
Shift_loop:
        LSRD
        DEX
        BNE Shift_loop

        PULX

        ANDB #$F
        PSHY
        TFR B, Y
        LDAA H2A, Y
        STAA X
        PULY

        INX
        PSHX
        TFR Y, D
        LDX #08
Shift_loop_2:
        LSRD
        DEX
        BNE Shift_loop_2

        PULX

        ANDB #$F
        PSHY
        TFR B, Y
        LDAA H2A, Y
        STAA X
        PULY

        INX
        PSHX
        TFR Y, D
        LDX #4
Shift_loop_3:
        LSRD
        DEX
        BNE Shift_loop_3

        PULX

        ANDB #$F
        PSHY
        TFR B, Y
        LDAA H2A, Y
        STAA X
        PULY

        INX
        TFR Y, D
        ANDB #$F
        PSHY
        TFR B, Y
        LDAA H2A, Y
        STAA X
        PULY

        INX
        LDAA #0
        STAA X

        TFR Y, D

        PULY
        PULX
        RTS