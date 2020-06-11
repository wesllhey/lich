#include "symbol_table.h"
#include "alloc.h"

symbol_table_entry *symbol_table_entry_new(
    char *name)
{
    symbol_table_entry *symbol = (symbol_table_entry *)alloc_and_check(sizeof(symbol_table_entry));
    symbol->name = name;

    return symbol;
}

symbol_table *symbol_table_new(void)
{
    return hash_table_init();
}

void symbol_table_put(
    symbol_table *table,
    symbol_table_entry *symbol,
    void *value)
{
    hash_table_put(table, symbol, value);
}

void *symbol_table_get(
    symbol_table *table,
    symbol_table_entry *symbol)
{
    return hash_table_get(table, symbol);
}

void symbol_table_free(
    symbol_table *table)
{
    return hash_table_free(table);
}
