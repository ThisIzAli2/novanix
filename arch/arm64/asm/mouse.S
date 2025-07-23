.global mouse_init
.global mouse_read
.global mouse_data

.section .text
.align 4

// Mouse base address
.equ MOUSE_BASE,     0x10001000
.equ MOUSE_STATUS,   MOUSE_BASE
.equ MOUSE_X,        MOUSE_BASE + 4
.equ MOUSE_Y,        MOUSE_BASE + 8
.equ MOUSE_BTN,      MOUSE_BASE + 12

// Output structure
.section .bss
.align 4
mouse_data:
    .skip 12   // x (4 bytes), y (4 bytes), buttons (4 bytes)

.section .text

// Mouse init (stub)
mouse_init:
    // Normally you'd configure the controller here
    ret

// Mouse read (polls MMIO and stores movement/buttons)
mouse_read:
    // Read status
    ldr x1, =MOUSE_STATUS
    ldr w2, [x1]

    // Check if data available (bit 0)
    tst w2, #1
    beq .no_data

    // Read X
    ldr x1, =MOUSE_X
    ldr w3, [x1]

    // Read Y
    ldr x1, =MOUSE_Y
    ldr w4, [x1]

    // Read Button
    ldr x1, =MOUSE_BTN
    ldr w5, [x1]

    // Store to mouse_data
    ldr x0, =mouse_data
    str w3, [x0]        // x
    str w4, [x0, #4]     // y
    str w5, [x0, #8]     // buttons

.no_data:
    ret
