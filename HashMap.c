#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct HashMapEntry
{
    char *key;
    int value;
    struct HashMapEntry *__prev;
    struct HashMapEntry *__next;
};

struct HashMap
{
    int __buckets;
    struct HashMapEntry *__heads[8];
    struct HashMapEntry *__tails[8];
    int __count;

    void (*put)(struct HashMap *self, char *key, int value);
    int (*get)(struct HashMap *self, char *key, int def);
    int (*size)(struct HashMap *self);
    void (*dump)(struct HashMap *self);
    struct HashMapIter *(*iter)(struct HashMap *self);
    void (*del)(struct HashMap *self);
};

struct HashMapIter
{
    int __bucket;
    struct HashMap *__map;
    struct HashMapEntry *__current;

    struct HashMapEntry *(*next)(struct HashMapIter *self);
    void (*del)(struct HashMapIter *self);
};

void __HashMapIter_del(struct HashMapIter *self)
{
    free((void *)self);
}

struct HashMapEntry *__HashMapIter_next(struct HashMapIter *self)
{
    struct HashMapEntry *retval;

    while (self->__current == NULL) {
        self->__bucket++;
        if (self->__bucket >= self->__map->__buckets)
            return NULL;
        self->__current = self->__map->__heads[self->__bucket];
    }
    retval = self->__current;
    if (self->__current != NULL)
        self->__current = self->__current->__next;
    return retval;
}

struct HashMapIter *__HashMapIter_new(struct HashMap *map)
{
    struct HashMapIter *iter = malloc(sizeof(*iter));

    iter->__map = map;
    iter->__bucket = 0;
    iter->__current = map->__heads[iter->__bucket];

    iter->next = &__HashMapIter_next;
    iter->del = &__HashMapIter_del;
    return iter;
}

void __HashMap_del(struct HashMap *self)
{
    free((void *)self);
}

int __HashMap_size(struct HashMap *self)
{
    return self->__count;
}

int getBucket(char *str, int buckets)
{
    unsigned int hash = 123456;
    printf("\nHashing %s\n", str);
    if (str == NULL)
        return 0;
    for (; *str; str++)
    {
        hash = (hash << 3) ^ *str;
        printf("%c 0x%08x %d\n", *str, hash, hash % buckets);
    }
    return hash % buckets;
}

struct HashMapEntry *__HashMap_find(struct HashMap *self, char *key, int bucket)
{
    struct HashMapEntry *cur;
    if (self == NULL || key == NULL)
        return NULL;
    for (cur = self->__heads[bucket]; cur != NULL; cur = cur->__next)
    {
        if (strcmp(key, cur->key) == 0)
            return cur;
    }
    return NULL;
}

int __HashMap_get(struct HashMap *self, char *key, int def)
{
    int bucket = getBucket(key, self->__buckets);
    struct HashMapEntry *retval = __HashMap_find(self, key, bucket);
    if (retval == NULL)
        return def;
    return retval->value;
}

void __HashMap_put(struct HashMap *self, char *key, int value)
{
    int bucket;
    struct HashMapEntry *old, *new;
    char *new_key;
    bucket = getBucket(key, self->__buckets);

    old = __HashMap_find(self, key, bucket);
    if (old != NULL)
    {
        old->value = value;
        self->__count++;
        return;
    }

    new = malloc(sizeof(*new));
    new->key = key;
    new->value = value;
    new->__next = NULL;

    if (self->__heads[bucket] == NULL)
        self->__heads[bucket] = new;
    if (self->__tails[bucket] != NULL)
        self->__tails[bucket]->__next = new;

    new->__prev = self->__tails[bucket];
    self->__tails[bucket] = new;
    self->__count++;
}

void __HashMap_dump(struct HashMap *self)
{
    int i;
    struct HashMapEntry *cur;

    printf("\nObject HashMap@ %p count=%d buckets=%d\n", self, self->__count, self->__buckets);

    for (i = 0; i < self->__buckets; i++)
    {
        for (cur = self->__heads[i]; cur != NULL; cur = cur->__next)
        {
            printf("%s=%d [%d]\n", cur->key, cur->value, i);
        }
    }
}

struct HashMap *HashMap_new()
{
    struct HashMap *p = malloc(sizeof(*p));

    p->__buckets = 8;
    for (int i = 0; i < p->__buckets; i++)
    {
        p->__heads[i] = NULL;
        p->__tails[i] = NULL;
    }
    p->__count = 0;

    p->put = &__HashMap_put;
    p->get = &__HashMap_get;
    p->size = &__HashMap_size;
    p->dump = &__HashMap_dump;
    p->iter = &__HashMapIter_new;
    p->del = &__HashMap_del;

    return p;
}

int main()
{
    struct HashMap *map = HashMap_new();
    map->put(map, "Danny", 1);
    map->put(map, "Lindsey", 2);
    map->put(map, "Shawn", 3);
    struct HashMapIter *iter = map->iter(map);
    struct HashMapEntry *current = iter->next(iter);
    while (current)
    {
        printf("%s=%d\n", current->key, current->value);
        current = iter->next(iter);
    }
    map->dump(map);
    iter->del(iter);
    map->del(map);
}
