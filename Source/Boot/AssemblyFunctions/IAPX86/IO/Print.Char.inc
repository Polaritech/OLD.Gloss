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

IAPX86.IO.Print.Char:
    IAPX86.IO.Print.Char.Serial:
        test word [BSS.Serial.Flags], 0x01
        je IAPX86.IO.Print.Char.Video
        call IAPX86.IO.Serial.Print
    IAPX86.IO.Print.Char.Video:
        test word [BSS.Video.Flags], 0x01
        je IAPX86.IO.Print.Char.Done
        call IAPX86.IO.Video.Print
    IAPX86.IO.Print.Char.Done:
        ret