#ifndef __ALLOC_H__
#define __ALLOC_H__

#include <stdlib.h>
#include <stdio.h>

extern void *alloc_and_check(
    unsigned size);

extern void **alloc_and_check_list(
    unsigned quantity,
    unsigned size);

#endif