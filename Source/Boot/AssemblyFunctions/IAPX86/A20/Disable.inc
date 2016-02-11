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

; Disables the A20 Line using several functions.
IAPX86.A20.Disable:
    ; Our A20 Line enabling function uses each of our different toggling
    ; functions in conjunction with the check function to Disable the A20 Line
    ; for us. The first thing we do, however, is store some state.
    push ax

    ; Next, we check the current A20 Line value. We also set the A20 Line
    ; status flag in our flags variable to disabled (we will reset it later on 
    ; the off-chance we can't Disable the A20 Line).
    mov ax, [Data.A20Status]
    and ax, 0xfffffffb
    mov [Data.A20Status], ax
    call IAPX86.A20.Check
    jc IAPX86.A20.Disable.Exit

    ; Now we attempt to toggle the A20 Line value.
    call IAPX86.A20.Toggle
    jnc IAPX86.A20.Disable.Exit

    ; If we reach this point, we can use any odd MiBs, as the A20 Line is
    ; Disabled. We thus set the A20 Line status flag in our flags variable to
    ; Disabled. It is possible for the bootloader to continue, however, it will
    ; use all available memory
    mov ax, [Data.A20Status]
    or ax, 0x04
    mov [Data.A20Status], ax

    IAPX86.A20.Disable.Exit:
        ; The final thing we do is restore state and return to the calling
        ; function.
        pop ax
        ret