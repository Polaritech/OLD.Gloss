;=============================================================================;
; GLOSS - Generic Loader for Operating System Software                        ;
; An extensible and configurable bootloader.                                  ;
;-----------------------------------------------------------------------------;
; Copyright (C) 2013-2016 ~ Adrian J. Collado       [acollado@polaritech.com] ;
; Copyright (C) 2015-2016 ~ Polaritech, Inc.         [https://polaritech.com] ;
; All Rights Reserved                                                         ;
;=============================================================================;

%ifndef ASSEMBLYFUNCTIONS_IAPX86_IO_IOINC
%define ASSEMBLYFUNCTIONS_IAPX86_IO_IOINC

%include "Serial/Init.inc"
%include "Serial/Print.inc"
%include "Video/Init.inc"
%include "Video/Print.inc"

%include "Clear.inc"
%include "Init.inc"
%include "Print.Char.inc"
%include "Print.String.inc"

%endif ;ASSEMBLYFUNCTIONS_IAPX86_A20_A20INC