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

; Enables the A20 Line using several functions.
IAPX86.A20.Toggle:
    ; Our A20 Line toggle function uses each of our different toggling
    ; functions in conjunction with the check function to toggle the A20 Line
    ; for us. The first thing we do, however, is store some state (and clear
    ; the carry flag).
    clc
    push ax
    push bx

    ; Next, we check the current A20 Line value so we can determine if toggling
    ; functions worked.
    call IAPX86.A20.Check
    pushf
    pop bx
    and bx, 0x01
    test bx, ax
    clc
    jne IAPX86.A20.Toggle.Exit

    ; Now we attempt to toggle the A20 Line using the BIOS. After trying this
    ; method, we check if the A20 Line is toggled using our check function.
    call IAPX86.A20.Toggle.BIOS
    call IAPX86.A20.Check
    pushf
    pop bx
    and bx, 0x01
    test bx, ax
    clc
    jne IAPX86.A20.Toggle.Exit

    ; If the BIOS function didn't work, we attempt to toggle the A20 Line using
    ; the PS/2 Controller. It is reasonable to assume that if the BIOS function
    ; failed, then the PS/2 function will succeed. We then check the A20 Line
    ; status again.
    call IAPX86.A20.Toggle.PS2
    call IAPX86.A20.Check
    pushf
    pop bx
    and bx, 0x01
    test bx, ax
    clc
    jne IAPX86.A20.Toggle.Exit

    ; Our last and final hope is to try the Fast A20 method. On some systems
    ; attempting this method can be extremely bad, but if we reach this point
    ; then we have nothing to lose. After calling the Fast A20 method, we once
    ; again check the A20 Line status.
    call IAPX86.A20.Toggle.Fast
    call IAPX86.A20.Check
    pushf
    pop bx
    and bx, 0x01
    test bx, ax
    clc
    jne IAPX86.A20.Toggle.Exit

    ; If we reach this point, we could not toggle the A20 Line. We thus return
    ; a carry flag as a failure result.
    stc

    IAPX86.A20.Toggle.Exit:
        ; The final thing we do is restore state and return to the calling
        ; function.
        pop bx
        pop ax
        ret