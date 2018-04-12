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

unsigned int prehash(const char *key, const int prime, const int mod);

hash_table *create_hash_table(const int capacity);
void delete_hash_table(hash_table *dict);

void insert(hash_table *dict, const char *key, const char *value);
void delete (hash_table *dict, const char *key);
char *search(hash_table *dict, const char *key);