#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct TreeMap {
    struct TreeMapEntry *__root;
    int __count;

    void (*put)(struct TreeMap *self, char *key, int value);
    int (*get)(struct TreeMap *self, char *key, int def);
    void (*dump)(struct TreeMapEntry *root, int depth);
    void (*dump_inorder)(struct TreeMapEntry *root);
    void (*dump_preorder)(struct TreeMapEntry *root);
    void (*dump_postorder)(struct TreeMapEntry *root);
    void (*del)(struct TreeMap *self);
};

struct TreeMapEntry {
    char *key;
    int value;
    struct TreeMapEntry *__left;
    struct TreeMapEntry *__right;
};

struct TreeMapEntry *TreeMapEntry_new(char *key, int value) {
    struct TreeMapEntry *entry = malloc(sizeof(*entry));
    char *new_key = malloc(strlen(key) + 1);
    strcpy(new_key, key);
    entry->key = new_key;
    entry->value = value;
    entry->__left = NULL;
    entry->__right = NULL;
    return entry;
}

void __TreeMap_dump(struct TreeMapEntry *root, int depth) {
    if (root != NULL) {
        for (int i = 0; i < depth; i++) {
            printf(" | ");
        }
        printf("%s=%d\n", root->key, root->value);

        __TreeMap_dump(root->__left, depth + 1);
        __TreeMap_dump(root->__right, depth + 1);
    }
}

void __TreeMap_dump_inorder(struct TreeMapEntry *root) {
    if (root != NULL) {
        __TreeMap_dump_inorder(root->__left);
        printf("%s=%d\n", root->key, root->value);
        __TreeMap_dump_inorder(root->__right);
    }
}

void __TreeMap_dump_preorder(struct TreeMapEntry *root) {
    if (root != NULL) {
        printf("%s=%d\n", root->key, root->value);
        if (root->__left != NULL) {
            __TreeMap_dump_preorder(root->__left);
        }
        if (root->__right != NULL) {
            __TreeMap_dump_preorder(root->__right);
        }
    }
}

void __TreeMap_dump_postorder(struct TreeMapEntry *root) {
    if (root != NULL) {
        if (root->__left != NULL) {
            __TreeMap_dump_postorder(root->__left);
        }
        if (root->__right != NULL) {
            __TreeMap_dump_postorder(root->__right);
        }
        printf("%s=%d\n", root->key, root->value);
    }
}

int __TreeMap_get(struct TreeMap *self, char *key, int def) {
    struct TreeMapEntry *cur;
    int cmp;

    if (key == NULL || self->__root == NULL) return def;
    cur = self->__root;
    while (cur != NULL) {
        cmp = strcmp(key, cur->key);
        if (cmp == 0) return cur->value;
        if (cmp < 0) {
            cur = cur->__left;
        } else {
            cur = cur->__right;
        }
    }
    return def;
}

void __TreeMap_put(struct TreeMap *self, char *key, int value) {
    struct TreeMapEntry *cur = self->__root;
    struct TreeMapEntry *parent = NULL;
    int cmp;

    while(cur != NULL) {
        parent = cur;
        cmp = strcmp(key, cur->key);
        if (cmp == 0) {
            cur->value = value;
            return;
        }
        if (cmp < 0) {
            cur = cur->__left;
        } else {
            cur = cur->__right;
        }
    }
    struct TreeMapEntry *new_entry = TreeMapEntry_new(key, value);

    if (parent == NULL) {
        self->__root = new_entry;
    } else if (cmp < 0) {
        parent->__left = new_entry;
    } else {
        parent->__right = new_entry;
    }
    self->__count++;
}

void __TreeMap_del(struct TreeMapEntry *root)
{
    if (root != NULL)
    {
        __TreeMap_del(root->__left);
        __TreeMap_del(root->__right);
        free(root->key);
        free(root);
    }
}

void TreeMap_del(struct TreeMap *self)
{
    __TreeMap_del(self->__root);
    free(self);
}

struct TreeMap * TreeMap_new() {
    struct TreeMap *tree = malloc(sizeof(*tree));
    tree->__root = NULL;
    tree->__count = 0;
    tree->put = &__TreeMap_put;
    tree->get = &__TreeMap_get;
    tree->dump = &__TreeMap_dump;
    tree->dump_inorder = &__TreeMap_dump_inorder;
    tree->dump_preorder = &__TreeMap_dump_preorder;
    tree->dump_postorder = &__TreeMap_dump_postorder;
    tree->del = &TreeMap_del;
    return tree;
}


int main() {
    struct TreeMap *map = TreeMap_new();
    
    map->put(map, "h", 22);
    map->put(map, "h", 42);
    map->put(map, "d", 8);
    map->put(map, "b", 123);
    map->put(map, "f", 6);
    map->put(map, "k", 9);
    map->put(map, "m", 68);

    printf("%d\n", map->get(map, "d", 404));

    // map->dump(map->__root, 0);

    // printf("\nInorder:\n");
    // map->dump_inorder(map->__root);

    // printf("\nPreorder:\n");
    // map->dump_preorder(map->__root);

    // printf("\nPostorder:\n");
    // map->dump_postorder(map->__root);

    map->del(map);
}

