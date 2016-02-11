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
[CPU 8086]

; The following function is located in the .TEXT section of the executable.
[SECTION .TEXT]

; Checks the A20 Line status by observing if memory wraps around at 1 MiB.
IAPX86.A20.Check:
    ; This function checks the status of the A20 Line by observing the effect
    ; of writing a byte value at the edge of memory. If the word wraps around
    ; to the start of memory, then the A20 Line is disabled. We start by
    ; storing some state.
    push ax
    push ds
    push es
    push di
    push si

    ; Next we disable interrupts. If memory does wrap around in this function,
    ; then (very) bad things will happen if a CPU interrupt occurs, as the
    ; start of memory on an x86 is the location of the Real-Mode IVT (Interrupt
    ; Vector Table).
    cli

    ; Next we set two segment registers, the data segment register and the
    ; extra segment register, to 0x0000 and 0xffff, respectively. We do this
    ; since we will soon want to access the first byte of memory and the first
    ; byte of memory after 1 MiB of total memory.
    xor ax, ax
    mov es, ax
    not ax
    mov ds, ax

    ; Next we set two index registers, the destination index register and the
    ; source index register, to 0x0500 and 0x0510, respectively. These
    ; registers have values that are a total of 16 bytes apart, which happens
    ; to be the values required to wrap around on machines without the A20 Line
    ; enabled (in conjunction with the segment registers). Hence, when the A20
    ; Line is disabled, the memory location 0x0000:0x0500 is the same as the
    ; memory location 0xffff:0x0510.
    mov di, 0x0500
    mov si, 0x0510

    ; We now store the current bytes at our test memory locations. We do this
    ; because, as stated above, we don't want to mess up the Real-Mode IVT. At
    ; this point in the bootloader, we will still need BIOS interrupts.
    mov al, [es:di]
    push ax
    mov al, [ds:si]
    push ax

    ; Now we write two distinct bytes to both memory locations. This allows us
    ; to check to see if, when we wrote the second value, that the first value
    ; was overwritten. If this is the case, then our memory wraps around, and
    ; the A20 Line is not enabled. If it doesn't overwrite the first value,
    ; then the A20 Line is enabled.
    mov byte [es:di], 0x00
    mov byte [ds:si], 0xff
    cmp byte [es:di], 0xff

    ; Now we restore the original values that were at the memory locations. We
    ; don't have to worry about corrupting the result of the previous
    ; comparison, as none of the instructions that we execute right now affect
    ; the FLAGS register.
    pop ax
    mov [ds:si], al
    pop ax
    mov [es:di], al

    ; Now we set a status value by using the carry flag. If memory did not wrap
    ; around, then we clear the carry flag. If it did wrap around, then we set
    ; the carry flag.
    clc
    je IAPX86.A20.Check.Wrap.Exit
    stc

    IAPX86.A20.Check.Wrap.Exit:
        ; Now we can re-enable interrupts, as the Real-Mode IVT was returned to
        ; normal.
        sti

        ; We finally reset all of the registers we used back to their previous
        ; values and return to the calling function.
        pop si
        pop di
        pop es
        pop ds
        pop ax
        ret