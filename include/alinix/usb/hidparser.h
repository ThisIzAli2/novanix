/**
 * @file hidparser.h
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
 * 	- Kernel USB header file util.
*/


#ifndef __ALINIX_KERNEL_INCLUDE_USB_HID_PARSER_H
#define __ALINIX_KERNEL_INCLUDE_USB_HID_PARSER_H



#include <alinix/types.h>


enum HID_PAGE_USAGE {
    GEN_DESKTOP = 1, BUTTON = 9,
};

enum HID_USAGE {
    POINTER = 1, MOUSE,
    POINTER_X = 0x30, POINTER_Y, POINTER_WHEEL = 0x38,
    NOTHING = 0xFF
};

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


struct HID_NODE {
    uint16_t u_page;
    uint16_t usage;
};

// Describe a HID Path
struct HID_PATH {
    int    size;                      // HID Path size
    struct HID_NODE node[PATH_SIZE];  // HID Path
};

// Describe a HID Data with its location in report 
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



typedef HIDParser HIDParser;

HIDParser* HIDParserCreate();
void HIDParserDestroy(HIDParser* parser);


bool HIDParser_Parse(struct HID_DATA* data);
void HIDParser_Reset();
bool HIDParser_FindObject(struct HID_DATA* data);
int* HIDParser_GetReportOffset(const uint8_t report_id, const uint8_t report_type);  

#endif /*__ALINIX_KERNEL_INCLUDE_USB_HID_PARSER_H*/