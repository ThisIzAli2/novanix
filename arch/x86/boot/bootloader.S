; bootloader.asm
; Assembled with NASM: nasm -f bin bootloader.asm -o bootloader.bin
; This code fits in one 512-byte sector, with boot signature at the end.

[bits 16]                ; 16-bit real mode
[org 0x7c00]             ; BIOS loads bootloader here

start:
    mov si, msg          ; Load pointer to message string
.print_loop:
    lodsb                ; Load byte at [si] into al, increment si
    cmp al, 0
    je .hang             ; If zero (end of string), halt
    mov ah, 0x0e         ; BIOS teletype function
    int 0x10             ; Print character in AL
    jmp .print_loop

.hang:
    cli                  ; Disable interrupts
    hlt                  ; Halt CPU
    jmp .hang            ; Infinite loop

msg db "Hello from bootloader!", 0

; Fill remaining bytes with zeros
times 510 - ($ - $$) db 0

; Boot signature (must be 0x55, 0xAA)
dw 0xAA55
