#ifndef __OLD_COMM_NOVANIX_HPP
#define __OLD_COMM_NOVANIX_HPP

// Simulated virtual communication line (1 = idle high, 0 = low)
volatile int virtual_line = 1;

// Bit timing in milliseconds
#define BIT_DURATION_MS 100
// Forward declarations - you must implement or link these in your kernel
extern void printk(const char* fmt, ...);
extern void putchar(char c);
extern void msleep(int ms);
extern void start_kernel_thread(void (*func)(void*), void* arg);

// Send one bit on the virtual line and wait BIT_DURATION_MS
inline void send_bit(int bit) {
    virtual_line = (bit != 0) ? 1 : 0;
    msleep(BIT_DURATION_MS);
}

// Send a full byte: 1 start bit (0), 8 data bits (LSB first), 1 stop bit (1)
void send_byte(char b) {
    send_bit(0); // start bit
    for (int i = 0; i < 8; i++) {
        send_bit((b >> i) & 1);
    }
    send_bit(1); // stop bit
    msleep(BIT_DURATION_MS);
}

// Receive one byte by waiting for start bit and sampling bits at BIT_DURATION_MS intervals
char receive_byte() {
    // Wait for start bit (line goes low)
    while (virtual_line != 0) {
        msleep(1);
    }
    msleep(BIT_DURATION_MS / 2); // Wait half bit time for stable sampling

    char result = 0;
    for (int i = 0; i < 8; i++) {
        msleep(BIT_DURATION_MS);
        if (virtual_line != 0)
            result |= (1 << i);
    }
    msleep(BIT_DURATION_MS); // Wait for stop bit
    return result;
}

// Send a null-terminated string byte by byte
void send_string(const char* str) {
    for (; *str != 0; str++) {
        send_byte(*str);
    }
}

// Thread function: receives bytes and prints them
void receiver_thread(void* arg) {
    (void)arg;
    printk("[OldComm] Receiver started...\n");
    while (true) {
        char c = receive_byte();
        putchar(c);
        if (c == '\n') {
            printk("\n");
        }
    }
}

// Thread function: sends a fixed string message
void sender_thread(void* arg) {
    const char* msg = (const char*)arg;
    printk("[OldComm] Sender started...\n");
    msleep(500); // slight delay before sending
    send_string(msg);
    printk("[OldComm] Sender finished sending message.\n");
}

// Initialize old communication by launching sender and receiver threads
inline void oldcomm_init() {
    static const char message[] = "Hello from Novanix oldcomm!\n";
    start_kernel_thread(receiver_thread, 0);
    start_kernel_thread(sender_thread, (void*)message);
}

#endif // __OLD_COMM_NOVANIX_HPP
