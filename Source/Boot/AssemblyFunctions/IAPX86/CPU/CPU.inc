;=============================================================================;
; GLOSS - Generic Loader for Operating System Software                        ;
; An extensible and configurable bootloader.                                  ;
;-----------------------------------------------------------------------------;
; Copyright (C) 2013-2016 ~ Adrian J. Collado       [acollado@polaritech.com] ;
; Copyright (C) 2015-2016 ~ Polaritech, Inc.         [https://polaritech.com] ;
; All Rights Reserved                                                         ;
;=============================================================================;

%ifndef ASSEMBLYFUNCTIONS_IAPX86_CPU_CPUINC
%define ASSEMBLYFUNCTIONS_IAPX86_CPU_CPUINC

%define CPUSTR_AMDK5 "AMDisbetter!"
%define CPUSTR_AMD "AuthenticAMD"
%define CPUSTR_CENTAUR "CentaurHauls"
%define CPUSTR_CYRIX "CyrixInstead"
%define CPUSTR_INTEL "GenuineIntel"
%define CPUSTR_TRANSMETA "TransmetaCPU"
%define CPUSTR_TRANSMETAX86 "GenuineTMx86"
%define CPUSTR_NATIONAL "Geode by NSC"
%define CPUSTR_NEXGEN "NexGenDriven"
%define CPUSTR_RISE "RiseRiseRise"
%define CPUSTR_SIS "SiS SiS SiS"
%define CPUSTR_UMC "UMC UMC UMC"
%define CPUSTR_VIA "VIA VIA VIA"
%define CPUSTR_VORTEX "Vortex86 SoC"
%define CPUSTR_KVM "KVMKVMKVM"
%define CPUSTR_HYPERV "Microsoft Hv"
%define CPUSTR_PARALLELS " lrpepyh vr"
%define CPUSTR_VMWARE "VMwareVMware"
%define CPUSTR_XEN "XenVMMXenVMM"

%define CPUFEAT_FPU     1 << 0
%define CPUFEAT_VME     1 << 1
%define CPUFEAT_DE      1 << 2
%define CPUFEAT_PSE     1 << 3
%define CPUFEAT_TSC     1 << 4
%define CPUFEAT_MSR     1 << 5
%define CPUFEAT_PAE     1 << 6
%define CPUFEAT_MCE     1 << 7
%define CPUFEAT_CX8     1 << 8
%define CPUFEAT_APIC    1 << 9

; IGNORE ABOVE - WILL CHANGE TO DIFFERENT SECTION

%include "Check.AMD64.inc"

%endif ;ASSEMBLYFUNCTIONS_IAPX86_CPU_CPUINC