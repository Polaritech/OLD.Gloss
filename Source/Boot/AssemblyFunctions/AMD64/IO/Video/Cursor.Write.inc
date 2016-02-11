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

; The following function is located in the .TEXT section of the executable.
[SECTION .TEXT]

AMD64.IO.Video.Cursor.Write:
	mov ax, [Data.Video.CursorLocation]
	out 0x03d4, byte 0x0e
	out 0x03d5, ah
	out 0x03d4, byte 0x0f
	out 0x03d5, al
	ret