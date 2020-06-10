#ifndef __HASH_TAB__H
#define __HASH_TAB__H

#define HASH_TABLE_DEFAULT_CAPACITY 1 << 7

typedef struct hash_table_entry {
    void *key;
    void *value;
    struct hash_table_entry *next; // collision
} hash_table_entry;

typedef struct hash_table {
    struct hash_table_entry **entries;
    unsigned capacity;
    unsigned size;
} hash_table;

extern hash_table *hash_table_init();

extern void hash_table_put(
    hash_table *table,
    void *key,
    void *value);

extern void *hash_table_get(
    hash_table *table,
    void *key);

extern void hash_table_free(
    hash_table *table);

#endif
