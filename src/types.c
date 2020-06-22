#include "types.h"

static type t_nil = {TYPE_NIL};
static type t_int = {TYPE_INT};
static type t_void = {TYPE_VOID};

type *type_nil(void) {
    return &t_nil;
}

type *type_int(void)
{
    return &t_int;
}

type *type_void(void)
{
    return &t_void;
}
