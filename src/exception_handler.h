#ifndef __EXCEPTION_HANDLER_H__
#define __EXCEPTION_HANDLER_H__

#include <stdio.h>

unsigned exception_handler_has_error;
unsigned exception_handler_token_position;

void exception_handler_new_line(void);

void exception_handler_error(
    int position, 
    char *message, 
    ...);

void exception_handler_init(
    char *f_name,
    FILE *yyin);

void exception_handler_free(void);

#endif