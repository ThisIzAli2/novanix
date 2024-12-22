/*
 *
 * Copyright (C) 2012 ARM Limited
 */

#ifndef _HEISEN_VEXPRESS_H
#define _HEISEN_VEXPRESS_H

#include <heisen/device.h>
#include <heisen/regmap.h>

/* Config regmap API */

struct regmap *devm_regmap_init_vexpress_config(struct device *dev);

#endif