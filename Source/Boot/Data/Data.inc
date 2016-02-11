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
;[BITS 16]
;[CPU 8086]

; The following function is located in the .TEXT section of the executable.
[SECTION .TEXT]

Data:
    Data.Message.Init.Splash001:        db "GLOSS - Generic Loader for Operating System Software", 0x0a, 0x00
    Data.Message.Init.Splash002:        db "Version 0.0.1-A", 0x0a, 0x00
    Data.Message.Init.Splash003:        db "Copyright (c) 2013-2016 - Adrian J. Collado", 0x0a, 0x00
    Data.Message.Init.Splash004:        db "Sponsored & Developed by the Rensselaer Center for Open Source.", 0x0a, 0x00
    Data.Message.NewLine:               db 0x0a, 0x00

    Data.Message.Abort:                 db "Boot Aborted. Please Restart Your Computer.", 0x0a, 0x00

    Data.Message.BIOS.Error.Generic:    db "  BIOS Error: ", 0x00
    Data.Message.BIOS.Error.Code00:     db "Unknown", 0x0a, 0x00
    Data.Message.BIOS.Error.Code01:     db "Invalid Function", 0x0a, 0x00
    Data.Message.BIOS.Error.Code02:     db "Missing Address Mark", 0x0a, 0x00
    Data.Message.BIOS.Error.Code04:     db "Sector Not Found or Read Error", 0x0a, 0x00
    Data.Message.BIOS.Error.Code06:     db "Disk Changed", 0x0a, 0x00
    Data.Message.BIOS.Error.Code08:     db "DMA Overrun", 0x0a, 0x00
    Data.Message.BIOS.Error.Code09:     db "Data Boundary Error", 0x0a, 0x00
    Data.Message.BIOS.Error.Code0C:     db "Unsupported Track or Invalid Media", 0x0a, 0x00
    Data.Message.BIOS.Error.Code10:     db "Uncorrectable CRC or ECC Error on Read", 0x0a, 0x00
    Data.Message.BIOS.Error.Code20:     db "Controller Failure", 0x0a, 0x00
    Data.Message.BIOS.Error.Code40:     db "Seek Failed", 0x0a, 0x00
    Data.Message.BIOS.Error.Code80:     db "Timout", 0x0a, 0x00
    Data.Message.BIOS.Error.CodeB0:     db "Media Not Locked", 0x0a, 0x00
    Data.Message.BIOS.Error.CodeB1:     db "Media Locked", 0x0a, 0x00
    Data.Message.BIOS.Error.CodeB2:     db "Media Not Removable", 0x0a, 0x00
    Data.Message.BIOS.Error.CodeB3:     db "Media In Use", 0x0a, 0x00
    Data.Message.BIOS.Error.CodeB4:     db "Lock Count Exceeded", 0x0a, 0x00
    Data.Message.BIOS.Error.CodeB5:     db "Eject Request Failed", 0x0a, 0x00
    Data.Message.BIOS.Error.CodeB6:     db "Media is Read Only", 0x0a, 0x00

    Data.BIOSErrorTable.CDBoot.T1:      dw Data.Message.BIOS.Error.Code00
                                        dw Data.Message.BIOS.Error.Code01
                                        dw Data.Message.BIOS.Error.Code02
                                        dw Data.Message.BIOS.Error.Code00
                                        dw Data.Message.BIOS.Error.Code04
                                        dw Data.Message.BIOS.Error.Code00
                                        dw Data.Message.BIOS.Error.Code06
                                        dw Data.Message.BIOS.Error.Code00
                                        dw Data.Message.BIOS.Error.Code08
                                        dw Data.Message.BIOS.Error.Code09

    Data.BIOSErrorTable.CDBoot.T2:      dw Data.Message.BIOS.Error.CodeB0
                                        dw Data.Message.BIOS.Error.CodeB1
                                        dw Data.Message.BIOS.Error.CodeB2
                                        dw Data.Message.BIOS.Error.CodeB3
                                        dw Data.Message.BIOS.Error.CodeB4
                                        dw Data.Message.BIOS.Error.CodeB5
                                        dw Data.Message.BIOS.Error.CodeB6
