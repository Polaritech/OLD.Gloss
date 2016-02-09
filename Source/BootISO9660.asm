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

Start:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov sp, 0x7c00

    mov eax, 0xb8000
    mov [eax], word 0x1f2b

    cli
    hlt