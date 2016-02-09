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

    xor bx, bx
    mov ah, 0x0e
    mov al, 'A'
    int 0x10
    ;mov ax, 0x1f2b
    ;mov [0xb8000], ax

    cli
    hlt