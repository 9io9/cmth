#ifndef _LJW_CMTH_CALC_H_

#define _LJW_CMTH_CALC_H_

#include "chdrs/result.h"

Result addi32(int32_t a, int32_t b);
Result subi32(int32_t a, int32_t b);
Result muli32(int32_t a, int32_t b);
Result divi32(int32_t a, int32_t b);
Result modi32(int32_t a, int32_t b);
Result mmodi32(int32_t a, int32_t b);

#if __SIZEOF_POINTER__ == 8
Result addi64(int64_t a, int64_t b);
Result subi64(int64_t a, int64_t b);
Result muli64(int64_t a, int64_t b);
Result divi64(int64_t a, int64_t b);
Result modi64(int64_t a, int64_t b);
Result mmodi64(int64_t a, int64_t b);
#endif

#endif