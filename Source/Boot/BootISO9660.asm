[org 0x7c00]
[bits 16]

Entry:
    jmp 0x0000:Start

times 8-($-$$) db 0
BootTable:
    BootTable.PrimaryDescriptor:        resd 1
    BootTable.BootFileLocation:         resd 1
    BootTable.BootFileLength:           resd 1
    BootTable.Checksum:                 resd 1
    BootTable.Reserved:                 resb 40

%include "AssemblyFunctions/IAPX86/A20/A20.inc"
%include "AssemblyFunctions/IAPX86/CPU/CPU.inc"
%include "AssemblyFunctions/IAPX86/Error/Error.inc"
%include "AssemblyFunctions/IAPX86/IO/IO.inc"
%include "Data/Data.inc"
%include "Data/BSS.inc"

[SECTION .TEXT]
[CPU X64]

GDT:
GDT.Null:
    dd 0x00000000
    dd 0x00000000
GDT.Code:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00
GDT.Data:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00
GDT.End:
    dw GDT.End - GDT - 1
    dd GDT

EnableGDT:
    cli
    pusha
    lgdt [GDT.End]
    sti
    popa
    ret

Start:
    ; We need to initialize our segment registers and the stack so that we
    ; don't accidentally access the wrong data or code and triple fault.
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov sp, 0x7c00

    ; Now we zero out the BSS section of our bootloader so that the bootloader
    ; can store data and access it with a known initial state.
;    pusha
;    cld
    mov cx, (BSS.End - BSS)
    mov di, BSS
    cld
    rep stosb
;    popa

    ; Next we initialize IO for the bootloader and clear the screen of any
    ; initial input.
    call IAPX86.IO.Init
    call IAPX86.IO.Clear

    ; Now we print out the splash information, consisting of the title of the
    ; project as well as version information and copyright information.
    mov si, Data.Message.Init.Splash001
    call IAPX86.IO.Print.String
    mov si, Data.Message.Init.Splash002
    call IAPX86.IO.Print.String
    mov si, Data.Message.NewLine
    call IAPX86.IO.Print.String
    mov si, Data.Message.Init.Splash003
    call IAPX86.IO.Print.String
    mov si, Data.Message.Init.Splash004
    call IAPX86.IO.Print.String

    call IAPX86.A20.Enable
    call IAPX86.CPU.Check.AMD64
    jc Failure
    call EnableGDT

;     mov ax, 0x4500
;     mov dl, [DriveNumber]
;     int 0x13

;     mov eax, 17
;     mov di, 0x4000
; LoadBRVD:
;     call IAPX86.Storage.CD.LoadSector
;     cmp byte [di], 0x00
;     je FoundBRVD
;     inc eax
;     cmp byte [di], 255
;     je Failure
;     cmp eax, 32+17
;     jb LoadBRVD

; FoundBRVD:
;     cmp byte [di+0x001], 'C'
;     jne Failure
;     cmp dword [di+0x002], 'D001'
;     jne Failure
;     cmp byte [di+0x007], 'E'
;     jne Failure
;     cmp dword [di+0x008], 'L TO'
;     jne Failure
;     cmp dword [di+0x00C], 'RITO'
;     jne Failure
;     cmp dword [di+0x010], ' SPE'
;     jne Failure
;     cmp dword [di+0x014], 'CIFI'
;     jne Failure
;     cmp dword [di+0x018], 'CATI'
;     jne Failure
;     cmp word [di+0x01C], 'ON'
;     jne Failure

;     mov eax, [di+0x47]
;     call IAPX86.Storage.CD.LoadSector
;     lea bp, [di+2048]

; ;    cmp word [di], 0x0001
; ;    jne Failure
; ;    cmp word [di+0x01E], 0xAA55
; ;    jne Failure

    

    cli
    mov eax, cr0
    or al, 1
    mov cr0, eax

    jmp 0x08:PStart

Failure:
    mov eax, 0x000b8000
    mov [eax], word 0x4e4e
    cli
    hlt

[bits 32]
PStart:
    mov ax, 0x10
    mov ds, ax
    ;mov es, ax
    ;mov fs, ax
    ;mov gs, ax
    ;mov ss, ax
    ;mov esp, 0x9000

