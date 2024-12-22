#ifndef DRIVER_H
#define  DRIVER_H

#include <heisen/typing.h>

#define MAX_DRIVER_FUNCTION_COUNT 32
struct driver;
struct device;
typedef struct {
    void (*recieve_notification)(uintptr_t key, uintptr_t val);
    int (*on_start)();
    int (*on_stop)();
    int (*init_with_dev)(struct device* device);
} driver_system_funcs_t;

struct driver_desc {
    int type;
    uint32_t flags;
    uint32_t listened_device_mask;
    uint32_t listened_driver_mask;
    void * functions[MAX_DRIVER_FUNCTION_COUNT];

};


#endif // DRIVER_H