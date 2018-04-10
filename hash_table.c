#include "hash_table.h"

/* djb2 string hash function */
unsigned int get_hash(char* key) {
	unsigned int result = 5381;
	unsigned char *p = (unsigned char *) key;
	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}
	return result % capacity;
}

int insert(char* key, char* value) {
    unsigned int index = get_hash(key);
    if (items[index] != NULL) {
        items[index]->value = strdup(value);
        return 1;
    } else {
        items[index] = malloc(sizeof(item));
        items[index]->key = strdup(key);
        items[index]->value = strdup(value);
        ++size;
    }
    return 1;
}

int delete(char* key) {
    unsigned int index = get_hash(key);
    if (items[index] != NULL) {
        --size;
        free(items[index]);
        items[index] = NULL;
    }
    return 1;
}

char* get(char* key) {
    unsigned int index = get_hash(key);
    if (items[index] == NULL) {
        return NULL;
    }
    return items[index]->value;
}

int main() {
    items = malloc(capacity * sizeof(item*));
    if (items == NULL) {
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
        insert(tests[i], snum);
    }
    insert("test1", "update");
    delete("test2");
    for (i = 0;i < 7; ++i) {
        printf("%s\n", get(tests[i]));
    }
    printf("%s\n", get("none"));
    /** free the memory */
    for (i = 0; i < capacity; ++i) {
        if (items[i] != NULL)
            free(items[i]);
    }
    free(items);
    return EXIT_SUCCESS;
}
