#ifndef __OLD_COMM_NOVANIX_HPP
#define __OLD_COMM_NOVANIX_HPP

#include <common/init.hpp>
#include <charstr.hpp>
// Emulated line to simulate transmission
int comm_line = 1;

// Simple wait loop for timing (CPU stall)
void delay_cycles(int count) {
    while (count-- > 0) {
        __asm__ __volatile__("nop");
    }
}

// Send one bit
void comm_send_bit(int bit) {
    comm_line = (bit != 0) ? 1 : 0;
    delay_cycles(1000000);  // Adjust for timing
}

// Read one bit
int comm_read_bit() {
    delay_cycles(1000000);  // Wait before reading
    return comm_line;
}

// Send byte: 1 start bit, 8 data bits, 1 stop bit
void comm_send_byte(char ch) {
    comm_send_bit(0);  // Start bit

    for (int i = 0; i < 8; ++i) {
        comm_send_bit((ch >> i) & 1);
    }

    comm_send_bit(1);  // Stop bit
    delay_cycles(1000000);  // Extra stop time
}

// Read byte: wait for start bit and read data
char comm_read_byte() {
    while (comm_line != 0);  // Wait for start bit

    delay_cycles(500000);  // Align to center of bit

    char result = 0;
    for (int i = 0; i < 8; ++i) {
        result |= (comm_read_bit() << i);
    }

    comm_read_bit();  // Read stop bit
    return result;
}

// Send string over line
void comm_send_string(const char* str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        comm_send_byte(str[i]);
    }
}

// Receive and print string
void comm_receive_n_print(int count) {
    for (int i = 0; i < count; ++i) {
        char c = comm_read_byte();
        char output[2] = {c, '\0'};
        Novanix::system::printk(Novanix::system::VGA_COLOR_GREEN, output, 0);
    }
}

// Manually called in cmdline with "comm-send" or "comm-recv"
void comm_command_handler(const char* full_cmd) {
    if (cmd_cmp(full_cmd, "comm-send") == 0) {
        comm_send_string("Hello from Novanix!\n");
        Novanix::system::printk(Novanix::system::VGA_COLOR_CYAN, "[Sent old-style message]\n", 1);
    } else if (cmd_cmp(full_cmd, "comm-recv") == 0) {
        Novanix::system::printk(Novanix::system::VGA_COLOR_CYAN, "[Waiting for message...]\n", 1);
        comm_receive_n_print(20);  // Adjust character count
        Novanix::system::printk(Novanix::system::VGA_COLOR_CYAN, "\n[End of message]\n", 1);
    }
}

#endif // __OLD_COMM_NOVANIX_HPP
