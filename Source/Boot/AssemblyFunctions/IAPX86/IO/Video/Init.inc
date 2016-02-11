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

IAPX86.IO.Video.Init:
    mov ax, 0x1a00
    stc
    int 0x10
    cmp al, 0x1a
    jne IAPX86.IO.Video.Init.Done
    or word [BSS.Video.Flags], 0x0001

    mov ax, 0x1b00
    xor bx, bx
    mov di, BSS.Video.State
    int 0x10
    cmp al, 0x1b
    jne IAPX86.IO.Video.Init.Reset
    cmp byte [BSS.Video.State.VideoMode], 0x03
    jne IAPX86.IO.Video.Init.Reset
    cmp byte [BSS.Video.State.Display.Columns], 0x50
    jne IAPX86.IO.Video.Init.Reset
    cmp byte [BSS.Video.State.Display.Rows], 0x19
    je IAPX86.IO.Video.Init.SetProperties
    cmp byte [BSS.Video.State.Display.Rows], 0x18
    je IAPX86.IO.Video.Init.SetProperties

    IAPX86.IO.Video.Init.Reset:
        mov ax, 0x0003
        int 0x10

    IAPX86.IO.Video.Init.SetProperties:
        mov ah, 0x01
        mov cx, 0x2d0e
        int 0x10

        mov ax, 0x1003
        xor bx, bx
        int 0x10

        xor bx, bx
        mov ah, 0x0f
        int 0x10

        mov [BSS.Video.DisplayPage], bh

    IAPX86.IO.Video.Init.Done:
        ret