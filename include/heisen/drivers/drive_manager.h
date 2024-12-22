#ifndef _HEISEN_DRIVE_MANAGER_H
#define _HEISEN_DRIVE_MANAGER_H

#define MAX_DRIVERS_COUNT 256
#define MAX_DEVICE_COUNT 64


#define DEVMAN_FUNC_NOTIFY 0x0
#define DEVMAN_FUNC_DEVICE_START 0x1
#define DEVMAN_FUNC_DRIVER_START 0x1
#define DEVMAN_FUNC_DRIVER_EMIT_DRIVER 0x1
#define DEVMAN_FUNC_DRIVER_EMIT_DEVICE 0x2

#define DEFAULT_DRIVER_PRIV (100)


typedef void (*driver_installation_func_t)();

#define devman_register_driver_installation_order(func, N)                          \
    static driver_installation_func_t registered_driver_##func                      \
        __attribute__((used)) __attribute__((section(".driver_init_sections." #N))) \
        = func

#define devman_register_driver_installation(func) devman_register_driver_installation_order(func, DEFAULT_DRIVER_PRIV)


extern driver_t

#endif // _HEISEN_DRIVE_MANAGER_H