#include "hash_table.h"

/**
 * djb2 string hash function
 **/
unsigned int prehash(const char *key, const int prime, const int mod) {
  unsigned int result = prime;
  unsigned char *p = (unsigned char *)key;
  while (*p != '\0') {
    result = (result << 5) + result + *p;
    ++p;
  }
  return result % mod;
}

/**
 * allocate memory for the hash table
 **/
hash_table *create(const int capacity) {
  hash_table *dict = malloc(sizeof(hash_table));
  if (dict == NULL) {
    printf("allocation error\n");
    exit(EXIT_FAILURE);
  }
  dict->size = 0;
  dict->capacity = capacity;
  dict->items = malloc(dict->capacity * sizeof(item *));
  if (dict->items == NULL) {
    printf("allocation error\n");
    exit(EXIT_FAILURE);
  }
  return dict;
}
/**
 * free memory used by the hash table
 **/
void destruct(hash_table *dict) {
  int i = 0;
  for (i = 0; i < dict->capacity; ++i) {
    if (dict->items[i] != NULL)
      free(dict->items[i]);
  }
  free(dict->items);
}
/**
 * insert the item {key, value} into the hash table
 * increment hash table size
 * if the item already exists, update the {value}
 **/
void insert(hash_table *dict, const char *key, const char *value) {
  unsigned int index = prehash(key, PRIME_1, dict->capacity);
  if (dict->items[index] != NULL) {
    dict->items[index]->value = strdup(value);
  } else {
    dict->items[index] = malloc(sizeof(item));
    if (dict->items[index] == NULL) {
      printf("allocation error\n");
      exit(EXIT_FAILURE);
    }
    dict->items[index]->key = strdup(key);
    dict->items[index]->value = strdup(value);
    ++dict->size;
  }
}
/**
 * look for the item associated with {key} in the hash table
 * if the item exists, delete it, decrement hash table size
 **/
void delete (hash_table *dict, const char *key) {
  unsigned int index = prehash(key, PRIME_1, dict->capacity);
  if (dict->items[index] != NULL) {
    --dict->size;
    free(dict->items[index]);
    dict->items[index] = NULL;
  }
}
/**
 * look for the item associated with {key} in the hash table
 * @return {value}, if the item exists
 *         NULL, if the item does not exist
 **/
char *search(hash_table *dict, const char *key) {
  unsigned int index = prehash(key, PRIME_1, dict->capacity);
  if (dict->items[index] == NULL) {
    printf("allocation error\n");
    return NULL;
  }
  return dict->items[index]->value;
}

int main() {
  /** create dictionary */
  hash_table *dict = create(DEFAULT_CAPACITY);
  /** testing dictionary */
  char *tests[] = {"test1", "test2", "test3", "test4",
                   "test5", "test6", "test7"};
  int i = 0;
  char snum[5];
  for (i = 0; i < 7; ++i) {
    snprintf(snum, sizeof snum, "%d", i + 1);
    insert(dict, tests[i], snum);
  }
  insert(dict, "test1", "update");
  delete (dict, "test2");
  for (i = 0; i < 7; ++i) {
    printf("%s\n", search(dict, tests[i]));
  }
  printf("%s\n", search(dict, "none"));
  destruct(dict);
  return EXIT_SUCCESS;
}
