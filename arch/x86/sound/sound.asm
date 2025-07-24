[BITS 16]
[ORG 0x7C00]

start:
    ; Set PIT channel 2 to desired frequency
    mov al, 0xB6            ; Channel 2, LSB/MSB, square wave
    out 0x43, al

    ; Frequency = 1193180 / N
    ; Let's say N = 1193 => Frequency = ~1000Hz (1kHz beep)
    mov ax, 1193
    out 0x42, al            ; Send LSB
    mov al, ah
    out 0x42, al            ; Send MSB

    ; Enable speaker (set bits 0 and 1 of port 0x61)
    in al, 0x61
    or al, 0x03
    out 0x61, al

    ; Delay loop (~1 second)
    mov cx, 0xFFFF
delay:
    loop delay

    ; Turn speaker off (clear bits 0 and 1)
    in al, 0x61
    and al, 0xFC
    out 0x61, al

    ; Infinite loop
    cli
    hlt

times 510-($-$$) db 0
dw 0xAA55
