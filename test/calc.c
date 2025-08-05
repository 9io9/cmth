#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

static void fres(Result* r) {
    if (!r->has_value) {
        fprintf(stderr, "line %u, function %s, file %s for %s\n", r->result.error.line, r->result.error.function, r->result.error.file, r->result.error.message);
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    Result r = addi32(4, 4);

    fres(&r);

    if (r.result.data.to_i32 != 8) {
        fprintf(stderr, "add returns %d, but expect %d\n", r.result.data.to_i32, 8);
        return 1;
    }

    r = addi32(INT32_MAX - 8, 9);

    if (r.has_value) {
        fprintf(stderr, "add should return overflow error, but not\n");
        return 1;
    }

    r = subi32(1, INT32_MIN);

    if (r.has_value) {
        fprintf(stderr, "sub should return overflow error, but not\n");
        return 1;
    }

    r = mmodi32(-4, -3);

    fres(&r);

    if (r.result.data.to_i32 != 2) {
        fprintf(stderr, "math mod returns %d, but expect %d\n", r.result.data.to_i32, 2);
        return 1;
    }

    return 0;
}