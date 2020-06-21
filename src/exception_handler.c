#include <stdarg.h>

#include "exception_handler.h"
#include "alloc.h"

unsigned has_error = 0;

typedef struct line_position {
    unsigned position;
    struct line_position *rest;
} line_position;

static line_position *lines_handler = NULL;
static char *file_name = "";

unsigned line_number = 1;

unsigned exception_handler_token_position = 0;
unsigned exception_handler_has_error = 0;

static line_position *line_position_init(
    unsigned position,
    line_position *rest)
{
    line_position *new_lp = (line_position *)alloc_and_check(sizeof(line_position));

    new_lp->position = position;
    new_lp->rest = rest;

    return new_lp;
}

void exception_handler_new_line(void)
{
    line_number++;
    lines_handler = line_position_init(exception_handler_token_position, lines_handler);
}

void exception_handler_error(
    int position,
    char *message,
    ...)
{

    va_list ap;
    line_position *lines_tmp = lines_handler;
    unsigned line_number_tmp = line_number;

    exception_handler_has_error = 1;

    while (lines_tmp && lines_tmp->position > position) {
        lines_tmp = lines_tmp->rest;
        line_number_tmp--;
    }

    if (file_name)
        fprintf(stderr, "%s:", file_name);

    if (lines_tmp)
        fprintf(stderr, "%d.%d: ", line_number_tmp, position - lines_tmp->position);

    va_start(ap, message);
    vfprintf(stderr, message, ap);
    va_end(ap);

    fprintf(stderr, "\n");
}

void exception_handler_init(
    char *f_name,
    FILE *yyin)
{
    file_name = f_name;
    if (!yyin) {
        exception_handler_error(0, "cannot open");
        exit(1);
    }
}

void free_lines(
    line_position *lines)
{
    if (lines) {
        if (lines->rest) {
            free_lines(lines->rest);
            lines->rest = NULL;
        }

        free(lines);
        lines = NULL;
    }
}

void exception_handler_free(void)
{
    free_lines(lines_handler);
}
