/**
 * @file types.h
 ** This file is part of AliNix.

**AliNix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**AliNix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with AliNix. If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * @abstraction:
 *  - UACPI util.
*/
#ifndef __ALINIX_KERNEL_UAPI_POWER_TYPES_H
#define __ALINIX_KERNEL_UAPI_POWER_TYPES_H


#include <alinix/types.h>

typedef struct uacpi_object uacpi_object;
struct uacpi_shareable {
    u32 reference_count;
};

typedef union uacpi_object_name {
    char text[4];
    u32 id;
} uacpi_object_name;


typedef struct uacpi_namespace_node {
    struct uacpi_shareable shareable;
    uacpi_object_name name;
    u32 flags;
    uacpi_object *object;
    struct uacpi_namespace_node *parent;
    struct uacpi_namespace_node *child;
    struct uacpi_namespace_node *next;
} uacpi_namespace_node;
typedef struct uacpi_namespace_node uacpi_namespace_node;

typedef void *uacpi_handle;
typedef enum uacpi_status {
    UACPI_STATUS_OK = 0,
    UACPI_STATUS_MAPPING_FAILED = 1,
    UACPI_STATUS_OUT_OF_MEMORY = 2,
    UACPI_STATUS_BAD_CHECKSUM = 3,
    UACPI_STATUS_INVALID_SIGNATURE = 4,
    UACPI_STATUS_INVALID_TABLE_LENGTH = 5,
    UACPI_STATUS_NOT_FOUND = 6,
    UACPI_STATUS_INVALID_ARGUMENT = 7,
    UACPI_STATUS_UNIMPLEMENTED = 8,
    UACPI_STATUS_ALREADY_EXISTS = 9,
    UACPI_STATUS_INTERNAL_ERROR = 10,
    UACPI_STATUS_TYPE_MISMATCH = 11,
    UACPI_STATUS_INIT_LEVEL_MISMATCH = 12,
    UACPI_STATUS_NAMESPACE_NODE_DANGLING = 13,
    UACPI_STATUS_NO_HANDLER = 14,
    UACPI_STATUS_NO_RESOURCE_END_TAG = 15,
    UACPI_STATUS_COMPILED_OUT = 16,
    UACPI_STATUS_HARDWARE_TIMEOUT = 17,

    // All errors that have bytecode-related origin should go here
    UACPI_STATUS_AML_UNDEFINED_REFERENCE = 0x0EFF0000,
    UACPI_STATUS_AML_INVALID_NAMESTRING = 0x0EFF0001,
    UACPI_STATUS_AML_OBJECT_ALREADY_EXISTS = 0x0EFF0002,
    UACPI_STATUS_AML_INVALID_OPCODE = 0x0EFF0003,
    UACPI_STATUS_AML_INCOMPATIBLE_OBJECT_TYPE = 0x0EFF0004,
    UACPI_STATUS_AML_BAD_ENCODING = 0x0EFF0005,
    UACPI_STATUS_AML_OUT_OF_BOUNDS_INDEX = 0x0EFF0006,
    UACPI_STATUS_AML_SYNC_LEVEL_TOO_HIGH = 0x0EFF0007,
    UACPI_STATUS_AML_INVALID_RESOURCE = 0x0EFF0008,
} uacpi_status;


typedef enum uacpi_object_type {
    UACPI_OBJECT_UNINITIALIZED = 0,
    UACPI_OBJECT_INTEGER = 1,
    UACPI_OBJECT_STRING = 2,
    UACPI_OBJECT_BUFFER = 3,
    UACPI_OBJECT_PACKAGE = 4,
    UACPI_OBJECT_FIELD_UNIT = 5,
    UACPI_OBJECT_DEVICE = 6,
    UACPI_OBJECT_EVENT = 7,
    UACPI_OBJECT_METHOD = 8,
    UACPI_OBJECT_MUTEX = 9,
    UACPI_OBJECT_OPERATION_REGION = 10,
    UACPI_OBJECT_POWER_RESOURCE = 11,
    UACPI_OBJECT_PROCESSOR = 12,
    UACPI_OBJECT_THERMAL_ZONE = 13,
    UACPI_OBJECT_BUFFER_FIELD = 14,
    UACPI_OBJECT_DEBUG = 16,

    UACPI_OBJECT_REFERENCE = 20,
    UACPI_OBJECT_BUFFER_INDEX = 21,
    UACPI_OBJECT_MAX_TYPE_VALUE = UACPI_OBJECT_BUFFER_INDEX
} uacpi_object_type;




