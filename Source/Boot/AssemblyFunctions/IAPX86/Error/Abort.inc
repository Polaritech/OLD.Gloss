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

; The following function is located in the .TEXT section of the executable.
[SECTION .TEXT]

IAPX86.Error.Abort:
    call IAPX86.IO.Print.String

    mov si, Data.Message.Abort
    call IAPX86.IO.Print.String

    IAPX86.Error.Abort.Halt:
        hlt
        jmp IAPX86.Error.Abort.Halt