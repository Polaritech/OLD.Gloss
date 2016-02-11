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

IAPX86.Storage.CD.LoadSector:
    mov byte [BSS.Storage.CD.DiskRetries], 3

    IAPX86.Storage.CD.LoadSector.Loop:
        pushad

        mov byte [BSS.Storage.CD.DiskPacket.Size], 0x10
        mov byte [BSS.Storage.CD.DiskPacket.Blocks], 0x01
        mov word [BSS.Storage.CD.DiskPacket.Dest.Offset], di
        mov [BSS.Storage.CD.DiskPacket.LBA.Lower], eax

        mov ah, 0x42
        mov dl, [BSS.Storage.DriveNumber]
        mov si, BSS.Storage.CD.DiskPacket
        int 0x13

        jc IAPX86.Storage.CD.LoadSector.Error
        test ah, ah
        je IAPX86.Storage.CD.LoadSector.Done

    IAPX86.Storage.CD.LoadSector.Error:
        sub byte [BSS.Storage.CD.DiskRetries], 1
        popad
        jae IAPX86.Storage.CD.LoadSector.Loop

        ; ERROR MESSAGE HERE

        jmp IAPX86.Error.CriticalFailure.LoadSector.CD

    IAPX86.Storage.CD.LoadSector.Done:
        popad
        ret