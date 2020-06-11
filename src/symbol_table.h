#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

#include "hash_table.h"

typedef struct symbol_table_entry {
    char *name;
} symbol_table_entry;

typedef struct hash_table symbol_table;

extern symbol_table_entry *symbol_table_entry_new(
    char *name);

extern symbol_table *symbol_table_new(void);

extern void symbol_table_put(
    symbol_table *table,
    symbol_table_entry *symbol,
    void *value);

extern void *symbol_table_get(
    symbol_table *table,
    symbol_table_entry *symbol);

extern void symbol_table_free(
    symbol_table *table);

#endif