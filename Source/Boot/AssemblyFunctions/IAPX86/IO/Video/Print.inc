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

IAPX86.IO.Video.Print:
    push ax
    push bx
    push cx
    push dx
    push si
    push di
    push bp
    cmp al, 0x0a
    jne IAPX86.IO.Video.Print.Output

    IAPX86.IO.Video.Print.Output.NewLine:
        mov ah, 0x0e
        mov bh, [BSS.Video.DisplayPage]
        int 0x10
        mov al, 0x0d

    IAPX86.IO.Video.Print.Output:
        mov ah, 0x0e
        mov bh, [BSS.Video.DisplayPage]
        int 0x10

    pop bp
    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop ax

    ret