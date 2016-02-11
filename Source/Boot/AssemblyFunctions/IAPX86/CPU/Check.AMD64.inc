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
[CPU SandyBridge]

; The following function is located in the .TEXT section of the executable.
[SECTION .TEXT]

IAPX86.CPU.Check.AMD64:
    pushfd
    pop eax

    mov ecx, eax

    xor eax, 1 << 21

    push eax
    popfd

    pushfd
    pop eax

    push ecx
    popfd

    xor eax, ecx
    jz IAPX86.CPU.Check.AMD64.Failure

    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb IAPX86.CPU.Check.AMD64.Failure

    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz IAPX86.CPU.Check.AMD64.Failure

    clc
    jmp IAPX86.CPU.Check.AMD64.Done

    IAPX86.CPU.Check.AMD64.Failure:
        stc

    IAPX86.CPU.Check.AMD64.Done:
        ret