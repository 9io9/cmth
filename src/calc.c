#include <stdlib.h>
#include "calc.h"

static inline int32_t signb(int32_t d) {
    return d & (1 << 31);
}

Result addi32(int32_t a, int32_t b) {
    if (a > 0 && b > 0) {
        if (a > INT32_MAX - b) {
            return RESULT_FAIL("add result overflow(max)");
        }
    } else if (a < 0 && b < 0) {
        if (a < INT32_MIN - b) {
            return RESULT_FAIL("add result overflow(min)");
        }
    }

    return RESULT_SUC(i32, a + b);
}

Result subi32(int32_t a, int32_t b) {
    if (a > 0 && b < 0) {
        if (a > INT32_MAX + b) {
            return RESULT_FAIL("sub result overflow(max)");
        }
    } else if (a < 0 && b > 0) {
        if (a < INT32_MIN + b) {
            return RESULT_FAIL("sub result overflow(min)");
        }
    }

    return RESULT_SUC(i32, a - b);
} 

Result muli32(int32_t a, int32_t b) {
    if (a == 0 || b == 0) {
        return RESULT_SUC(i32, 0);
    }

    int bd = (signb(a) ^ signb(b)) == 0 ? INT32_MAX : INT32_MIN;

    if (a > 0) {
        if (a > bd / b) {
            return RESULT_FAIL("mul result overflow");
        }
    } else {
        if (a < bd / b) {
            return RESULT_FAIL("mul result overflow");
        }
    }

    return RESULT_SUC(i32, a * b);
}

Result divi32(int32_t a, int32_t b) {
    if (b == 0) {
        return RESULT_FAIL("divide zero");
    }

    return RESULT_SUC(i32, a / b);
}

Result modi32(int32_t a, int32_t b) {
    if (b == 0) {
        return RESULT_FAIL("mod zero");
    }

    return RESULT_SUC(i32, a % b);
}

Result mmodi32(int32_t a, int32_t b) {
    if (b == 0) {
        return RESULT_FAIL("mod zero");
    }

    if (a < 0) {
        if (b == INT32_MIN) {
            return RESULT_SUC(i32,  b - a);
        }

        return RESULT_SUC(i32, labs(b) + (a % b));
    }

    return RESULT_SUC(i32, a % b);
}


// TODO: int64 calcs function
#if __SIZEOF_POINTER__ == 8
Result addi64(int64_t a, int64_t b);
Result subi64(int64_t a, int64_t b);
Result muli64(int64_t a, int64_t b);
Result divi64(int64_t a, int64_t b);
Result modi64(int64_t a, int64_t b);
Result mmodi64(int64_t a, int64_t b);
#endif