#ifndef __ALINIX_KERNEL_SYSTEM_DRIVERS_HID_PARSER_H
#define __ALINIX_KERNEL_SYSTEM_DRIVERS_HID_PARSER_H

#include <alinix/types.h>

enum HID_PAGE_USAGE {
    GEN_DESKTOP = 1, BUTTON = 9,
};

enum HID_USAGE {
    POINTER = 1, MOUSE,
    POINTER_X = 0x30, POINTER_Y, POINTER_WHEEL = 0x38,
    NOTHING = 0xFF
};

// Defining the useful macros for parsing data from USB report descriptor

#define BUTTON_LEFT    0
#define BUTTON_RIGHT   1
#define BUTTON_MIDDLE  2

#define PATH_SIZE               10 // maximum depth for Path
#define USAGE_TAB_SIZE          50 // Size of usage stack
#define MAX_REPORT             300 // Including FEATURE, INPUT and OUTPUT

#define SIZE_0                0x00
#define SIZE_1                0x01
#define SIZE_2                0x02
#define SIZE_4                0x03
#define SIZE_MASK             0x03
                        
#define TYPE_MAIN             0x00
#define TYPE_GLOBAL           0x04
#define TYPE_LOCAL            0x08
#define TYPE_MASK             0xC0

#define ITEM_MASK             0xFC
#define ITEM_UPAGE            0x04
#define ITEM_USAGE            0x08  // local item
#define ITEM_LOG_MIN          0x14
#define ITEM_USAGE_MIN        0x18  // local item
#define ITEM_LOG_MAX          0x24
#define ITEM_USAGE_MAX        0x28  // local item
#define ITEM_PHY_MIN          0x34
#define ITEM_PHY_MAX          0x44
#define ITEM_UNIT_EXP         0x54
#define ITEM_UNIT             0x64
#define ITEM_REP_SIZE         0x74
#define ITEM_STRING           0x78  // local item?
#define ITEM_REP_ID           0x84
#define ITEM_REP_COUNT        0x94

#define ITEM_COLLECTION       0xA0
#define ITEM_END_COLLECTION   0xC0
#define ITEM_FEATURE          0xB0
#define ITEM_INPUT            0x80
#define ITEM_OUTPUT           0x90

// Attribute Flags
#define ATTR_DATA_CST         0x01
#define ATTR_NVOL_VOL         0x80

// Describe a HID Path point 
struct HID_NODE {
    uint16_t u_page;
    uint16_t usage;
};

// Describe a HID Path
struct HID_PATH {
    int    size;                      // HID Path size
    struct HID_NODE node[PATH_SIZE];  // HID Path
};
struct HID_DATA {
    uint32_t value;     // HID Object Value
    struct HID_PATH path;       // HID Path
    
    uint8_t  report_id; // Report ID, (from incoming report) ???
    int    report_count;        // count of reports for this usage type
    int    offset;              // Offset of data in report
    int    size;                // Size of data in bits
                                
    uint8_t  type;      // Type : FEATURE / INPUT / OUTPUT
    uint8_t  attribute; // Report field attribute (2 = (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position))
                                //                        (6 = (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position))
    uint8_t unit;       // HID Unit
    uint8_t unit_exp;   // Unit exponent
    
    int    log_min;             // Logical Min
    int    log_max;             // Logical Max
    int    phy_min;             // Physical Min
    int    phy_max;             // Physical Max
};


static const uint8_t *report_desc;              // Store Report Descriptor
static int    report_desc_size;             // Size of Report Descriptor
static int    pos;                          // Store current pos in descriptor
static uint8_t  item;                         // Store current Item
static uint32_t value;                        // Store current Value

static struct HID_DATA data;                  // Store current environment

static int    offset_table[MAX_REPORT][3];  // Store ID, type & offset of report
static int    report_count;                 // Store Report Count
static int    count;                        // Store local report count

static uint16_t u_page;                       // Global UPage
static struct HID_NODE usage_table[USAGE_TAB_SIZE]; // Usage stack
static int    usage_size;                   // Design number of usage used
static int    usage_min;
static int    usage_max;

static int    cnt_object;                   // Count objects in Report Descriptor
static int    cnt_report;                   // Count reports in Report Descriptor
static bool Parse(struct HID_DATA* data);
static void Reset();
static bool FindObject(struct HID_DATA* data);
static int* GetReportOffset(const uint8_t report_id, const uint8_t report_type);

#endif /*__ALINIX_KERNEL_SYSTEM_DRIVERS_HID_PARSER_H*/