typedef struct uacpi_buffer {
    struct uacpi_shareable shareable;
    union {
        void *data;
        u8 *byte_data;
        char *text;
    };
    size_t size;
} uacpi_buffer;

typedef struct uacpi_package {
    struct uacpi_shareable shareable;
    uacpi_object **objects;
    size_t count;
} uacpi_package;

typedef struct uacpi_buffer_field {
    uacpi_buffer *backing;
    size_t bit_index;
    u32 bit_length;
    bool force_buffer;
} uacpi_buffer_field;

typedef struct uacpi_buffer_index {
    size_t idx;
    uacpi_buffer *buffer;
} uacpi_buffer_index;

typedef struct uacpi_mutex {
    struct uacpi_shareable shareable;
    uacpi_handle handle;
    uacpi_handle owner;
    u64 depth;
    u8 sync_level;
} uacpi_mutex;

typedef struct uacpi_event {
    struct uacpi_shareable shareable;
    uacpi_handle handle;
} uacpi_event;

typedef enum uacpi_region_op {
    UACPI_REGION_OP_ATTACH = 1,
    UACPI_REGION_OP_READ = 2,
    UACPI_REGION_OP_WRITE = 3,
    UACPI_REGION_OP_DETACH = 4,
} uacpi_region_op;

typedef struct uacpi_region_attach_data {
    void *handler_context;
    uacpi_namespace_node *region_node;
    void *out_region_context;
} uacpi_region_attach_data;

typedef struct uacpi_region_rw_data {
    void *handler_context;
    void *region_context;
    union {
        u64 address;
        u64 offset;
    };
    u64 value;
    u8 byte_width;
} uacpi_region_rw_data;

typedef struct uacpi_region_detach_data {
    void *handler_context;
    void *region_context;
    uacpi_namespace_node *region_node;
} uacpi_region_detach_data;

typedef uacpi_status (*uacpi_region_handler)
    (uacpi_region_op op, uacpi_handle op_data);

typedef struct uacpi_address_space_handler {
    struct uacpi_shareable shareable;
    uacpi_region_handler callback;
    uacpi_handle user_context;
    struct uacpi_address_space_handler *next;
    struct uacpi_operation_region *regions;
    u16 space;
} uacpi_address_space_handler;

typedef uacpi_status (*uacpi_notify_handler)
    (uacpi_handle context, uacpi_namespace_node *node, u64 value);

typedef struct uacpi_device_notify_handler {
    uacpi_notify_handler callback;
    uacpi_handle user_context;
    struct uacpi_device_notify_handler *next;
} uacpi_device_notify_handler;

/*
 * NOTE: These are common object headers.
 * Any changes to these structs must be propagated to all objects.
 * ==============================================================
 * Common for the following objects:
 * - UACPI_OBJECT_OPERATION_REGION
 * - UACPI_OBJECT_PROCESSOR
 * - UACPI_OBJECT_DEVICE
 * - UACPI_OBJECT_THERMAL_ZONE
 */
typedef struct uacpi_address_space_handlers {
    struct uacpi_shareable shareable;
    uacpi_address_space_handler *head;
} uacpi_address_space_handlers;

/*
 * Common for the following objects:
 * - UACPI_OBJECT_PROCESSOR
 * - UACPI_OBJECT_DEVICE
 * - UACPI_OBJECT_THERMAL_ZONE
 */
