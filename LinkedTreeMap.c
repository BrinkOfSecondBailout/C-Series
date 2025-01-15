#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct TreeMap {
    struct TreeMapEntry *__head;
    struct TreeMapEntry *__root;
    int __count;

    int (*get)(struct TreeMap *self, char *key, int def);
    void (*put)(struct TreeMap *self, char *key, int value);
    void (*dump)(struct TreeMapEntry *root, int depth);
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
    struct TreeMapEntry * cur;
    int cmp;
    cur = self->__root;
    if (self == NULL || key == NULL) return def;
    while(cur != NULL) {
        cmp = strcmp(cur->key, key);
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
    struct TreeMapEntry *cur, *parent, *prev;
    parent = prev = NULL;
    int cmp;
    cur = self->__root;
    while(cur != NULL) {
        parent = cur;
        cmp = strcmp(cur->key, key);
        if (cmp == 0) {
            cur->value = value;
            return;
        } 
        if (cmp < 0) {
            prev = cur;
            cur = cur->__left;
        } else {
            prev = cur;
            cur = cur->__right;
        }
    }
    struct TreeMapEntry *new_entry = __TreeMapEntry_new(key, value);
    if (parent == NULL) {
        self->__root = new_entry;
        self->__head = new_entry;
    } else if (cmp < 0) {
        new_entry->__next = parent;
        parent->__left = new_entry;
        if (prev->__next != NULL && strcmp(prev->__next->key, parent->key) == 0) {
            prev->__next = new_entry;
        }
        if (self->__head == NULL || strcmp(self->__head->key, new_entry->key) > 0) {
            self->__head = new_entry;
        }
    } else {
        if (parent->__next == NULL) {
            parent->__next = new_entry;
        } else {
            new_entry->__next = parent->__next;
            parent->__next = new_entry;
        }
        parent->__right = new_entry;
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

struct TreeMap * TreeMap_new() {
    struct TreeMap *map = malloc(sizeof(*map));
    map->__count = 0;
    map->__head = NULL;
    map->__root = NULL;

    map->get = &__TreeMapEntry_get;
    map->put = &__TreeMapEntry_put;
    map->dump = &__TreeMap_dump;
    return map;
}

struct TreeMapEntry * __TreeMapIter_next(struct TreeMapIter* self) {
    struct TreeMapEntry *retval;
    if (self->__current == NULL) return NULL;
    retval = self->__current;
    self->__current = self->__current->__next;
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

int main() {
    struct TreeMap *map = TreeMap_new();

    map->put(map, "g", 0);
    map->put(map, "c", 0);
    map->put(map, "i", 0);
    map->put(map, "f", 0);
    map->put(map, "a", 0);
    map->put(map, "h", 0);
    map->put(map, "d", 0);
    map->put(map, "e", 0);
    map->put(map, "x", 0);

    // map->dump(map->__root, 0);

    struct TreeMapIter *iter = TreeMapIter_new(map);
    struct TreeMapEntry *cur;
    cur = iter->next(iter);
    while(cur != NULL) {
        printf("%s=%d\n", cur->key, cur->value);
        cur = iter->next(iter);
    }
}