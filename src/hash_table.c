#include <assert.h>

#include "hash_table.h"
#include "alloc.h"

long long adler_32_hash(
    void *value)
{
    char *str = value;

    int a = 1;
    int b = 0;
    const int MODADLER = 65521;

    for (int i = 0; str[i] != '\0'; i++) {
        a = (a + str[i]) % MODADLER;
        b = (b + a) % MODADLER;
    }

    return (b << 16) | a;
}

unsigned index_from_hash(
    const long long hash,
    const unsigned capacity)
{
    return hash % capacity;
}

hash_table *hash_table_init()
{
    hash_table *table = (hash_table *)alloc_and_check(sizeof(hash_table));
    table->entries = (hash_table_entry **)
        alloc_and_check_list(HASH_TABLE_DEFAULT_CAPACITY, sizeof(hash_table_entry));

    table->capacity = HASH_TABLE_DEFAULT_CAPACITY;
    table->size = 0;

    return table;
}

void hash_table_put(
    hash_table *table,
    void *key,
    void *value)
{
    assert(table && key);

    const unsigned index = index_from_hash(adler_32_hash(key), table->capacity);

    hash_table_entry *entry = table->entries[index];

    if (entry) {
        if (entry->key == key) {
            entry->value = value;
        } else {
            // collision
            hash_table_entry *new_entry = (hash_table_entry *)alloc_and_check(sizeof(hash_table_entry));
            new_entry->next = entry->next;
            new_entry->value = value;
            new_entry->key = key;

            entry->next = new_entry;
            table->size++;
        }
    } else {
        hash_table_entry *new_entry = (hash_table_entry *)alloc_and_check(sizeof(hash_table_entry));
        new_entry->value = value;

        new_entry->key = key;
        table->size++;

        table->entries[index] = new_entry;
    }
}

void *hash_table_get(
    hash_table *table,
    void *key)
{
    assert(table && key);
    
    const unsigned index = index_from_hash(adler_32_hash(key), table->capacity);

    hash_table_entry *entry = table->entries[index];

    // collision
    while (entry && entry->key != key) {
        entry = entry->next;
    }

    if (entry) {
        return entry->value;
    }

    return NULL;
}

void hash_table_entry_free(
    hash_table_entry *entry)
{
    if (entry) {
        if (entry->next) {
            hash_table_entry_free(entry->next);
        }

        free(entry);
        entry = NULL;
    }
}

void hash_table_free(
    hash_table *table)
{
    if (table) {
        for (unsigned i = 0; i < table->capacity; i++) {
            hash_table_entry_free(table->entries[i]);
        }

        free(table->entries);
        table->entries = NULL;
        free(table);
        table = NULL;
    }
}
