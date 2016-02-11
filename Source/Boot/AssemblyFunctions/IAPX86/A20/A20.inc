;=============================================================================;
; GLOSS - Generic Loader for Operating System Software                        ;
; An extensible and configurable bootloader.                                  ;
;-----------------------------------------------------------------------------;
; Copyright (C) 2013-2016 ~ Adrian J. Collado       [acollado@polaritech.com] ;
; Copyright (C) 2015-2016 ~ Polaritech, Inc.         [https://polaritech.com] ;
; All Rights Reserved                                                         ;
;=============================================================================;

%ifndef ASSEMBLYFUNCTIONS_IAPX86_A20_A20INC
%define ASSEMBLYFUNCTIONS_IAPX86_A20_A20INC

%include "Check.inc"
%include "Toggle.inc"
%include "Disable.inc"
%include "Enable.inc"
%include "Toggle.BIOS.inc"
%include "Toggle.Fast.inc"
%include "Toggle.PS2.inc"

Data.A20Status: db 0x00

%endif ;ASSEMBLYFUNCTIONS_IAPX86_A20_A20INC