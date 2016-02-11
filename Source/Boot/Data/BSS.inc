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
BSS:
[SECTION .BSS]
BSS.Video:
    BSS.Video.State:
        BSS.Video.State.StaticTable:            resb 4
        BSS.Video.State.VideoMode:              resb 1
        BSS.Video.State.Display.Columns:        resb 2
        BSS.Video.State.RegenBuffer.Length:     resb 2
        BSS.Video.State.RegenBuffer.Address:    resb 2
        BSS.Video.State.Cursor.Page0:           resb 2
        BSS.Video.State.Cursor.Page1:           resb 2
        BSS.Video.State.Cursor.Page2:           resb 2
        BSS.Video.State.Cursor.Page3:           resb 2
        BSS.Video.State.Cursor.Page4:           resb 2
        BSS.Video.State.Cursor.Page5:           resb 2
        BSS.Video.State.Cursor.Page6:           resb 2
        BSS.Video.State.Cursor.Page7:           resb 2
        BSS.Video.State.Cursor.Type:            resb 2
        BSS.Video.State.ActiveDisplayPage:      resb 1
        BSS.Video.State.CRTCPortAddress:        resb 2
        BSS.Video.State.PortSetting.P03x8:      resb 1
        BSS.Video.State.PortSetting.P03x9:      resb 1
        BSS.Video.State.Display.Rows:           resb 1
        BSS.Video.State.BytesPerCharacter:      resb 2
        BSS.Video.State.Display.Code:           resb 1
        BSS.Video.State.Display.Alternate.Code: resb 1
        BSS.Video.State.Display.Colors:         resb 2
        BSS.Video.State.Display.Pages:          resb 1
        BSS.Video.State.Display.ScanLines:      resb 1
        BSS.Video.State.Reserved:               resb 21
    BSS.Video.DisplayPage:                      resb 1
    BSS.Video.Flags:                            resb 2
BSS.Serial:
    BSS.Serial.Flags:                           resb 2
