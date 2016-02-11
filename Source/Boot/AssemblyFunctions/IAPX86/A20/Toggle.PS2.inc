;=============================================================================;
; GLOSS - Generic Loader for Operating System Software                        ;
; An extensible and configurable bootloader.                                  ;
;-----------------------------------------------------------------------------;
; Copyright (C) 2013-2016 ~ Adrian J. Collado       [acollado@polaritech.com] ;
; Copyright (C) 2015-2016 ~ Polaritech, Inc.         [https://polaritech.com] ;
; All Rights Reserved                                                         ;
;=============================================================================;

; Before starting the toggle function, a bit about the 8042 PS/2 controller
; should be discussed. The 8042 PS/2 controller is the controller used for the
; keyboard and mouse on IBM PC-AT compatible computers. Back when hardware was
; limited and the IBM PC-AT was being designed, it was found that the 8042 chip
; had an extra pin that wasn't being used. The designers, in their infinte
; wisdom, chose that pin for controlling the A20 line memory extensions (they
; also added a method to reset the entire computer through another pin). Since
; the x86 architecture is notorious for backwards compatibility, we still can
; toggle the A20 line status using the 8042 PS/2 controller.

; Nowadays, the functions of the 8042 PS/2 controller are integrated into a
; device called the Advanced

; This code is assembled to be run in 16-bit mode on any CPU that is an 8086 or
; newer. This basically means that any CPU that can run x86 code can run the
; following code.
[BITS 16]
[CPU 8086]

; This function appears as executable code inside of a binary file.
[SECTION .TEXT]

; Toggles the A20 line using the 8042 PS/2 controller.
IAPX86.A20.Toggle.PS2:
    ; When we modify the A20 line, rather than explicitly enabling or disabling
    ; the A20 line, it is actually much easier, faster, and provides more code
    ; reusability (and thus saves space in our binary) if we toggle the current
    ; value, as enabling and disabling are virtually the same. When using this
    ; method, the first thing we have to do is store some state, and disable
    ; interrupts.
    push ax
    cli

    ; For this method of toggling the A20 line, we will be performing direct
    ; hardware programming. The first thing we do is disable the first PS/2
    ; port by issuing a command to the PS/2 controller through its command
    ; port, 0x64.
    call IAPX86.A20.Toggle.PS2.Writable
    mov al, 0xad
    out 0x64, al

    ; Next we issue a command to read the PS/2 controller's output port. We do
    ; this by, again, issuing a command through its command port.
    call IAPX86.A20.Toggle.PS2.Writable
    mov al, 0xd0
    out 0x64, al
    
    ; Next we read the output port of the PS/2 controller.
    call IAPX86.A20.Toggle.PS2.Readable
    in al, 0x60
    push ax

    ; Now we issue a command to write to the PS/2 controller's output port. We
    ; do this by issuing yet another command through the command port.
    call IAPX86.A20.Toggle.PS2.Writable
    mov al, 0xd1
    out 0x64, al

    ; Now we write our updated A20 line value to the PS/2 controller's output
    ; port. What we do is toggle the A20 line enabled bit of the PS/2
    ; controller data register that we recieved when we read the byte value
    ; from the PS/2 controller.
    call IAPX86.A20.Toggle.PS2.Writable
    pop ax
    xor ax, 0x02
    out 0x60, al

    ; Finally, we wait until the PS/2 controller's input buffer is clear, and
    ; then we finally exit (after, of course, re-enabling interrupts and
    ; restoring state).
    call IAPX86.A20.Toggle.PS2.Writable
    sti
    pop ax
    ret

    ; This sub-function is a simple polling (also known as looping) function
    ; that just tests if the PS/2 controller's input buffer is clear. When the
    ; buffer is clear, we are able to send commands or data to the PS/2
    ; controller.
    IAPX86.A20.Toggle.PS2.Writable:
        in al, 0x64
        test al, 0x02
        jnz IAPX86.A20.Toggle.PS2.Writable
        ret

    ; This sub-function is another simple polling function that tests if the
    ; PS/2 controller's output buffer is full. When the buffer is full, we are
    ; able to read data from the PS/2 controller.
    IAPX86.A20.Toggle.PS2.Readable:
        in al, 0x64
        test al, 0x01
        jz IAPX86.A20.Toggle.PS2.Readable
        ret