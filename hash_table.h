#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CAPACITY 1000

typedef struct {
    char *key;
    char *value;
} item;

item **items;
int capacity = DEFAULT_CAPACITY;
int size = 0;

int insert(char* key, char* value);
int update(char* key, char* value);
int delete(char* key);
char* get(char* key);

unsigned int get_hash(char* key);