typedef struct uacpi_handlers {
    struct uacpi_shareable shareable;
    uacpi_address_space_handler *address_space_head;
    uacpi_device_notify_handler *notify_head;
} uacpi_handlers;

typedef enum uacpi_address_space {
    UACPI_ADDRESS_SPACE_SYSTEM_MEMORY = 0,
    UACPI_ADDRESS_SPACE_SYSTEM_IO = 1,
    UACPI_ADDRESS_SPACE_PCI_CONFIG = 2,
    UACPI_ADDRESS_SPACE_EMBEDDED_CONTROLLER = 3,
    UACPI_ADDRESS_SPACE_SMBUS = 4,
    UACPI_ADDRESS_SPACE_SYSTEM_CMOS = 5,
    UACPI_ADDRESS_SPACE_PCI_BAR_TARGET = 6,
    UACPI_ADDRESS_SPACE_IPMI = 7,
    UACPI_ADDRESS_SPACE_GENERAL_PURPOSE_IO = 8,
    UACPI_ADDRESS_SPACE_GENERIC_SERIAL_BUS = 9,
    UACPI_ADDRESS_SPACE_PCC = 0x0A,
    UACPI_ADDRESS_SPACE_PRM = 0x0B,
    UACPI_ADDRESS_SPACE_FFIXEDHW = 0x7F,

    // Internal type
    UACPI_ADDRESS_SPACE_TABLE_DATA = 0xDA1A,
} uacpi_address_space;
const char *uacpi_address_space_to_string(uacpi_address_space space);

// This region has a corresponding _REG method that was succesfully executed
#define UACPI_OP_REGION_STATE_REG_EXECUTED (1 << 0)

// This region was successfully attached to a handler
#define UACPI_OP_REGION_STATE_ATTACHED (1 << 1)

typedef struct uacpi_operation_region {
    struct uacpi_shareable shareable;
    uacpi_address_space_handler *handler;
    uacpi_handle user_context;
    u16 space;
    u8 state_flags;
    u64 offset;
    u64 length;

    // Used to link regions sharing the same handler
    struct uacpi_operation_region *next;
} uacpi_operation_region;

typedef struct uacpi_device {
    struct uacpi_shareable shareable;
    uacpi_address_space_handler *address_space_handlers;
    uacpi_device_notify_handler *notify_handlers;
} uacpi_device;

typedef struct uacpi_processor {
    struct uacpi_shareable shareable;
    uacpi_address_space_handler *address_space_handlers;
    uacpi_device_notify_handler *notify_handlers;
    u8 id;
    u32 block_address;
    u8 block_length;
} uacpi_processor;

typedef struct uacpi_thermal_zone {
    struct uacpi_shareable shareable;
    uacpi_address_space_handler *address_space_handlers;
    uacpi_device_notify_handler *notify_handlers;
} uacpi_thermal_zone;

typedef struct uacpi_power_resource {
    u8 system_level;
    u16 resource_order;
} uacpi_power_resource;

typedef uacpi_status (*uacpi_native_call_handler)(
    uacpi_handle ctx, uacpi_object *retval
);

typedef struct uacpi_control_method {
    struct uacpi_shareable shareable;
    union {
        u8 *code;
        uacpi_native_call_handler handler;
    };
    uacpi_mutex *mutex;
    u32 size;
    u8 sync_level : 4;
    u8 args : 3;
    u8 is_serialized : 1;
    u8 named_objects_persist: 1;
    u8 native_call : 1;
} uacpi_control_method;

typedef enum uacpi_access_type {
    UACPI_ACCESS_TYPE_ANY = 0,
    UACPI_ACCESS_TYPE_BYTE = 1,
    UACPI_ACCESS_TYPE_WORD = 2,
    UACPI_ACCESS_TYPE_DWORD = 3,
    UACPI_ACCESS_TYPE_QWORD = 4,
    UACPI_ACCESS_TYPE_BUFFER = 5,
} uacpi_access_type;

