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

; The following function is located in the .DATA section of the executable.
[SECTION .BSS]
BSS:
BSS.Video:
    BSS.Video.State:
        BSS.Video.State.StaticTable:                resb 4
        BSS.Video.State.VideoMode:                  resb 1
        BSS.Video.State.Display.Columns:            resb 2
        BSS.Video.State.RegenBuffer.Length:         resb 2
        BSS.Video.State.RegenBuffer.Address:        resb 2
        BSS.Video.State.Cursor.Page0:               resb 2
        BSS.Video.State.Cursor.Page1:               resb 2
        BSS.Video.State.Cursor.Page2:               resb 2
        BSS.Video.State.Cursor.Page3:               resb 2
        BSS.Video.State.Cursor.Page4:               resb 2
        BSS.Video.State.Cursor.Page5:               resb 2
        BSS.Video.State.Cursor.Page6:               resb 2
        BSS.Video.State.Cursor.Page7:               resb 2
        BSS.Video.State.Cursor.Type:                resb 2
        BSS.Video.State.ActiveDisplayPage:          resb 1
        BSS.Video.State.CRTCPortAddress:            resb 2
        BSS.Video.State.PortSetting.P03x8:          resb 1
        BSS.Video.State.PortSetting.P03x9:          resb 1
        BSS.Video.State.Display.Rows:               resb 1
        BSS.Video.State.BytesPerCharacter:          resb 2
        BSS.Video.State.Display.Code:               resb 1
        BSS.Video.State.Display.Alternate.Code:     resb 1
        BSS.Video.State.Display.Colors:             resb 2
        BSS.Video.State.Display.Pages:              resb 1
        BSS.Video.State.Display.ScanLines:          resb 1
        BSS.Video.State.Reserved:                   resb 21
    BSS.Video.DisplayPage:                          resb 1
    BSS.Video.Flags:                                resb 2
BSS.Serial:
    BSS.Serial.Flags:                               resb 2
; BSS.Storage:
;     BSS.Storage.CD:
;         BSS.Storage.CD.DiskRetries:                 resb 1
;         BSS.Storage.CD.DiskPacket:
;             BSS.Storage.CD.DiskPacket.Size:         resb 1
;             BSS.Storage.CD.DiskPacket.Reserved:     resb 1
;             BSS.Storage.CD.DiskPacket.Blocks:       resb 2
;             BSS.Storage.CD.DiskPacket.Dest.Offset:  resb 2
;             BSS.Storage.CD.DiskPacket.Dest.Segment: resb 2
;             BSS.Storage.CD.DiskPacket.LBA.Lower:    resb 4
;             BSS.Storage.CD.DiskPacket.LBA.Upper:    resb 4
BSS.End: