#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct dnode {
    char *key;
    char *value;
};

struct p3dict {
    int alloc;
    int length;
    struct dnode *items;
    int *index;
};