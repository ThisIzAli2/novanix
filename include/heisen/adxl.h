#ifndef HEISEN_ADXL_H
#define HEISEN_ADXL_H
#include <stdint.h>
#include <types.h>
const char * const *adxl_get_component_names(void);
int adxl_decode(int64_t addr, int64_t component_values[]);

#endif /* HEISEN_ADXL_H */