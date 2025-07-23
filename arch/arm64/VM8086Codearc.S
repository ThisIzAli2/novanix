.global VM86CodeStart
.global VM86CodeEnd
.global Int86
.global diskInfo

.section .text
.align 4

VM86CodeStart:

// This simulates `Int86` behavior
Int86:
    // Simulate loading registers from fixed memory
    ldr w0, =0x8000
    ldrh w1, [w0]       // ax
    ldrh w2, [w0, #2]   // bx
    ldrh w3, [w0, #4]   // cx
    ldrh w4, [w0, #6]   // dx
    ldrh w5, [w0, #8]   // di

    // Here you would simulate the `int n` behavior
    // Since ARM has no BIOS, you'd jump to handler or emulate logic

    // Simulate saving registers back
    strh w1, [w0]       // ax
    strh w2, [w0, #2]   // bx
    strh w3, [w0, #4]   // cx
    strh w4, [w0, #6]   // dx
    strh w5, [w0, #8]   // di

    // Simulate return to kernel (just branch somewhere or call system handler)
    b EndHandler

// This simulates `diskInfo` logic
diskInfo:
    // w0 = drive number (simulate input)
    // Simulate 0x13/0x48 disk info function
    // In real ARM64 firmware, you'd call into UEFI or a disk driver
    ldr w1, =0x7000
    mov w2, 0x42
    strh w2, [w1]

    // Simulate success/failure condition
    // On error:
    // mov w2, 0
    // strh w2, [w1]

    b EndHandler

EndHandler:
    // Exit or return to kernel logic
    ret

VM86CodeEnd:
