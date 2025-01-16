#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct cstring {
    int length;
    int alloc;
    char *data;
};

struct cstring * cstring_new() {
    struct cstring *p = malloc(sizeof(*p));
    p->length = 0;
    p->alloc = 10;
    p->data = malloc(10);
    p->data[0] = '\0';
    return p;
}

void cstring_append(struct cstring *self, char c) {
    if (self->length + 2 >= self->alloc) {
        self->alloc = self->alloc * 2;
        self->data = realloc(self->data, self->alloc);
    }
    self->data[self->length] = c;
    self->length++;
    self->data[self->length] = '\0';
}

void cstring_appends(struct cstring *self, char *c) {
    for (; *c != '\0'; c++) {
        cstring_append(self, *c);
    }
}

void cstring_dump(struct cstring *self) {
    printf("Pystr length=%d alloc=%d data=%s\n", self->length, self->alloc, self->data);
}

void cstring_del(struct cstring *self) {
    free(self->data);
    free(self);
}

int main() {
    struct cstring *new_str = cstring_new();
    cstring_appends(new_str, "hello");
    cstring_dump(new_str);
    cstring_del(new_str);
}