typedef enum uacpi_access_attributes {
    UACPI_ACCESS_ATTRIBUTE_QUICK = 0x02,
    UACPI_ACCESS_ATTRIBUTE_SEND_RECEIVE = 0x04,
    UACPI_ACCESS_ATTRIBUTE_BYTE = 0x06,
    UACPI_ACCESS_ATTRIBUTE_WORD = 0x08,
    UACPI_ACCESS_ATTRIBUTE_BLOCK = 0x0A,
    UACPI_ACCESS_ATTRIBUTE_BYTES = 0x0B,
    UACPI_ACCESS_ATTRIBUTE_PROCESS_CALL = 0x0C,
    UACPI_ACCESS_ATTRIBUTE_BLOCK_PROCESS_CALL = 0x0D,
    UACPI_ACCESS_ATTRIBUTE_RAW_BYTES = 0x0E,
    UACPI_ACCESS_ATTRIBUTE_RAW_PROCESS_BYTES = 0x0F,
} uacpi_access_attributes;

typedef enum uacpi_lock_rule {
    UACPI_LOCK_RULE_NO_LOCK = 0,
    UACPI_LOCK_RULE_LOCK = 1,
} uacpi_lock_rule;

typedef enum uacpi_update_rule {
    UACPI_UPDATE_RULE_PRESERVE = 0,
    UACPI_UPDATE_RULE_WRITE_AS_ONES = 1,
    UACPI_UPDATE_RULE_WRITE_AS_ZEROES = 2,
} uacpi_update_rule;

typedef enum uacpi_field_unit_kind {
    UACPI_FIELD_UNIT_KIND_NORMAL = 0,
    UACPI_FIELD_UNIT_KIND_INDEX = 1,
    UACPI_FIELD_UNIT_KIND_BANK = 2,
} uacpi_field_unit_kind;

typedef struct uacpi_field_unit {
    struct uacpi_shareable shareable;

    union {
        // UACPI_FIELD_UNIT_KIND_NORMAL
        struct {
            uacpi_namespace_node *region;
        };

        // UACPI_FIELD_UNIT_KIND_INDEX
        struct {
            struct uacpi_field_unit *index;
            struct uacpi_field_unit *data;
        };

        // UACPI_FIELD_UNIT_KIND_BANK
        struct {
            uacpi_namespace_node *bank_region;
            struct uacpi_field_unit *bank_selection;
            u64 bank_value;
        };
    };

    uacpi_object *connection;

    u32 byte_offset;
    u32 bit_length;
    u8 bit_offset_within_first_byte;
    u8 access_width_bytes;
    u8 access_length;

    u8 attributes : 4;
    u8 update_rule : 2;
    u8 kind : 2;
    u8 lock_rule : 1;
} uacpi_field_unit;



typedef struct uacpi_args {
    uacpi_object **objects;
    size_t count;
} uacpi_args;


typedef enum uacpi_firmware_request_type {
    UACPI_FIRMWARE_REQUEST_TYPE_BREAKPOINT,
    UACPI_FIRMWARE_REQUEST_TYPE_FATAL,
} uacpi_firmware_request_type;

typedef struct uacpi_firmware_request {
    u8 type;

    union {
        // UACPI_FIRMWARE_REQUEST_BREAKPOINT
        struct {
            // The context of the method currently being executed
            uacpi_handle ctx;
        } breakpoint;

        // UACPI_FIRMWARE_REQUEST_FATAL
        struct {
            u8 type;
            u32 code;
            u64 arg;
        } fatal;
    };
} uacpi_firmware_request;

#define UACPI_INTERRUPT_NOT_HANDLED 0
#define UACPI_INTERRUPT_HANDLED 1
typedef u32 uacpi_interrupt_ret;

typedef uacpi_interrupt_ret (*uacpi_interrupt_handler)(uacpi_handle);

uacpi_object *uacpi_create_object(uacpi_object_type type);

void uacpi_object_ref(uacpi_object *obj);
void uacpi_object_unref(uacpi_object *obj);




#endif  /*__ALINIX_KERNEL_UAPI_POWER_TYPES_H*/