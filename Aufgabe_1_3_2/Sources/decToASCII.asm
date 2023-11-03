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
;**************************************************************
; Public interface function: decToASCII ... convert a decimal value to ASCII 
; Parameter: X ... pointer to output string
;            D ... input decimal value
; Return:    -
decToASCII:
        PSHX
        PSHY
        PSHD

        TFR X,Y
        TFR D,X
        ; determine sign
        BPL First_else
        LDAA #'-'
        BRA First_end_if
First_else:
        LDAA #' '
First_end_if:
        STAA Y
        INY
        TFR X,D
        ; determine digit 5
        LDX #10000
        IDIVS                           ; X = value/10000 (integer division)
        EXG D, X                        ; D = value%10000 (Rest)
        BPL Pos_value                   ; 
        EORA #$FF                       ; - => +
        EORB #$FF                       ;
        ADDD #1                         ; because +1 is the second pos value and -1 the first neg value
Pos_value:
        ADDD #$30                       ; dec to ASCII
        STAB Y                          ; store to output string
        TFR X, D                        ; Rest is our new value
        INY
        ; determine digit 4 (same as digit 5 but with 1000)
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
        ; determine digit 3 (same as digit 5 but with 100)
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
        ; determine digit 2 (same as digit 5 but with 10)
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
        ; determine digit 1 (same as digit 5 but with 1)
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
        ; store terminating \0
        LDAB #0
        STAB Y

        PULD
        PULY
        PULX
        RTS
