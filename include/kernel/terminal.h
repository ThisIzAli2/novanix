#ifndef _HEISEN_TERMINAL_H
#define _HEISEN_TERMINAL_H

#include <heisen/typing.h>

class StringView;


enum class NumberFormat{
    Decimal,
    DecimalNoCommas,
    Hexa
};

class Printer{
    public:
        Printer();
        /*Print a single character*/
        Printer& operator<<(char c);

        Printer& operator<<(const char* str);
        Printer& operator <<(const StringView& str);

        // Prints an signed int.
        Printer& operator <<(int c);

        // Prints a long int.
        Printer& operator <<(size_t num);

        // Switches to a new number format.
        Printer& operator <<(NumberFormat format);
    
    private:
        void PrintHexidecimal(size_t number);
        void PrintDecimal(size_t number, bool with_commas);

        // The current number format.
        NumberFormat number_format_;
};

extern Printer print;

// Initializes the text printer.
extern void InitializePrinter();


#endif // _HEISEN_TERMINAL_H