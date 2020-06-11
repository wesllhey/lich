#ifndef __ALLOC_H__
#define __ALLOC_H__

#include <stdlib.h>
#include <stdio.h>

void *alloc_and_check(
    unsigned size);

void **alloc_and_check_list(
    unsigned quantity,
    unsigned size);

#endif