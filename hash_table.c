#include "hash_table.h"

/* djb2 string hash function */
unsigned int get_hash(const char* key, const int prime, const int mod) {
	unsigned int result = prime;
	unsigned char *p = (unsigned char *) key;
	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}
	return result % mod;
}
/** initialize the hash table */
hash_table* init(const int capacity) {
    hash_table* dict = malloc(sizeof(hash_table));
    dict->size = 0;
    dict->capacity = capacity;
    dict->items = malloc(dict->capacity * sizeof(item*));
    if (dict->items == NULL) {
        return NULL;
    }
    return dict;
}

/** free heap memory */
void destruct(hash_table* dict) {
    int i = 0;
    for (i = 0; i < dict->capacity; ++i) {
        if (dict->items[i] != NULL)
            free(dict->items[i]);
    }
    free(dict->items);
}

int insert(hash_table* dict, const char* key, const char* value) {
    unsigned int index = get_hash(key, PRIME_1, dict->capacity);
    if (dict->items[index] != NULL) {
        dict->items[index]->value = strdup(value);
        return 1;
    } else {
        dict->items[index] = malloc(sizeof(item));
        dict->items[index]->key = strdup(key);
        dict->items[index]->value = strdup(value);
        ++dict->size;
    }
    return 1;
}

char* get(hash_table* dict, const char* key) {
    unsigned int index = get_hash(key, PRIME_1, dict->capacity);
    if (dict->items[index] == NULL) {
        return NULL;
    }
    return dict->items[index]->value;
}

int delete(hash_table* dict, const char* key) {
    unsigned int index = get_hash(key, PRIME_1, dict->capacity);
    if (dict->items[index] != NULL) {
        --dict->size;
        free(dict->items[index]);
        dict->items[index] = NULL;
    }
    return 1;
}

int main() {
    hash_table* dict = init(DEFAULT_CAPACITY);
    if (dict == NULL) {
        printf("allocation error\n");
        return EXIT_FAILURE;
    }
    /** tests */
    char *tests[] = {
        "test1",
        "test2",
        "test3",
        "test4",
        "test5",
        "test6",
        "test7"
    };
    int i = 0;
    char snum[5];
    for (i = 0;i < 7; ++i) {
        snprintf(snum, sizeof snum, "%d", i + 1);
        insert(dict, tests[i], snum);
    }
    insert(dict, "test1", "update");
    delete(dict, "test2");
    for (i = 0;i < 7; ++i) {
        printf("%s\n", get(dict, tests[i]));
    }
    printf("%s\n", get(dict, "none"));
    destruct(dict);
    return EXIT_SUCCESS;
}
