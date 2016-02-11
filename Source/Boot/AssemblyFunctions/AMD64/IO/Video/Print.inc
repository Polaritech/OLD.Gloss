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

AMD64.IO.Video.Print:
	mov ah, [Data.Video.AttributeByte]

	AMD64.IO.Video.Print.TryBackspace:
	cmp al, 0x08
	jne AMD64.IO.Video.Print.TryTab
	call AMD64.IO.Video.Print.Handle.Backspace
	jmp AMD64.IO.Video.Print.NewLine

	AMD64.IO.Video.Print.TryTab:
	cmp al, 0x09
	jne AMD64.IO.Video.Print.TryCarriageReturn
	call AMD64.IO.Video.Print.Handle.Tab
	jmp AMD64.IO.Video.Print.NewLine

	AMD64.IO.Video.Print.TryCarriageReturn:
	cmp al, 0x0d
	jne AMD64.IO.Video.Print.TryNewLine
	call AMD64.IO.Video.Print.Handle.CarriageReturn
	jmp AMD64.IO.Video.Print.NewLine

	AMD64.IO.Video.Print.TryNewLine:
	cmp al, 0x0a
	jne AMD64.IO.Video.Print.TryOther
	call AMD64.IO.Video.Print.Handle.NewLine
	jmp AMD64.IO.Video.Print.NewLine

	AMD64.IO.Video.Print.TryOther:
	cmp al, 0x20
	jb AMD64.IO.Video.Print.NewLine
	mov ebx, [Data.Video.VideoMemoryBase]
	mov cx, [Data.Video.CursorLocation]
	mov [rbx + cx], ax
	call AMD64.IO.Video.Cursor.Increment

	AMD64.IO.Video.Print.NewLine:
		xchg cx, ax
		div byte 0x50
		cmp al, 25

	AMD64.IO.Video.Print.Handle.Backspace:
		cmp al, 0x08
		jne AMD64.IO.Video.Print.Handle.Tab
		mov bx, [Data.Video.CursorLocation]
		xchg ax, bx
		div byte 0x50
		test ah, ah
		jz AMD64.IO.Video.Print.CheckNew
		xchg ax, bx
		dec word [Data.Video.Cursorlocation]
		jmp AMD64.IO.Video.Print.CheckNew

	AMD64.IO.Video.Print.Handle.Tab:
