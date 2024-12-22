/**
 * @author Ali Mirmohammad
 * @file math.h
 * *************************************IMPORTANT ALINIX LICENSE TERM********************************************
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
 *  - Implementation of mathematical operations in this header file.
 * @file : math.h
*/
#ifndef __ALINIX_KERNEL_MATH_H
#define __ALINIX_KERNEL_MATH_H


#define MATH_PI 3.14159265358979323846
#define abs(x) ((x) < 0 ? -(x) : (x))

#define __KERNEL_DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))
#define DIV_ROUND_UP __KERNEL_DIV_ROUND_UP


long Abs(long v);
long Sign(long v);

long sine(double x);
double cosine(double x);
double tangent(double x);


#endif /*__ALINIX_KERNEL_MATH_H*/