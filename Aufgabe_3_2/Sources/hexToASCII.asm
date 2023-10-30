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

;**************************************************************
; Public interface function: hexToASCII ... convert a hexadecimal value to ASCII 
; Parameter: X ... pointer to output string
;            D ... input hexadecimal value
; Return:    -
hexToASCII:
        ; Store adress of string and register Y into Stack for later re-use  
        PSHX            
        PSHY
        ; Transfer register D into Y (value of variable <val>)            
        TFR D, Y
        ; Set 0x        
        LDAA #$30               
        STAA X          
        INX             
        LDAA #$78
        STAA X
        INX
        ; 1. hex value to ASCII
        ; SLR 12 times on register D
        PSHX
        TFR Y, D
        
        LDX #12

Shift_loop:
        LSRD
        DEX
        BNE Shift_loop

        PULX
        ; set everything zero except the first four bits        
        ANDB #$F
        ; translate hex value into ASCII and safe to string 
        PSHY
        TFR B, Y
        LDAA H2A, Y
        STAA X
        PULY
        ; increaso string pointer to next character
        INX
        ; 2. hex value to ASCII
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
        ; 3. hex value to ASCII
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
        ; 4. hex value to ASCII
        TFR Y, D
        ANDB #$F
        PSHY
        TFR B, Y
        LDAA H2A, Y
        STAA X
        PULY

        INX
        ; Set string zero
        LDAA #0
        STAA X
        ; Restore values
        TFR Y, D

        PULY
        PULX
        RTS
