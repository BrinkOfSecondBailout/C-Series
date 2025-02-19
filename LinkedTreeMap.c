#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

struct TreeMap {
    struct TreeMapEntry *__head;
    struct TreeMapEntry *__root;
    int __count;

    int (*get)(struct TreeMap *self, char *key, int def);
    void (*put)(struct TreeMap *self, char *key, int value);
    void (*dump)(struct TreeMapEntry *root, int depth);
    void (*del)(struct TreeMap *self);
    struct TreeMapIter *(*iter)(struct TreeMap *self);
};

struct TreeMapEntry {
    char *key;
    int value;
    struct TreeMapEntry *__next;
    
    struct TreeMapEntry *__left;
    struct TreeMapEntry *__right;
};

struct TreeMapIter {
    struct TreeMap *__tree;
    struct TreeMapEntry *__current;

    struct TreeMapEntry * (*next)(struct TreeMapIter *self);
    void (*del)(struct TreeMapIter *self);
};

int __TreeMapEntry_get(struct TreeMap *self, char *key, int def) {
    if (self->__root == NULL || key == NULL) return def;
    struct TreeMapEntry * cur;
    int cmp;
    cur = self->__root;
    while(cur != NULL) {
        cmp = strcmp(key, cur->key);
        if (cmp == 0) {
            return cur->value;
        } else if (cmp < 0) {
            cur = cur->__left;
        } else {
            cur = cur->__right;
        }
    }
    return def;
}

struct TreeMapEntry * __TreeMapEntry_new(char *key, int value) {
    struct TreeMapEntry *entry = malloc(sizeof(*entry));

    char * new_key = malloc(strlen(key) + 1);
    strcpy(new_key, key);
    entry->key = new_key;
    entry->value = value;
    entry->__left = NULL;
    entry->__right = NULL;
    entry->__next = NULL;

    return entry;
}

void __TreeMapEntry_put(struct TreeMap *self, char *key, int value) {
    struct TreeMapEntry *cur, *parent, *smaller, *larger;
    parent = smaller = larger = NULL;
    int cmp;
    cur = self->__root;
    while(cur != NULL) {
        parent = cur;
        cmp = strcmp(key, cur->key);
        if (cmp == 0) {
            cur->value = value;
            return;
        } 
        if (cmp < 0) {
            larger = cur;
            cur = cur->__left;
        } else {
            smaller = cur;
            cur = cur->__right;
        }
    }

    struct TreeMapEntry *new_entry = __TreeMapEntry_new(key, value);
    if (parent == NULL) {
        self->__root = new_entry;
        self->__head = new_entry;
    } else if (cmp < 0) {
        if (smaller == NULL) 
            self->__head = new_entry;
        parent->__left = new_entry;
        new_entry->__next = larger;
        if (smaller != NULL)
            smaller->__next = new_entry;
    } else {
        parent->__right = new_entry;
        smaller->__next = new_entry;
        if (larger != NULL)
            new_entry->__next = larger;
    }
    self->__count++;
}


void __TreeMap_dump(struct TreeMapEntry *root, int depth) {
    if (root != NULL)
    {
        for (int i = 0; i < depth; i++)
        {
            printf(" | ");
        }
        printf("%s=%d\n", root->key, root->value);

        __TreeMap_dump(root->__left, depth + 1);
        __TreeMap_dump(root->__right, depth + 1);
    }
}

void __TreeMap_del(struct TreeMap *self) {
    free((void *)self);
}


struct TreeMapEntry * __TreeMapIter_next(struct TreeMapIter* self) {
    struct TreeMapEntry *retval;
    retval = self->__current;
    if (self->__current != NULL) {
        self->__current = self->__current->__next;
    }
    return retval;
}

void __TreeMapIter_del(struct TreeMapIter * self) {
    free((void *)self);
}

struct TreeMapIter * TreeMapIter_new(struct TreeMap* tree) {
    struct TreeMapIter *iter = malloc(sizeof(*iter));
    iter->__tree = tree;
    iter->__current = tree->__head;

    iter->next = &__TreeMapIter_next;
    iter->del = &__TreeMapIter_del;
    return iter;
}

struct TreeMap * TreeMap_new() {
    struct TreeMap *map = malloc(sizeof(*map));
    map->__count = 0;
    map->__head = NULL;
    map->__root = NULL;

    map->get = &__TreeMapEntry_get;
    map->put = &__TreeMapEntry_put;
    map->dump = &__TreeMap_dump;
    map->iter = &TreeMapIter_new;
    map->del = &__TreeMap_del;
    return map;
}

int main() {
    struct TreeMap *map = TreeMap_new();
    struct TreeMapEntry *cur;
    struct TreeMapIter *iter;
    char name[100];
    char word[100];
    int i, j;
    int count, maxvalue;
    char *maxkey;

    printf("Enter file name: ");
    scanf("%s", name);

    FILE *fp = fopen(name, "r");
    while (fscanf(fp, "%s", word) != EOF) {
        for (i = 0, j = 0; word[i] != '\0'; i++) {
            if ( !isalpha(word[i])) continue;
            word[j++] = tolower(word[i]);
        }
        word[j] = '\0';
        count = map->get(map, word, 0);
        map->put(map, word, count + 1);
    }
    fclose(fp);
    map->dump(map->__root, 0);

    maxkey = NULL;
    maxvalue = -1;
    iter = map->iter(map);
    while(1) {
        cur = iter->next(iter);
        if (cur == NULL) break;
        if (maxkey == NULL || cur->value > maxvalue) {
            maxkey = cur->key;
            maxvalue = cur->value;
        }
    }
    iter->del(iter);
    printf("\n%s %d\n", maxkey, maxvalue);

    map->del(map);


    // map->put(map, "j", 3);
    // map->put(map, "c", 23);
    // map->put(map, "l", 4);
    // map->put(map, "b", 7);
    // map->put(map, "f", 6);
    // map->put(map, "m", 55);
    // map->put(map, "o", 10);
    // map->put(map, "n", 511);
    // map->put(map, "i", 42);
    // map->put(map, "a", 77);
    // map->put(map, "e", 9);
    // map->put(map, "g", 2);
    // map->put(map, "h", 8);

    // map->dump(map->__root, 0);

    // struct TreeMapIter *iter = TreeMapIter_new(map);
    // struct TreeMapEntry *cur;
    // cur = iter->next(iter);
    // while(cur != NULL) {
    //     printf("%s = %d\n", cur->key, cur->value);
    //     cur = iter->next(iter);
    // }
    // iter->del(iter);

}