;    mov eax, 0x000b8000
;    mov ebx, 0xdeadbeef
;    mov [eax], word 0x3f3f

    mov edi, 0x1000
    mov cr3, edi
    xor eax, eax
    mov ecx, 4096
    rep stosd
    mov edi, cr3

    mov dword [edi], 0x2003
    add edi, 0x1000
    mov dword [edi], 0x3003
    add edi, 0x1000
    mov dword [edi], 0x4003
    add edi, 0x1000

    mov ebx, 0x00000003
    mov ecx, 512

SetEntry:
    mov dword [edi], ebx
    add ebx, 0x1000
    add edi, 8
    loop SetEntry

    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    lgdt [GDT64.Pointer]
    jmp GDT64.Code:LStart

    cli
    hlt

GDT64:
    GDT64.Null: equ $ - GDT64
        dw 0x0000
        dw 0x0000
        db 0x00
        db 0x00
        db 0x00
        db 0x00
    GDT64.Code: equ $ - GDT64
        dw 0x0000
        dw 0x0000
        db 0x00
        db 10011010b
        db 00100000b
        db 0x00
    GDT64.Data: equ $ - GDT64
        dw 0x0000
        dw 0x0000
        db 0x00
        db 10010010b
        db 00000000b
        db 0x00
    GDT64.Pointer:
        dw $ - GDT64 - 1
        dq GDT64

[BITS 64]
LStart:
    cli
    mov ax, GDT64.Data
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ; mov edi, 0xb8000
    ; mov rax, 0x1f201f201f201f20
    ; mov ecx, 500
    ; rep stosq

LHalt:
    hlt
    jmp LHalt

;     ; Check for 64-Bit capable CPU
;     pushfd
;     pop eax
;     mov ecx, eax
;     xor eax, 0x200000
;     push eax
;     popfd
;     pushfd
;     pop eax
;     xor eax, ecx
;     shr eax, 0x15
;     and eax, 0x01
;     push ecx
;     popfd
;     test eax, eax
;     jz Failure
;     mov eax, 0x80000000
;     cpuid
;     cmp eax, 0x80000001
;     jb Failure
;     mov eax, 0x80000001
;     cpuid
;     test edx, 1 << 29

;     jz Failure

;     mov edi, 0x1000
;     mov cr3, edi
;     mov ecx, 0x1000
;     xor eax, eax
;     cld
;     rep stosd
;     mov edi, cr3
;     mov dword [edi], 0x2003
;     add edi, 0x1000
;     mov dword [edi], 0x3003
;     add edi, 0x1000
;     mov dword [edi], 0x4003
;     add edi, 0x1000
;     mov ebx, 0x00000003
;     mov ecx, 0x00000200
    
; LoopPages:
;     mov dword [edi], ebx
;     add ebx, 0x1000
;     add edi, 8
;     loop LoopPages
    
;     mov al, 0xFF
;     out 0xA1, al
;     out 0x21, al
;     nop
;     nop
;     lidt [IDT]

;     mov eax, cr4
;     or eax, 1 << 5
;     mov cr4, eax
;     mov ecx, 0xC0000080
;     rdmsr
;     or eax, 0x00000100
;     wrmsr
;     mov eax, cr0
;     or ebx, 0x80000001
;     mov cr0, eax

;     lgdt [GDT.Ptr]
;     jmp 0x0008:LongStart

; Failure:
;     mov eax, [0xb8000]
;     mov [eax], word 0x3f3f
;     cli
;     hlt
;     jmp Failure

; IDT:
;     .Length: dw 0
;     .Base dd 0

; GDT:
;     GDT.Null:
;         dq 0x0000000000000000
;     GDT.Code:
;         dq 0x00209A0000000000
;     GDT.Data:
;         dq 0x0000920000000000
;     GDT.Ptr:
;         dw $ - GDT - 1
;         dd GDT

; [bits 64]
; LongStart:
;     mov ax, 0x0010
;     mov ds, ax
;     mov es, ax
;     mov fs, ax
;     mov gs, ax
;     mov ss, ax

;     mov rax, 0xB8000
;     mov [rax], word 0x3f3f

;     mov edi, 0xB8000
;     mov rcx, 500
;     mov rax, 0x1F201f201f201f20
;     rep stosq
    
; LongHalt:
;     hlt
;     jmp LongHalt