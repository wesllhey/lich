#include "alloc.h"

void *alloc_and_check(
    unsigned size)
{
    void *pointer = malloc(size);

    if (!pointer) {
        fprintf(stderr, "Ran out of memory!\n");
        exit(1);
    }

    return pointer;
}

void **alloc_and_check_list(
    unsigned quantity,
    unsigned size)
{
    void **pointer_list = calloc(quantity, size);

    if (!pointer_list) {
        fprintf(stderr, "Ran out of memory!\n");
        exit(1);
    }

    return pointer_list;
}
