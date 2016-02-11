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

IAPX86.Error.CriticalFailure:
    IAPX86.Error.CriticalFailure.LoadSector.CD:
        movzx eax, ah
        mov si, Data.Message.BIOS.Error.Generic
        call IAPX86.IO.Print.String

        cmp al, 0x09
        ja IAPX86.Error.CriticalFailure.LoadSector.CD.NotTable
        mov si, [Data.BIOSErrorTable.CDBoot.T1 + eax * 2]
        jmp IAPX86.Error.Abort

        IAPX86.Error.CriticalFailure.LoadSector.CD.NotTable:
            mov si, Data.Message.BIOS.Error.Code0C
            cmp al, 0x0c
            je IAPX86.Error.Abort

            mov si, Data.Message.BIOS.Error.Code10
            cmp al, 0x10
            je IAPX86.Error.Abort

            mov si, Data.Message.BIOS.Error.Code20
            cmp al, 0x20
            je IAPX86.Error.Abort

            mov si, Data.Message.BIOS.Error.Code40
            cmp al, 0x40
            je IAPX86.Error.Abort

            mov si, Data.Message.BIOS.Error.Code80
            cmp al, 0x80
            je IAPX86.Error.Abort

            cmp al, 0xB0
            jb IAPX86.Error.CriticalFailure.LoadSector.CD.Default
            cmp al, 0xB6
            ja IAPX86.Error.CriticalFailure.LoadSector.CD.Default

            mov si, [Data.BIOSErrorTable.CDBoot.T2 + eax*2 - 0xB0 * 2]
            jmp IAPX86.Error.Abort

        IAPX86.Error.CriticalFailure.LoadSector.CD.Default:
            mov si, Data.Message.BIOS.Error.Code00
            jmp IAPX86.Error.Abort
