;#done by Florian

; export symbols
        XDEF toLower, strCpy

; Defines

; RAM: Variable data section
.data: SECTION

; ROM: Constant data
.const: SECTION

; ROM: Code section
.init: SECTION

toLower:
        PSHX                            ; Save current X and D value on the stack
        PSHD                            ;
        TFR D, X                        ; Use X for the Address in D because wie use A
toLower_loop:
        LDAA X                          ; get the current character from memory
        CMPA #$41                       ; if char < $41 or char > $5A it is not a uppercase Letter so don't change anything
        BLT No_Change                   ;
        CMPA #$5A                       ;
        BGT No_Change                   ;
        ADDA #32                        ; else add 32 to make it a lowercase Letter
        STAA X                          ; Store the new value back to memory
No_Change:
        INX                             ; go to the next character
        CMPA #0                         ; if previous character != 0 do the loop again
        BNE toLower_loop                ;
        PULD                            ; get the stored values of X and D back from the stack
        PULX                            ;
        RTS                             ; Return from Subroutine

strCpy:
        PSHD                            ; Save current D, X and Y value on the stack
        PSHX
        PSHY
strCpy_loop:
        MOVB X, Y                       ; Store the value current character of X in Y             
        LDAA X                          ; Load the current character of X in A
        INX                             ; go to the next character in X and Y
        INY                             ;
        CMPA #0                         ; if the previous character is not 0 to it again
        BNE strCpy_loop
        PULY                            ; get the stored values of D, X and Y back
        PULX
        PULD
        RTS                             ; Return form Subroutine