;# done by Tim and Florian:
; export symbols
        XDEF delay_0_5sec

.data: SECTION

.vect: SECTION

.const: SECTION

.init: SECTION

delay_0_5sec:
        LDX #$000D                      ; Set the number of iterations for the delay
        JSR delay_loop                  ; Jump to subroutine delay_loop
        RTS                             ; Return from Subroutine
delay_loop:
        DEX                             ; Decrement the value of register X (iteration)
        LDY #$FFFF                      ; Load the number of iteration in the Y register
        CPX #0                          ; Compare the value of X with zero
        BNE delay_loop_2                ; If the value in X is greater than zero jump to subroutine delay_loop_2
        RTS                             ; Return from Subroutine
delay_loop_2:                           ; Second loop because bit value is to high for 1 Byte to get the 0,5sec delay
        DEY                             ; Decrement the value of register Y (iteration)
        BNE delay_loop_2                ; If the value in register Y is not equal to zero go back to the start of the subroutine 
        BRA delay_loop                  ; If the value is zero, the operation before is not true so the program is executing this operation instead and branch to subroutine delay_loop