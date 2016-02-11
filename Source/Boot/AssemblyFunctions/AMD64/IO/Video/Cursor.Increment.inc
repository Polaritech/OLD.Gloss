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
[BITS 64]

; The following function is located in the .TEXT section of the executable.
[SECTION .TEXT]

AMD64.IO.Video.Cursor.Increment:
	mov ax, [Data.Video.CursorLocation]
	inc ax
	mov [Data.Video.CursorLocation], ax

	xor dx, dx
	div byte 0x50
	cmp al, 25
	jae AMD64.IO.Video.Cursor.Increment.Done

	mov rsi, 0xb8050
	mov rdi, 0xb8000
	mov rcx, 480
	rep movsq

	mov rsi, 0xb8000+1920
	mov rax, 0x0000000000000000
	mov rcx, 0x18
	rep movsq

	mov ax, [Data.Video.CursorLocation]
	sub ax, 0x50
	mov [Data.Video.CursorLocation], ax

	call AMD64.IO.Video.Cursor.Write
	ret