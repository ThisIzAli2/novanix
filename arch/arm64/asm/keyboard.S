.global keyboard_init
.global keyboard_read
.global key_data

.section .text
.align 4

// MMIO addresses for fictional keyboard
.equ KEYBOARD_BASE,    0x10002000
.equ KB_STATUS,        KEYBOARD_BASE
.equ KB_KEYCODE,       KEYBOARD_BASE + 4
.equ KB_MODIFIERS,     KEYBOARD_BASE + 8

// Data output area
.section .bss
.align 4
key_data:
    .skip 8   // keycode (4 bytes), modifiers (4 bytes)

.section .text

// Stub for initialization
keyboard_init:
    // In real code, you'd configure interrupts or controller here
    ret

// Reads one key if available
keyboard_read:
    // Load status register
    ldr x1, =KB_STATUS
    ldr w2, [x1]
    tst w2, #1          // Check if key is available (bit 0 set)
    beq .no_key

    // Read keycode
    ldr x1, =KB_KEYCODE
    ldr w3, [x1]

    // Read modifiers (Shift, Ctrl, etc.)
    ldr x1, =KB_MODIFIERS
    ldr w4, [x1]

    // Store into key_data
    ldr x0, =key_data
    str w3, [x0]        // Store keycode
    str w4, [x0, #4]    // Store modifiers

.no_key:
    ret
