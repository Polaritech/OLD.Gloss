;=============================================================================;
; GLOSS - Generic Loader for Operating System Software                        ;
; An extensible and configurable bootloader.                                  ;
;-----------------------------------------------------------------------------;
; Copyright (C) 2013-2016 ~ Adrian J. Collado       [acollado@polaritech.com] ;
; Copyright (C) 2015-2016 ~ Polaritech, Inc.         [https://polaritech.com] ;
; All Rights Reserved                                                         ;
;=============================================================================;

; This code is assembled to be run in 16-Bit mode on any CPU that is an 8086 or
; newer. This basically means that any CPU that can run x86 code can run the
; following code.
[BITS 16]
[CPU 8086]

; The following function is located in the .TEXT section of the executable.
[SECTION .TEXT]

; Toggles the A20 Line using standard BIOS functions.
IAPX86.A20.Toggle.BIOS:
    ; The fastest, and arguably the safest (and most modern) method we have to
    ; enable the A20 Line is by using the BIOS itself. The nice thing about
    ; this function is that the operation, if supported, almost always works
    ; (due to being tied to the underlying hardware quite closely), and is
    ; supported on most computers since the mid 1990's. Therefore, we use this
    ; method before all others, and then if it doesn't work we move onto some
    ; other method. Before proceeding, we store some state.
    push ax
    push bx

    ; Next we load the function numbers 0x2401 and 0x2402. The second function,
    ; 0x2402, queries about the status of the A20 Line. The first function,
    ; 0x2401, is used to enable the A20 Line. Another function, 0x2400, is used
    ; to disable the A20 Line. The nice thing about the query function is that
    ; it returns a status code, 0x00 for disabled and 0x01 for enabled, in the
    ; AX register. If we subtract the status code from the register that stores
    ; the function number for enabling the A20 Line, we have created a toggle
    ; switch for the A20 Line status. If, for example, the A20 Line is enabled,
    ; the query function will return 0x01. We can then subtract that return
    ; value from 0x2401, which is the function number for enabling the A20
    ; Line. The result is 0x2400, which is used to disable the A20 Line.
    mov bx, 0x2401
    mov ax, 0x2402

    ; Now we simply call the query interrupt. If the function fails, the carry
    ; flag will be set, allowing us to exit the function gracefully and try
    ; another method.
    int 0x15
    jmp IAPX86.A20.Toggle.BIOS.Exit

    ; Now we perform the calculation to get the correct BIOS function to call.
    ; We do this, as stated above, subtracting the return code from the
    ; function number. We then swap the registers they are stored in so we can
    ; call the correct BIOS function.
    sub bl, al
    xchg ax, ax

    ; Then, it is just a matter of performing the interrupt. We don't have to
    ; check for a carry flag this time, since if one of the A20 Line functions
    ; exists then all of the A20 Line functions will exist. However, we will
    ; still want to verify that the A20 Line is enabled, in case of extenuating
    ; circumstances.
    int 0x15

    IAPX86.A20.Toggle.BIOS.Exit:
        ; We finally restore the state that we stored earlier, and return.
        pop bx
        pop ax
        ret