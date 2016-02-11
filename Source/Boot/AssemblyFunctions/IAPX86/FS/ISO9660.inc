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

IAPX86.FS.ISO9660.FindFile:
    mov eax, 0x00000010
    mov di, 0x4000
    call IAPX86.Storage.CD.LoadSector

    cmp byte [di], 0x01
    jne IAPX86.FS.ISO9660.FindFile.Failure

    cmp byte [di+156], 34
    jb IAPX86.FS.ISO9660.FindFile.Failure
    cmp byte [di+156+25], 2
    je IAPX86.FS.ISO9660.FindFile.Failure
    cmp byte [di+156+26], 0
    jne IAPX86.FS.ISO9660.FindFile.Failure
    cmp byte [di+156+27], 0
    jne IAPX86.FS.ISO9660.FindFile.Failure
    mov eax, [di+156+2]
    mov ecx, [di+156+10]
    cmp ecx, 1
    jne IAPX86.FS.ISO9660.FindFile.Failure

    IAPX86.FS.ISO9660.FindFile.NextRootSector:
        mov edi, 0x4000
        call IAPX86.Storage.CD.LoadSector

    IAPX86.FS.ISO9660.FindFile.NextRootRecord:
        mov 
