#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 1000
#define PRIME_1 5183

typedef struct {
    char *key;
    char *value;
} item;

typedef struct {
    item **items;
    int capacity;
    int size;
} hash_table;

unsigned int get_hash(const char* key, const int prime, const int mod);

hash_table* init(const int capacity);
int insert(hash_table* dict, const char* key, const char* value);
char* get(hash_table* dict, const char* key);
int delete(hash_table* dict, const char* key);