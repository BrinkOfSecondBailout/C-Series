#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define DEFAULT_ALLOC 2;

struct p1list {
    int alloc;
    int length;
    char **items;
};

struct p1list * p1list_new() {
    struct p1list *p = malloc(sizeof(*p));
    p->alloc = DEFAULT_ALLOC;
    p->length = 0;
    p->items = malloc(p->alloc * sizeof(char *));
    return p;
}

void p1list_append(struct p1list *self, char *str) {
    if (self->length >= self->alloc) {
        printf("Extending from %d to %d\n", self->alloc, self->alloc + 10);
        self->alloc = self->alloc + 10;
        self->items = (char **) realloc(self->items, (self->alloc * sizeof(char *)));
    }

    char *saved = malloc(strlen(str) + 1);
    strcpy(saved, str);
    self->items[self->length] = saved;
    self->length++;
}

void p1list_del(struct p1list *self) {
    int i;
    for (i = 0; i < self->length; i++) {
        free(self->items[i]);
    }
    free((void *)self->items);
    free((void *)self);
}

void p1list_print(struct p1list *self) {
    int i;
    int first = 1;
    printf("[");
    for (i = 0; i < self->length; i++) {
        if (!first) printf(", ");
        printf("'%s'", self->items[i]);
        first = 0;
    }
    printf("]\n");
}

int p1list_index(struct p1list *self, char *str) {
    int i;
    if (str == NULL) return -1;
    for (i = 0; i < self->length; i++) {
        if (strcmp(str, self->items[i]) == 0) return i;
    }
    return -1;
}

int main() {
    struct p1list *lst = p1list_new();
    p1list_append(lst, "Hello world");
    p1list_print(lst);
    p1list_append(lst, "Catch phrase");
    p1list_print(lst);
    p1list_append(lst, "Danny");
    p1list_print(lst);
    printf("Danny ? %d\n", p1list_index(lst, "Danny"));
    p1list_del(lst);
}
