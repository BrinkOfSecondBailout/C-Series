#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


struct lnode {
    char *text;
    struct lnode *next;
};

struct list {
    int count;
    struct lnode *head;
    struct lnode *tail;
};

struct lnode * new_node(char *str) {
    struct lnode *p = malloc(sizeof(*p));
    char *saved = malloc(strlen(str) + 1);
    strcpy(saved, str);
    p->text = saved;
    p->next = NULL;
    return p;
}

struct list * list_new() {
    struct list *p = malloc(sizeof(*p));
    p->count = 0;
    p->head = NULL;
    p->tail = NULL;
    return p;
}

void list_append(struct list *self, char *str) {
    struct lnode *new = new_node(str);
    if (self->head == NULL) {
        self->head = new;
        self->tail = new;
    } else {
        self->tail->next = new;
        self->tail = new;
    }
    self->count++;
}

void list_print(struct list *self) {
    struct lnode *cur = self->head;
    printf("[");
    while(cur) {
        printf("'%s'", cur->text);
        cur = cur->next;
        if (cur) printf(", ");
    }
    printf("]");
}

void list_del(struct list *self) {
    struct lnode *cur, *next;
    cur = self->head;
    while(cur) {
        free(cur->text);
        next = cur->next;
        free(cur);
        cur = next;
    }
    free((void *)self);
}