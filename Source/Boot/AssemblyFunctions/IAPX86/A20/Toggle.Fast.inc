;=============================================================================;
; GLOSS - Generic Loader for Operating System Software                        ;
; An extensible and configurable bootloader.                                  ;
;-----------------------------------------------------------------------------;
; Copyright (C) 2013-2016 ~ Adrian J. Collado       [acollado@polaritech.com] ;
; Copyright (C) 2015-2016 ~ Polaritech, Inc.         [https://polaritech.com] ;
; All Rights Reserved                                                         ;
;=============================================================================;

; This code is assembled to be run in 16-bit mode on any CPU that is an 8086 or
; newer. This basically means that any CPU that can run x86 code can run the
; following code.
[BITS 16]
[CPU 8086]

; This function appears as executable code inside of a binary file.
[SECTION .TEXT]

; Toggles the A20 line using the Fast A20 method (System Control Port 0x92)
IAPX86.A20.Toggle.Fast:
    ; This function, while called the Fast A20 method, is actually quite slow,
    ; and on some systems is dangerous. This function is the least recommended
    ; of all of the functions we use to toggle the A20 line. What this function
    ; does is outputs a value through the system control port 0x92. The problem
    ; with this method is that on some computers it is unsupported, while on
    ; other computers it may do something entirely different (such as clearing
    ; the screen or eating your laundry). Therefore, we should only use this
    ; method if we have no other choice.
    push ax
    in al, 0x92
    xor al, 0x02
    and al, 0xfe
    out 0x92, al
    pop ax
    ret