#include "error.h"
#include <stdio.h>

void error(const char *reason) {
    (void)printf("Fatal error: %s\n", reason);
    exit(EXIT_FAILURE);
}
