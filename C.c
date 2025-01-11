#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



struct MapEntry {
    char *key; /* public */
    int value; /* public */
    struct MapEntry *__prev;
    struct MapEntry *__next;
};

struct MapIter {
    struct MapEntry *__current;

    struct MapEntry* (*next) (struct MapIter* self);
    void (*del) (struct MapIter* self);
};

struct MapEntry * __MapIter_next(struct MapIter* self) {
    
}

void __MapIter_del(struct MapIter* self) {

}



struct Map {
    struct MapEntry *__head;
    struct MapEntry *__tail;
    int __count;

    /* Public methods*/
    void (*put) (struct Map* self, char *key, int value);
    int (*get) (struct Map* self, char *key, int def);
    int (*size) (struct Map* self);
    void (*dump) (struct Map* self);
    void (*del) (struct Map* self);
};

void __Map_dump(struct Map* self) {
    struct MapEntry *cur;
    printf("Object Map count=%d\n", self->__count);
    for(cur = self->__head; cur != NULL; cur = cur->__next) {
        printf("%s=%d\n", cur->key, cur->value);
    }
}

void __Map_del(struct Map* self) {
    struct MapEntry *cur, *next;
    cur = self->__head;
    while(cur) {
        free(cur->key);
        next = cur->__next;
        free(cur);
        cur = next;
    }
    free((void *)self);
    printf("Successfully freed.\n");
}

struct MapEntry * __Map_find(struct Map* self, char *key) {
    struct MapEntry *cur;
    cur = self->__head;
    while(cur) {
        if (strcmp(cur->key, key) == 0) {
            return cur;
        }
        cur = cur->__next;
    }
    return NULL;
}

int __Map_get(struct Map *self, char *key, int def)
{
    struct MapEntry *retval = __Map_find(self, key);
    if (!retval)
        return def;
    return retval->value;
}

void __Map_put(struct Map* self, char *key, int value) {
    struct MapEntry *retval = __Map_find(self, key);
    if (retval) {
        retval->value = value;
        return;
    }

    struct MapEntry *new_entry = malloc(sizeof(*new_entry));
    if (!new_entry) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    new_entry->__next = NULL;

    new_entry->key = malloc(strlen(key) + 1);
    if (!new_entry->key) {
        fprintf(stderr, "Memory allocation failed\n");
        free(new_entry);
        return;
    }
    strcpy(new_entry->key, key);
    new_entry->value = value;

    if (self->__head == NULL) {
        self->__head = new_entry;
        self->__tail = new_entry;
        new_entry->__prev = NULL;
    } else {
        self->__tail->__next = new_entry;
        new_entry->__prev = self->__tail;
        self->__tail = new_entry;
    }
    self->__count++;
}

int __Map_size(struct Map *self) {
    return self->__count;
}

struct Map * Map_new() {
    struct Map *p = malloc(sizeof(*p));

    p->__head = NULL;
    p->__tail = NULL;
    p->__count = 0;

    p->put = &__Map_put;
    p->get = &__Map_get;
    p->size = &__Map_size;
    p->dump = &__Map_dump;
    p->del = &__Map_del;

    return p;
}

struct MapIter * MapIter_new(struct Map *self) {
    struct MapIter *p = malloc(sizeof(*p));

    p->__current = self->__head;
    p->next = &__MapIter_next;
    p->del = &__MapIter_del;

    return p;
}

int main() {
    struct Map * map = Map_new();
    map->put(map, "Danny", 5);
    map->put(map, "Lindsey", 15);
    printf("Danny=%d\n", map->get(map, "Danny", 404));
    printf("Zach=%d\n", map->get(map, "Zach", 404));
    map->dump(map);
    printf("Size=%d\n", map->size(map));
    map->del(map);
}




// struct dnode
// {
//     char *key;
//     char *value;
//     struct dnode *next;
// };

// struct pydict
// {
//     struct dnode *head;
//     struct dnode *tail;
//     int count;
//     void (*del)(struct pydict *self);
//     void (*put)(struct pydict *self, char *key, char *value);
//     int (*len)(const struct pydict *self);
//     char* (*get)(struct pydict *self, char *key);
// };


// int pydict_len(const struct pydict *self)
// {
//     return (self->count);
// }

// void pydict_del(struct pydict *self)
// {
//     struct dnode *cur, *next;
//     cur = self->head;
//     while (cur)
//     {
//         free(cur->key);
//         free(cur->value);
//         next = cur->next;
//         free(cur);
//         cur = next;
//     }
//     free((void *)self);
// }

// struct dnode *pydict_find(struct pydict *self, char *key)
// {
//     struct dnode *cur;
//     cur = self->head;
//     while (cur)
//     {
//         if (strcmp(cur->key, key) == 0)
//         {
//             return cur;
//         }
//         cur = cur->next;
//     }
//     return NULL;
// }

// void pydict_put(struct pydict *self, char *key, char *value)
// {
//     struct dnode *cur;
//     cur = pydict_find(self, key);
//     if (cur)
//     {
//         char *new_value = malloc(strlen(value) + 1);
//         if (!new_value)
//         {
//             fprintf(stderr, "Memory reallocation failed\n");
//             return;
//         }
//         free(cur->value);
//         cur->value = new_value;
//         strcpy(cur->value, value);
//         return;
//     }

//     struct dnode *new_node = malloc(sizeof(*new_node));
//     if (!new_node)
//     {
//         fprintf(stderr, "Memory allocation failed\n");
//         exit(EXIT_FAILURE);
//     }
//     new_node->next = NULL;

//     new_node->key = malloc(strlen(key) + 1);
//     if (!new_node->key)
//     {
//         fprintf(stderr, "Memory reallocation failed\n");
//         free(new_node);
//         exit(EXIT_FAILURE);
//     }
//     strcpy(new_node->key, key);

//     new_node->value = malloc(strlen(value) + 1);
//     if (!new_node->value)
//     {
//         fprintf(stderr, "Memory reallocation failed\n");
//         free(new_node->key);
//         free(new_node);
//         exit(EXIT_FAILURE);
//     }
//     strcpy(new_node->value, value);

//     if (self->head == NULL)
//     {
//         self->head = new_node;
//         self->tail = new_node;
//     }
//     else
//     {
//         self->tail->next = new_node;
//         self->tail = new_node;
//     }
//     self->count++;
// }

// char *pydict_get(struct pydict *self, char *key)
// {
//     struct dnode *cur;
//     cur = pydict_find(self, key);
//     if (cur)
//         return cur->value;
//     return NULL;
// }

// void pydict_print(struct pydict *self)
// {
//     struct dnode *cur;
//     cur = self->head;
//     printf("{");
//     while (cur)
//     {
//         printf("'%s': '%s'", cur->key, cur->value);
//         cur = cur->next;
//         if (cur)
//             printf(", ");
//     }
//     printf("}\n");
// }

// struct pydict *pydict_new()
// {
//     struct pydict *p = malloc(sizeof(*p));
//     p->head = NULL;
//     p->tail = NULL;
//     p->count = 0;
//     p->del = &pydict_del;
//     p->put = &pydict_put;
//     p->len = &pydict_len;
//     p->get = &pydict_get;

//     return p;
// }

// int main()
// {
//     struct pydict *dct = pydict_new();

//     dct->put(dct, "z", "Catch");
//     dct->put(dct, "z", "W");
//     printf("Length=%d\n", dct->len(dct));
//     printf("z=%s\n", dct->get(dct, "z"));
//     dct->del(dct);
// }

// int main(void)
// {
//     struct pydict *dct = pydict_new();
//     pydict_put(dct, "z", "Catch phrase");
//     pydict_print(dct);
//     pydict_put(dct, "z", "W");
//     pydict_print(dct);
//     pydict_put(dct, "y", "B");
//     pydict_put(dct, "c", "C");
//     pydict_put(dct, "a", "D");
//     pydict_print(dct);
//     printf("Length=%d\n", pydict_len(dct));

//     printf("z=%s\n", pydict_get(dct, "z"));
//     printf("x=%s\n", pydict_get(dct, "x"));

//     printf("\nDump\n");
//     for (struct dnode *cur = dct->head; cur != NULL; cur = cur->next)
//     {
//         printf("%s=%s\n", cur->key, cur->value);
//     }
//     pydict_del(dct);
// }

// struct lnode {
//     char *text;
//     struct lnode *next;
// };

// struct pylist {
//     struct lnode *head;
//     struct lnode *tail;
//     int length;
// };

// struct pylist * pylist_new() {
//     struct pylist *p = malloc(sizeof(*p));

//     p->length = 0;
//     p->head = NULL;
//     p->tail = NULL;

//     return p;
// }

// void pylist_append(struct pylist * self, char *c) {
//     struct lnode *new_node = malloc(sizeof(*new_node));

//     if (!new_node)
//     {
//         fprintf(stderr, "Memory allocation failed\n");
//         exit(EXIT_FAILURE);
//     }

//     new_node->text = malloc(strlen(c) + 1);
//     if (!new_node->text)
//     {
//         fprintf(stderr, "Memory allocation failed\n");
//         free(new_node);
//         exit(EXIT_FAILURE);
//     }

//     strcpy(new_node->text, c);

//     new_node->next = NULL;

//     if (self->head == NULL) {
//         self->head = new_node;
//         self->tail = new_node;
//     } else {
//         self->tail->next = new_node;
//         self->tail = new_node;
//     }
//     self->length++;

// }

// void pylist_print(struct pylist * self) {
//     if (self->length == 0) {
//         printf("[]\n");
//         return;
//     }

//     struct lnode *cur;
//     cur = self->head;
//     printf("[");
//     while(cur) {
//         printf("'%s'", cur->text);
//         cur = cur->next;
//         if (cur)
//             printf(", ");
//     }
//     printf("]\n");
// }

// int pylist_len(const struct pylist * self) {
//     return self->length;
// }

// int pylist_index(struct pylist *self, char *c) {
//     struct lnode *cur;
//     int i;
//     cur = self->head;
//     for(i = 0; cur != NULL; cur = cur->next, i++) {
//         if (strcmp(cur->text, c) == 0) return(i);
//     }
//     return(-1);
// }

// void pylist_del(struct pylist *self) {
//     struct lnode *cur, *next;
//     cur = self->head;
//     while (cur) {
//         free(cur->text);
//         next = cur->next;
//         free(cur);
//         cur = next;
//     }
//     free((void *)self);
// }

// int main(void)
// {
//     struct pylist *lst = pylist_new();
//     pylist_append(lst, "Hello world");
//     pylist_print(lst);
//     pylist_append(lst, "Catch phrase");
//     pylist_print(lst);
//     pylist_append(lst, "Brian");
//     pylist_print(lst);
//     printf("Length = %d\n", pylist_len(lst));
//     printf("Brian? %d\n", pylist_index(lst, "Brian"));
//     printf("Bob? %d\n", pylist_index(lst, "Bob"));
//     pylist_del(lst);
// }

// struct pystr
// {
//     int length;
//     int alloc;
//     char *data;
// };

// struct pystr *pystr_new()
// {
//     struct pystr *p = malloc(sizeof(*p));

//     p->length = 0;
//     p->alloc = 10;
//     p->data = malloc(10);
//     p->data[0] = '\0';

//     return p;
// }

// void pystr_del(const struct pystr *x)
// {
//     if (x)
//     {
//         free((void *)x->data);
//         free((void *)x);
//     }
// }

// void pystr_dump(const struct pystr *x)
// {
//     if (x)
//     {
//         printf("Pystr length=%d alloc=%d data=%s\n", x->length, x->alloc, x->data);
//     }
// }

// int pystr_len(const struct pystr *x)
// {
//     return (x ? x->length : 0);
// }

// char *pystr_str(const struct pystr *x)
// {
//     return x->data;
// }

// void pystr_append(struct pystr *x, char c)
// {
//     if (x->length + 1 >= x->alloc)
//     {
//         x->alloc *= 2;
//         x->data = realloc(x->data, x->alloc);
//         if (!x->data)
//         {
//             fprintf(stderr, "Memory reallocation failed\n");
//             exit(EXIT_FAILURE);
//         }
//     }
//     x->data[x->length] = c;
//     x->length++;
//     x->data[x->length] = '\0';
// }

// void pystr_appends(struct pystr *x, char *c)
// {
//     for (; *c != '\0'; c++)
//     {
//         pystr_append(x, *c);
//     }
// }

// void pystr_assign(struct pystr *x, char *c)
// {
//     if (x)
//     {
//         x->length = 0;
//         pystr_appends(x, c);
//     }
// }

// int main(void)
// {
//     struct pystr * x = pystr_new();
//     pystr_dump(x);

//     pystr_append(x, 'H');
//     pystr_dump(x);

//     pystr_appends(x, "ello world");
//     pystr_dump(x);

//     pystr_assign(x, "A new string");
//     printf("String = %s\n", pystr_str(x));
//     printf("Length = %d\n", pystr_len(x));
//     pystr_del(x);
// }

// struct Point {
//     double x;
//     double y;

//     void (*del) (const struct Point* self);
//     void (*dump) (const struct Point* self);
//     double (*origin) (const struct Point* self);
// };

// void point_dump(const struct Point* self) {
//     printf("Object point@%p x=%f y=%f\n", self, self->x, self->y);
// }

// void point_del(const struct Point* self) {
//     free((void*)self);
// }

// double point_origin(const struct Point* self) {
//     return sqrt(self->x*self->x + self->y * self->y);
// }

// struct Point *point_new(double x, double y) {
//     struct Point *p = malloc(sizeof(*p));
//     p->x = x;
//     p->y = y;
//     p->dump = &point_dump;
//     p->origin = &point_origin;
//     p->del = &point_del;
//     return p;
// }

// int main(void) {
//     struct Point *pt = point_new(4.0, 5.0);
//     pt->dump(pt);
//     printf("Origin %f\n", pt->origin(pt));
//     pt->del(pt);
// }

// struct Student {
//     char *name;
//     int age;

//     void (*del) (const struct Student* self);
//     void (*dump) (const struct Student* self);
// };

// void student_del(const struct Student* self) {
//     if (self) {
//         free((void *)self->name);
//         free((void *)self);
//     }
// }

// void student_dump(const struct Student* self) {
//     if (self) {
//         printf("Object @%p name=%s age=%d\n", self, self->name, self->age);
//     }
// }

// struct Student * student_new(char *name, int age) {
//     struct Student *p = malloc(sizeof(*p));
//     if (!p) {
//         fprintf(stderr, "Memory allocation failed for Student\n");
//         exit(EXIT_FAILURE);
//     }
//     p->name = malloc(strlen(name) + 1);
//     if (!p->name) {
//         fprintf(stderr, "Memory allocation failed for name\n");
//         free(p);
//         exit(EXIT_FAILURE);
//     }
//     strcpy(p->name, name);
//     p->age = age;
//     p->del = &student_del;
//     p->dump = &student_dump;
//     return p;
// }

// int main() {
//     char *name = "Danny";
//     struct Student * danny = student_new(name, 35);
//     danny->dump(danny);
//     danny->del(danny);
// }

// struct Example {
//     unsigned a : 5;
//     unsigned b : 10;
//     unsigned c : 17;
//     unsigned d : 8;
// };

// int main() {
//     printf("Size of struct Example: %zu bytes\n", sizeof(struct Example));
// }

// #define HASHSIZE 100

// struct nlist { /* basic table entry */
//     char *name;
//     char *def;
//     struct nlist *next; /* next entry in chain */
// };

// static struct nlist *hashtab[HASHSIZE]; /* pointer table */

// int hash(char *s) { /* form hash value for string s */
//     int hashval;

//     for (hashval = 0; *s != '\0'; )
//         hashval += *s++;
//     return(hashval % HASHSIZE);
// }

// struct nlist *lookup(char *s) { /* look for s in hashtab */
//     struct nlist *np;

//     for (np = hashtab[hash(s)]; np != NULL; np = np->next)
//         if (strcmp(s, np->name) == 0)
//             return(np); /* found */
//     return(NULL); /*not found */
// }

// struct nlist *install(char *name, char *def) { /* install in hashtab */
//     struct nlist *np, *lookup();
//     char *strsave(), *alloc();
//     int hashval;

//     if ((np = lookup (name)) == NULL) { /* Not found */
//         np = (struct nlist *) alloc(sizeof(*np));
//         if (np == NULL)
//             return(NULL);
//         if ((np->name = strsave(name)) == NULL)
//             return (NULL);
//         hashval = hash(np->name);
//         np->next = hashtab[hashval];
//     } else /* already there */
//         free(np->def); /* free previous definition */
//     if ((np->def = strsave(def)) == NULL)
//         return(NULL);
//     return(np);
// }

// #define MAXWORD 20
// #define LETTER 'a'

// struct tnode {
//     char *word;
//     int count;
//     struct tnode *left;
//     struct tnode *right;
// };

// int main() {
//     struct tnode *root, *tree();
//     char word[MAXWORD];
//     int t;

//     root = NULL;
//     while ((t = get_word(word, MAXWORD)) != EOF)
//         if (t == LETTER)
//             root = tree(root, word);
//     treeprint(root);
// }

// struct tnode *tree(struct tnode *p, char *w) {
//     struct tnode *talloc();
//     char *strsave();
//     int cond;

//     if (p == NULL) { /* tree is brand new and this is the first word */
//         p = talloc();
//         p->word = strsave(w);
//         p->count = 1;
//         p->left = p->right = NULL;
//     } else if ((cond = strcmp(w, p->word)) == 0) /* a word is found, increment the count */
//         p->count++;
//     else if (cond < 0) /* word is less than the root, go to the left */
//         p->left = tree(p->left, w);
//     else /* word is more than the root, go to the right */
//         p->right = tree(p->right, w);
//     return (p);
// }

// int treeprint(struct tnode *p) {
//     if (p != NULL) {
//         treeprint(p->left);
//         printf("%4d %s\n", p->count, p->word);
//         treeprint(p->right);
//     }
// }

// #define MAXLINE 1000

// struct lnode {
//     char *text;
//     struct lnode *prev;
//     struct lnode *next;
// };

// int main() {
//     struct lnode *head = NULL;
//     struct lnode *tail = NULL;
//     struct lnode *current;
//     char line[MAXLINE];

//     while (fgets(line, MAXLINE, stdin) != NULL) {
//         char *save = (char *) malloc(strlen(line) + 1);
//         strcpy(save, line);

//         struct lnode *new = (struct lnode *) malloc(sizeof(struct lnode));
//         new->text = save;
//         new->next = NULL;
//         new->prev = tail;

//         if (head == NULL) head = new;
//         if (tail != NULL) tail->next = new;
//         tail = new;
//     }

//     for (current = tail; current != NULL; current=current->prev) {
//         printf("%s", current->text);
//     }
// }

// #define MAXWORD 20
// #define LETTER 'a'
// #define DIGIT '0'
// #define NKEYS (sizeof(keytab) / sizeof(struct key))
// #define BUFSIZE 100
// char buf[BUFSIZE]; /* buffer for ungetch */
// int bufp = 0; /* next free position in buf */


// struct key {
//     char *keyword;
//     int keycount;
// } keytab[NKEYS];

// int type(int c) {
//     if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
//         return(LETTER);
//     else if (c >= '0' && c <= '9')
//         return(DIGIT);
//     else
//         return(c);
// }

// int getch() /* get a (possibly pushed back) character */
// {
//     return ((bufp > 0) ? buf[--bufp] : getchar());
// }

// int ungetch(int c) /* push character back on input */
// {
//     if (bufp > BUFSIZE)
//         printf("ungetch: too many characters\n");
//     else
//         buf[bufp++] = c;
// }

// int getword(char *w, int lim) {
//     int c, t;
//     if (type(c = *w++ = getch()) != LETTER) {
//         *w = '\0';
//         return(c);
//     }

//     while (--lim > 0) {
//         t = type(c = *w++ = getch());
//         if (t != LETTER && t != DIGIT) {{
//             ungetch(c);
//             break;
//         }}
//     }
//     *(w-1) = '\0';
//     return (LETTER);
// }


// int main() {
//     int t;
//     char word[MAXWORD];
//     struct key *binary(), *p;

//     while ((t = getword(word, MAXWORD)) != EOF)
//         if (t == LETTER)
//             if ((p=binary(word, keytab, NKEYS)) != NULL)
//                 p->keycount++;
//     for (p = keytab; p < keytab + NKEYS; p++)
//         if (p->keycount > 0)
//             printf("%4d %s\n", p->keycount, p->keyword);
// }

// struct key *binary(char *word, struct key tab[], int n) {
//     int cond;

//     struct key *low = &tab[0];
//     struct key *high = &tab[n - 1];
//     struct key *mid;

//     while (low <= high) {
//         mid = low + (high - low) / 2;
//         if ((cond = strcmp(word, mid->keyword)) < 0)
//             high = mid - 1;
//         else if (cond > 0)
//             low = mid + 1;
//         else
//             return (mid);
//     }
//     return(NULL);
// }




// struct key {
//     char *keyword;
//     int keycount;
// } keytab[NKEYS];

// int main() {
//     int n, t;
//     char word[MAXWORD];

//     while ((t = getword(word, MAXWORD)) != EOF)
//         if (t == LETTER)
//             if ((n = binary(word, keytab, NKEYS)) >= 0)
//                 keytab[n].keycount++;
    
//     for (n = 0; n < NKEYS; n++)
//         if (keytab[n].keycount > 0)
//             printf("%4d %s\n", keytab[n].keycount, keytab[n].keyword);
// }

// int binary(char *word, struct key tab[], int n) {
//     int low, high, mid, cond;

//     low = 0;
//     high = n - 1;
//     while (low <= high) {
//         mid = (low + high) / 2;
//         if ((cond = strcmp(word, tab[mid].keyword)) < 0)
//             high = mid - 1;
//         else if (cond > 0)
//             low = mid + 1;
//         else
//             return (mid);
//     }
//     return(-1);
// }

// int getword(char *w, int lim) {
//     int c, t;
//     if (type(c = *w++ = getch()) != LETTER) {
//         *w = '\0';
//         return(c);
//     }

//     while (--lim > 0) {
//         t = type(c = *w++ = getch());
//         if (t != LETTER && t != DIGIT) {{
//             ungetch(c);
//             break;
//         }}
//     }
//     *(w-1) = '\0';
//     return (LETTER);
// }

// int type(int c) {
//     if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
//         return(LETTER);
//     else if (c >= '0' && c <= '9')
//         return(DIGIT);
//     else
//         return(c);
// }


// struct date {
//     int day;
//     int month;
//     int year;
//     int yearday;
//     char mon_name[4];
// }

// static int day_tab[2][13] = {
//     {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
//     {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
// };

// int day_of_year(struct date *pd) {
//     int i, day, leap;

//     day = pd->day;
//     leap = pd->year % 4 == 0 && pd->year % 100 != 0 || pd->year % 400 == 0;
//     for (i = 1; i < pd->month; i++)
//         day += day_tab[leap][i];
//     return (day);
// }

// month_day(struct date *pd) /* set month and day from day of year */ {
//     int i, leap;

//     leap = pd->year % 4 == 0 && pd->year % 100 != 0 || pd->year % 400 == 0;
//     pd->day = pd->yearday;
//     for (i = 1; pd->day > day_tab[leap][i]; i++)
//         pd->day -= day_tab[leap][i];
//     pd->month = i;
// }

















// #define MAXLINE 1000

// struct lnode {
//     char *text;
//     struct lnode *next;
// };

// struct list {
//     struct lnode *head;
//     struct lnode *tail;
// };

// void list_add(struct list *lst, char *line) {
//     char *save = (char *) malloc(strlen(line) + 1);
//     strcpy(save, line);
//     struct lnode *new = (struct lnode *) malloc(sizeof(struct lnode));

//     if (lst->tail != NULL) lst->tail->next = new;
//     new->text = save;
//     new->next = NULL;
//     lst->tail = new;

//     if (lst->head == NULL) lst->head = new;
// }


// int main() {
//     char line[MAXLINE];
//     struct list mylist;
//     struct lnode *current;

//     mylist.head = NULL;
//     mylist.tail = NULL;

//     while(fgets(line, MAXLINE, stdin) != NULL) {
//         list_add(&mylist, line);
//     }

//     for (current = mylist.head; current != NULL; current = current->next) {
//         printf("%s", current->text);
//     }
// }




// #define LINES 100

// int main(int argc, char *argv[]) {
//     char *lineptr[LINES];
//     int nlines;
//     int strcmp(), numcpm();
//     int swap();
//     int numeric = 0;

//     if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'n')
//         numeric = 1;
//     if ((nlines = readlines(lineptr, LINES)) >= 0) {
//         if (numeric)
//             sort(lineptr, nlines, numcpm, swap);
//         else
//             sort(lineptr, nlines, strcmp, swap);
//         writelines(lineptr, nlines);
//     } else {
//         printf("input too big to sort\n");
//     }
// }

// int sort(char *v[], int n, int (*comp)(), int (*exch)()) {
//     int gap, i, j;

//     for (gap = n/2; gap > 0; gap /= 2)
//         for (i = gap; i < n; i++)
//             for (j = i - gap; j >= 0; j -= gap) {
//                 if ((*comp)(v[j], v[j + gap]) <= 0)
//                     break;
//                 (*exch)(&v[j], &v[j + gap]);
//             }
// }

// int numcmp(char *s1, char *s2) {
//     double atof(), v1, v2;

//     v1 = atof(s1);
//     v2 = atof(s2);
//     if (v1 < v2)
//         return(-1);
//     else if (v1 > v2)
//         return(1);
//     else
//         return(0);
// }

// int swap(char *px[], char *py[]) {
//     char *temp;

//     temp = *px;
//     *px = *py;
//     *py = temp;
// }



// int main(int argc, char *argv[]) {
//     int i;

//     for (i = 1; i < argc; i++)
//         printf("%s%c", argv[i], (i < argc-1) ? ' ' : '\n');
// }


// int main(int argc, char *argv[]) {
//     while (--argc > 0)
//         printf("%s%c", *++argv, (argc > 1) ? ' ' : '\n');
// }


// int main(int argc, char *argv[]) {
//     while (--argc > 0)
//         printf((argc > 1) ? "%s " : "%s\n", *++argv);
// }

// #define MAXLINE 1000

// int main(int argc, char *argv[]) { /* find pattern from first argument */
//     char line[MAXLINE];

//     if (argc != 2)
//         printf("Usage: find pattern\n");
//     else
//         while (getline(line, MAXLINE) > 0)
//             if (index(line, argv[1] >= 0))
//                 printf("%s", line);
// }

// int main(int argc, char *argv[]) {
//     char line[MAXLINE], *s;
//     long lineno = 0;
//     int except = 0, number = 0;

//     while (--argv > 0 && (*++argv)[0] == '-')
//         for (s = argv[0] + 1; *s != '\0'; s++)
//             switch(*s) {
//                 case 'x':
//                     except = 1;
//                     break;
//                 case 'n':
//                     number = 1;
//                     break;
//                 default:
//                     printf("find: illegal option%c\n", *s);
//                     argc = 0;
//                     break;
//             }
//     if (argc != 1)
//         printf("Usage: find -x -n pattern\n");
//     else
//         while (getline(line, MAXLINE) > 0) {
//             lineno++;
//             if ((index(line, *argv) >= 0) != except) {
//                 if (number)
//                     printf("%ld: ", lineno);
//                 printf("%s", line);
//             }
//         }
// }




// int getline(char s[], int maxlen)
// {
//     int c, i;

//     for (i = 0; i < maxlen - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
//         s[i] = c;

//     if (c == '\n')
//     {
//         s[i] = c; // Include newline character
//         ++i;
//     }

//     s[i] = '\0'; // Null-terminate the string
//     return i;    // Return the length of the line
// }

// int index(char s[], char t[]) { /* see if t is present in s */
//     int i, j, k;

//     for (i = 0; s[i] != '\0', i++) {
//         for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
//             ;
//         if (t[k] == '\0')
//             return i;
//     }

//     return -1;
// }





// char *month_name(int n) {
//     /* return name of the n-th month */
//     static char *name[] = {
//         "illegal month",
//         "January",
//         "February",
//         "March",
//         "April",
//         "May",
//         "June",
//         "July",
//         "August",
//         "September",
//         "October",
//         "November",
//         "December"
//     };

//     return((n < 1 || n > 12) ? name[0] : name[n]);
// }



// #define LINES 100 /* max lines to be sorted */
// #define MAXLEN 1000
// #define ALLOCSIZE 1000 /* size of available space */

// static char allocbuf[ALLOCSIZE]; /* storage for alloc */
// static char *allocp = allocbuf;  /* next free position */

// int main() {
//     char *lineptr[LINES]; /* pointers to text lines */
//     int nlines; /* number of input lines read */
//     int sort(), readlines(), writelines(), get_line();

//     if ((nlines = readlines(lineptr, LINES)) >= 0) {
//         sort(lineptr, nlines);
//         writelines(lineptr, nlines);
//     }
//     else
//         printf("input too big to sort\n");
// }


// int get_line(char s[], int maxlen) {
//     int c, i;

//     for (i = 0; i < maxlen - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
//         s[i] = c;
//     if (c == '\n') {
//         s[i] = c;
//         ++i;
//     }

//     s[i] = '\0';
//     return i;
// }

// int readlines(char *lineptr[], int maxlines) {
//     int len, nlines;
//     char *p, *alloc(), line[MAXLEN];

//     nlines = 0;
//     while ((len = get_line(line, MAXLEN)) > 0)
//         if (nlines >= maxlines)
//             return(-1);
//         else if ((p = alloc(len)) == NULL)
//             return(-1);
//         else {
//             line[len - 1] = '\0'; /* zap newline */
//             strcpy(p, line);
//             lineptr[nlines++] = p;
//         }
//     return (nlines);
// }

// int writelines(char *lineptr[], int nlines) {
//     /* write output lines */
//     while (--nlines >= 0)
//         printf("%s\n", *lineptr++);
// }


// int sort(char *v[], int n) {
//     int gap, i, j;
//     char *temp;

//     for (gap = n/2; gap > 0; gap /= 2)
//         for (i = gap; i < n; i++)
//             for (j = i - gap; j >= 0; j -= gap) {
//                 if (strcmp(v[j], v[j + gap]) <= 0)
//                     break;
//                 temp = v[j];
//                 v[j] = v[j + gap];
//                 v[j + gap] = temp;
//             }
// }

// char *alloc(int n) /* return pointer to n characters */
// {
//     if (allocp + n <= allocbuf + ALLOCSIZE) {
//         /* fits */
//         allocp += n;
//         return(allocp - n); /* old p */
//     } else {
//         /* not enough room */
//         return (NULL);
//     }
// }




// static int day_tab[2][13] = {
//     {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
//     {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
// };

// int main() {
//     int month, day, month_day(), day_of_year();

//     month_day(2023, 64, &month, &day);

//     printf("Month: %d, Day: %d\n", month, day);

//     printf("Day of year: %d\n", day_of_year(2023, 4, 20));
// }

// int day_of_year(int year, int month, int day) {
//     int i, leap;

//     leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
//     for (i = 1; i < month; i++)
//         day += day_tab[leap][i];
//     return(day);
// }

// int month_day(int year, int yearday, int *pmonth, int *pday) {
//     int i, leap;

//     leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
//     for(i = 1; yearday > day_tab[leap][i]; i++)
//         yearday -= day_tab[leap][i];
//     *pmonth = i;
//     *pday = yearday;
// }






// char *strsave(char *s) {
//     /* save string s somewhere */
//     char *p, *alloc();

//     if ((p = alloc(strlen(s) + 1)) != NULL)
//         strcpy(p, s);
//     return(p);
// }




// int strcmp(char s[], char t[]) {
//     /* return <0 if s < t, 0 if s==t, >0 if s>t */
//     int i;

//     i = 0;

//     while (s[i] == t[i])
//         if (s[i++] == '\0')
//             return(0);
//     return(s[i] - t[i]);
// }

// int strcmp(char *s, char *t) {
//     for ( ; *s == *t; s++, t++)
//         if (*s == '\0')
//             return(0);
//     return(*s - *t);
// }


// int strcopy(char s[], char t[]) {
//     /* copy t to s */
//     int i;

//     i = 0;
//     while ((s[i] = t[i]) != '\0')
//         i++;
    
// }

// int strcpy(char *s, char *t) {
//     /* copy to to s, pointer version */
//     while ((*s = *t) != '\0') {
//         s++;
//         t++;
//     }
// }

// int strcpy(char *s, char *t) {
//     /* copy t to s, pointer 2 */
//     while (*s++ = *t++)
//         ;
// }





// int main() {
//     int str_len();
//     char str[6];
//     str[0] = 'h';
//     str[1] = 'e';
//     str[2] = 'l';
//     str[3] = 'l';
//     str[4] = 'o';
//     printf("%s\n", str);
//     printf("%d\n", str_len(str));
// }

// int str_len(char *s)
// {
//     /* return length of string s */
//     char *p = s;

//     while (*p != '\0')
//         p++;
//     return(p - s);
// }

// #define NULL 0 /* pointer value for error report */
// #define ALLOCSIZE 1000 /* size of available space */

// static char allocbuf[ALLOCSIZE]; /* storage for alloc */
// static char *allocp = allocbuf; /* next free position */

// char *alloc(int n) /* return pointer to n characters */
// {
//     if (allocp + n <= allocbuf + ALLOCSIZE) {
//         /* fits */
//         allocp += n;
//         return(allocp - n); /* old p */
//     } else {
//         /* not enough room */
//         return (NULL);
//     }
// }

// int free(char *p) {
//     /* free storage pointed to by p */
//     if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
//         allocp = p;
// }






// int strlen( char *s) {
//     int n;

//     for (n = 0; *s != '\0'; s++)
//         n++;
//     return(n);
// }





// #define SIZE 10

// int main() {
//     int n, v, array[SIZE];
//     int get_int();

//     for (n = 0; n < SIZE && get_int(&v) != EOF; n++)
//         array[n] = v;
// }

// int get_int(int *pn) {
//     int c, sign;

//     while ((c = getch()) == ' ' || c == '\n' || c == '\t')
//         ;
//     sign = 1;
//     if (c == '+' || c == '-') {
//         sign = (c == '+') ? 1 : -1;
//         c = getch();
//     }
//     for (*pn = 0; c >= '0' && c <= '9'; c = getch())
//         *pn = 10 * *pn + c - '0';
//     *pn *= sign;
//     if (c != EOF)
//         ungetch(c);
//     return(c);
// }








// int main() {
//     int x, y;
//     x = 10;
//     y = 20;
//     void swap();
//     swap(&x, &y);
//     printf("x: %d\n", x);
//     printf("y: %d\n", y);
// }

// void swap(int *x, int *y) {
//     int temp;

//     temp = *x;
//     *x = *y;
//     *y = temp;
// }








// int main() {
//     int x = 42;  // A regular variable
//     int *p = &x; // p holds the address of x

//     printf("*p = %d\n", *p); // Output: *p = 42
//     *p = 100;                // Change the value at the address stored in p
//     printf("x = %d\n", x);   // Output: x = 100
// }





// int main() {
//     char ca[10], *cp;
//     int ia[10], *ip;

//     cp = ca + 1;
//     ip = ia + 1;

//     printf("ca %p cp %p\n", ca, cp);
//     printf("ia %p ip %p\n", ia, ip);
// }






// int main() {
//     int x, y;
//     int* px;

//     x = 42;
//     px = &x;
//     y = *px;
//     printf("%d %p %d\n", x, px, y);
// }


// int main() {
//     int x, y;
//     void func();

//     x = 42;
//     y = 43;
//     printf("main x=%d y=%d\n", x, y);
//     func(x, &y);
//     printf("back x=%d y=%d\n", x, y);
// }

// void func(a, pb)
//     int a, *pb;
// {
//     a = 1;
//     *pb = a;
// }







// printd(int n) {
//     /* print n in decimal */
//     char s[10];
//     int i;

//     if (n < 0) {
//         putchar('-');
//         n = -n;
//     }

//     i = 0;
//     do {
//         s[i++] = n % 10 + '0'; /* get next char */
//     } while ((n /= 10) > 0); /* discard it */

//     while (--i >= 0)
//         putchar(s[i]);
// }

// recursiveprint(int n) {
//     int i;

//     if (n < 0) {
//         putchar('-');
//         n = -n;
//     }

//     if ((i = n/10) != 0)
//         recursiveprint(i);

//     putchar(n % 10 + '0');
// }




// #define MAXOP 20 /* max size of operand, operator */
// #define NUMBER '0' /* signal that number found */
// #define TOOBIG '9' /* signal that string is too big */
// #define MAXVAL 100 /* maximum depth of val stack */
// #define BUFSIZE 100

// char buf[BUFSIZE]; /* buffer for ungetch */
// int bufp = 0; /* next free position in buf */

// int sp = 0; /* stack pointer */
// double val[MAXVAL]; /* value stack */

// int getch() /* get a (possibly pushed back) character */
// {
//     return ((bufp > 0) ? buf[--bufp] : getchar());
// }

// int ungetch(c) /* push character back on input */
// int c;
// {
//     if (bufp > BUFSIZE)
//         printf("ungetch: too many characters\n");
//     else
//         buf[bufp++] = c;
// }

// int clear()
// {
//     sp = 0;
// }

// int getop(s, lim) /* get next operator or operand */
// char s[];
// int lim;
// {
//     int i, c;

//     while ((c = getch()) == ' ' || c == '\t' || c == '\n')
//         ;
//     if (c != '.' && (c < '0' || c > '9'))
//         return (c);
//     s[0] = c;
//     for (i = 1; (c = getchar()) >= '0' && c <= '9'; i++)
//         if (i < lim)
//             s[i] = c;
//     if (c == '.') { /* collect fraction */
//         if (i < lim)
//             s[i] = c;
//         for (i++; (c=getchar()) >= '0' && c <= '9'; i++)
//             if (i < lim)
//                 s[i] = c;
//     }
//     if (i < lim) { /* number is ok */
//         ungetch(c);
//         s[i] = '\0';
//         return (NUMBER);
//     } else { /* it's too big; skip rest of the line */
//         while (c != '\n' && c != EOF)
//             c = getchar();
//         s[lim - 1] = '\0';
//         return(TOOBIG);
//     }
// }

// double push(double f) /* push f onto value stack */
// {
//     if (sp < MAXVAL)
//         return(val[sp++] = f);
//     else {
//         printf("error: stack full\n");
//         clear();
//         return(0);
//     }
// }

// double pop() {
//     if (sp > 0)
//         return(val[--sp]);
//     else {
//         printf("error: stack empty\n");
//         clear();
//         return(0);
//     }
// }

// int main() {
//     int type;
//     char s[MAXOP];
//     double op2;

//     while ((type = getop(s, MAXOP)) != EOF)
//         switch (type) {
//             case NUMBER:
//                 push(atof(s));
//                 break;
//             case '+':
//                 push(pop() + pop());
//                 break;
//             case '*':
//                 push(pop() * pop());
//                 break;
//             case '-':
//                 op2 = pop();
//                 push(pop() - op2);
//                 break;
//             case '/':
//                 op2 = pop();
//                 if (op2 != 0.0)
//                     push(pop() / op2);
//                 else
//                     printf("zero divisor popped\n");
//                 break;
//             case '=':
//                 printf("\t%f\n", push(pop()));
//                 break;
//             case 'c':
//                 clear();
//                 break;
//             case TOOBIG:
//                 printf("%.20s ... is too long\n", s);
//                 break;
//             default:
//                 printf("unknown command %c\n", type);
//                 break;
//         }
// }



// double atof(s) /* convert string to double */
// char s[];
// {
//     double val, power;
//     int i, sign;

//     for (i = 0; s[i] == ' ' || s[i] == '\n' || s[i] == '\t'; i++)
//         ; /* skip white space */
//     sign = 1;
//     if (s[i] == '+' || s[i] == '-') /* sign */
//         sign = (s[i++]=='+') ? 1 : -1;
//     for (val = 0; s[i] >= '0' && s[i] <= '9'; i++)
//         val = 10 * val + s[i] - '0';
//     if (s[i] == '.')
//         i++;
//     for (power = 1; s[i] >= '0' && s[i] <= '9'; i++) {
//         val = 10 * val + s[i] - '0';
//         power *= 10;
//     }
//     return(sign * val / power);
// }



// #define MAXLINE 1000

// int main() {
//     char line[MAXLINE];

//     while (get_line(line, MAXLINE) > 0)
//         if (index(line, "the") >= 0)
//             printf("%s\n", line);
// }

// int get_line(s, lim)
// char s[];
// int lim;
// {
//     int c, i;

//     for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
//         s[i] = c;
//     if (c == '\n') {
//         s[i] = c;
//         ++i;
//     }
//     s[i] = '\0';
//     return(i);
// }

// int index(s, t)
// char s[], t[];
// {
//     int i, j, k;

//     for (i = 0; s[i] != '\0'; i++) {
//         for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
//             ;
//         if (t[k] == '\0')
//             return(i);
//     }
//     return(-1);
// }









// void itoa(char s[], int n);
// void printBinary(int binary);
// void reverse(char s[]);
// int strlen(char s[]);

// int main()
// {
//     char s[12];
//     int n = 200;
//     printBinary(n);
// }

// void printBinary(int binary) {
//     printf("%d\n", binary);
//     for (int i = 31; i >= 0; i--) {
//         printf("%d", (binary >> i) & 1);
//         if (i % 4 == 0) printf(" ");
//     }
//     printf("\n");
// }

// void itoa(char s[], int n) {
//     int i, sign;

//     if ((sign = n) < 0)
//         n = -n;
//     i = 0;

//     do {
//         s[i++] = n % 10 + '0';
//     } while ((n /= 10) > 0);

//     if (sign < 0)
//         s[i++] = '-';
//     s[i] = '\0';
//     reverse(s);
// }


// void reverse(char s[])  /* reverse string s in place */
// {
//     int c, i, j;

//     for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
//         c = s[i];
//         s[i] = s[j];
//         s[j] = c;
//     }
// }

// /* strlen: return length of s */
// int strlen(char s[])
// {
//     int i = 0;
//     while (s[i] != '\0')
//         ++i;
//     return i;
// }





// void shell(int v[], int n) { /* sort v[0]...v[n-1] into increasing order */
//     int gap, i, j, temp;

//     for (gap = n/2; gap > 0; gap /= 2)
//         for (i = gap; i < n; i++)
//             for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) {
//                 temp = v[j];
//                 v[j] = v[j + gap];
//                 v[j + gap] = temp;
//             }
// }





// int atoi(char s[]);

// int main() {
//     char str[] = "-123";

//     printf("%d\n", atoi(str));
// }


// int atoi(char s[]) /* convert numeric strings to integer */
// {
//     int i, n, sign;

//     for (i = 0; s[i]==' ' || s[i]=='\n' || s[i]=='\t'; i++)
//         ; /* skip white spaces */
//     sign = 1;
//     if (s[i] == '+' || s[i] == '-') /* sign */
//         sign = (s[i++]=='+') ? 1 : -1;
//     for (n = 0; s[i] >= '0' && s[i] <= '9'; i++)
//         n = 10 * n + s[i] - '0';
//     return (sign * n);
// } 





// int main() { /* count digits, white space, others */
//     int c, i, nwhite, nother, ndigit[10];

//     nwhite = nother = 0;
//     for (i = 0; i < 10; i++)
//         ndigit[i] = 0;

//     while ((c = getchar()) != EOF)
//         switch (c) {
//             case '0':
//             case '1':
//             case '2':
//             case '3':
//             case '4':
//             case '5':
//             case '6':
//             case '7':
//             case '8':
//             case '9':
//                 ndigit[c-'0']++;
//                 break;
//             case ' ':
//             case '\n':
//             case '\t':
//                 nwhite++;
//                 break;
//             default:
//                 nother++;
//                 break;
//         }

//     printf("digits =");
//     for (i = 0; i < 10; i++)
//         printf(" %d", ndigit[i]);
//     printf("\nwhite space = %d, other = %d\n", nwhite, nother);
// }







// int binary(int x, int v[], int n);

// int main() {
//     int v[] = {1, 5, 19, 20};
//     printf("%d\n", binary(5, v, 4));
// }

// int binary(x, v, n) /* find x in v[0] ... v[n - 1] */
// int x, v[], n;
// {
//     int low, high, mid;

//     low = 0;
//     high = n - 1;
//     while (low <= high)
//     {
//         mid = (low+high) / 2;
//         if (x < v[mid])
//             high = mid - 1;
//         else if (x > v[mid])
//             low = mid + 1;
//         else /* found match */
//             return (mid);
//     }
//     return(-1);
// }







// int main() {
//     int bitcount(unsigned n);
//     printf("%d", bitcount(5255));
// }

// int bitcount(n)
// unsigned n;
// {
//     int b;

//     for (b = 0; n != 0; n >>=1 )
//         if (n & 01)
//             b++;
//     return(b);
// }




// char* strcat(char s[], char t[]);

// int main() {
//     char s[] = "hello";
//     char t[] = "world";
//     printf("%s\n", strcat(s, t));
// }

// char* strcat(char s[], char t[]) {
//     int i, j;
//     i = j = 0;
//     while (s[i] != '\0')
//         i++;
//     while ((s[i++] = t[j++]) != '\0')
//         ;
//     return s;
// }


// int main() {
//     char* squeeze(char s[], int c);
//     char str[] = "hello";
//     squeeze(str, 'l');
//     printf("%s\n", str);
// }

// char* squeeze(char s[], int c) {
//     int i, j;
    
//     for (i = j = 0; s[i] != '\0'; i++)
//         if (s[i] != c)
//             s[j++] = s[i];
//     s[j] = '\0';
//     return s;
// }



// #define N 4

// void detab();

// int main() {
//     int c;

//     while ((c = getchar()) != EOF) {
//         if (c == '\t') {
//             detab();
//         } else {
//             putchar(c);
//         }
//     }
// }

// void detab() {
//     for (int i = 0; i < N; i++) {
//         putchar(' ');
//     }
// }




// #define MAXLINE 1000

// char line[MAXLINE];
// char save[MAXLINE];
// int max;

// void main() {
//     int len;
//     extern int max;
//     extern char save[];
//     int getline();
//     max = 0;
//     while ((len = getline()) > 0)
//         if (len > max) {
//             max = len;
//             void copy();
//         }
//     if (max > 0)
//         printf("%s", save);
// }

// int get_line() {
//     int c, i;
//     extern char line[];

//     for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; i++)
//         line[i] = c;
//     if (c == '\n') {
//         line[i] = c;
//         i++;
//     }
//     line[i] = '\0';
//     return(i);
// }

// void copy() {
//     int i;
//     extern char line[], save[];

//     i = 0;
//     while ((save[i] = line[i]) != '\0')
//         i++;
// }






// #define MAXLINE 1000

// int main() {
//     int len;
//     int max;
//     char line[MAXLINE];
//     char save[MAXLINE];
//     int get_line();
//     int copy();

//     max = 0;

//     while ((len = get_line(line, MAXLINE)) > 0)
//         if (len > max) {
//             max = len;
//             copy(line, save);
//         }
//     if (max > 0)
//         printf("%s", save);
// }

// int get_line(s, lim)
// char s[];
// int lim;
// {
//     int c, i;

//     for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
//         s[i] = c;
//     if (c == '\n') {
//         s[i] = c;
//         i++;
//     }
//     s[i] = '\0';
//     return(i);
// }

// int copy(s1, s2)
// char s1[], s2[];
// {
//     int i;

//     i = 0;
//     while ((s2[i] = s1[i]) != '\0')
//         i++;
// }



// int main() {
//     int lowercase();
//     int c;

//     while ((c = getchar()) != EOF) {
//         putchar(lowercase(c));
//     }
// }

// int lowercase(c)
// int c; {
//     if (c >= 'A' && c <= 'Z')  {
//         return c + ('a' - 'A');
//     }
//     return c;
// }




// int main() {
//     int i;
//     int power();

//     for (i = 0; i < 10; i++)
//         printf("%d %d %d\n", i, power(2, i), power(-3, i));
// }

// int power(x, n)
// int x, n;
// {
//     int i, p;
//     p = 1;
//     for (i = 1; i <= n; i++)
//         p = p * x;
//     return (p);
// }


// #define IN 1
// #define OUT 0
// #define MAX_WORD_LENGTH 10

// int main() {
//     int c, state = OUT;
//     int word_length = 0;
//     int word_lengths[MAX_WORD_LENGTH + 1] = {0};

//     while ((c = getchar()) != EOF) {
//         if (c == ' ' || c == '\n' || c == '\t') {
//             if (state == IN) {
//                 state = OUT;
//                 if (word_length > 0 && word_length <= MAX_WORD_LENGTH)
//                     word_lengths[word_length]++;
//                 word_length = 0;
//             }
//         } else {
//             state = IN;
//             word_length++;
//         }
//     }

//     printf("\Horizontal Histogram:\n");
//     for (int i = 1; i <= MAX_WORD_LENGTH; i++) {
//         printf("%2d: ", i);
//         for (int j = 0; j < word_lengths[i]; j++) {
//             printf("#");
//         }
//         printf("\n");
//     }

//     return 0;
// }

// #define YES 1
// #define NO 0

// int main() {
//     int c, nl, nw, nc, inword;

//     inword = NO;
//     nl = nw = nc = 0;
//     while ((c = getchar()) != EOF) {
//         ++nc;
//         if (c == '\n')
//             ++nl;
//         if (c == ' ' || c == '\n' || c == '\t')
//             inword = NO;
//         else if (inword == NO) {
//             inword = YES;
//             ++nw;
//         }
//     }

//     printf("%d %d %d\n", nl, nw, nc);
// }

// int main() {
//     int c, i, nwhite,nother;
//     int ndigit[10];

//     nwhite = nother = 0;
//     for (i = 0; i < 10; i++)
//         ndigit[i] = 0;
    
//     while ((c = getchar()) != EOF)
//         if (c >= '0' && c <= '9')
//             ++ndigit[c -'0'];
//         else if (c == ' ' || c == '\n' || c == '\t')
//             ++nwhite;
//         else
//             ++nother;

//     printf("digits =");

//     for (i = 0; i < 10; ++i)
//         printf(" %d", ndigit[i]);

//     printf("\nwhite space = %d, other = %d\n", nwhite, nother);
// }


// int main() {
//     int c, prev = 0;

//     while ((c = getchar()) != EOF) {
//         if (c == ' ' && prev == ' ')
//             continue;
//         putchar(c);
//         prev = c;
//     }
// }


// int main() {
//     int c, blanks;

//     blanks = 0;

//     while ((c = getchar()) != EOF)
//         if (c == ' ')
//             ++blanks;
//     printf("%d\n", blanks);
// }


// int main() {
//     int c, nl;

//     nl = 0;
//     while ((c = getchar()) != EOF)
//         if (c == '\n')
//             ++nl;
//     printf("%d\n", nl);
// }


// int main() {
//     double nc;
//     int c;
//     while ((c = getchar()) != EOF) {
//         if (c != '\n')
//             ++nc;
//     }
//     printf("%.0f\n",nc);
// }

// int main() {
//     long nc;
//     nc = 0;
//     while (getchar() != EOF)
//         ++nc;
//     printf("%ld\n", nc);
// }


// int main() {
//     // we use int instead of char for c in case it ends up being an EOF file
//     int c;
//     while ((c=getchar()) != EOF)
//         putchar(c);
// }


// int main() {
//     int c;
//     c = getchar();

//     while (c != EOF) {
//         putchar(c);
//         c = getchar();
//     }
// }


// int main() {
//     char c;
//     c = getchar();
//     printf("%c", c);
// }



// #define LOWER 0
// #define UPPER 300
// #define STEP 20

// int main() {
//     int fahr;
//     for (fahr = UPPER; fahr >= LOWER; fahr = fahr - STEP)
//         printf("%4d %6.1f\n", fahr, (5.0/9.0) * (fahr-32));
// } 



    // int lower, upper, step;
    // float fahr, celsius;
    // lower = 0;
    // upper = 300;
    // step = 20;
    // fahr = lower;

    // while (fahr <= upper) {
    //     celsius = (5.0/9.0) * (fahr-32.0);
    //     printf("%4.0f %6.1f\n", fahr, celsius);
    //     fahr = fahr + step;
    // }


// int main() {
//     char x[] = "Hello";
//     int find_length();
//     int length = find_length(x);
//     void reverse_string();
//     reverse_string(length, x);
//     printf("%s\n", x);
// }

// int find_length(string)
//     char string[];
// {
//     int i;
//     int length = 0;
//     for (i=0; string[i]; i++) {
//         length++;
//     }

//     return length;
// }

// void reverse_string(length, string)
//     int length;
//     char string[]; {
//         int last = length - 1;
//         int i;
//         char temp;
//         if (length % 2 == 0) {
//             for (i = 0; i <= last; i++) {
//                 temp = string[i];
//                 string[i] = string[last];
//                 string[last] = temp;
//                 last--;
//             }
//         } else {
//             for (i = 0; i <= last; i++) {
//                 if (i != last) {
//                     temp = string[i];
//                     string[i] = string[last];
//                     string[last] = temp;
//                     last--;
//                 }
//             }
//         }
//     }

// int main() {
//     char x[] = "Hello";
//     int py_len();
//     printf("%s %d\n", x, py_len(x));
// }

// int py_len(self)
//     char self[];
// {
//     int i;
//     for (i=0; self[i]; i++);
//     return i;
// }

    // char x[3];
    // x[0] = 'H';
    // x[1] = 'O';
    // x[2] = 'E';

    // printf("%s\n", x);

    // char x[10];
    // int i;
    // for (i=0; i<100; i++) x[i] = '*';
    // printf("%s\n", x);

// int main() {
//     int mymult();
//     int retval;

//     retval = mymult(6, 7);
//     printf("Answer: %d\n", retval);
// }

// int mymult(a, b)
//     int a, b;
// {
//     int c = a * b;
//     return c;
// }


    // int guess;
    // while(scanf("%d", &guess) != EOF) {
    //     if (guess == 42) {
    //         printf("Nice work!\n");
    //         break;
    //     }
    //     else if (guess < 42) {
    //         printf("Too low\n");
    //     }
    //     else {
    //         printf("Too high\n");
    //     }
    // }

    // int first = 1;
    // int val, maxval, minval;
    // while(scanf("%d", &val) != EOF) {
    //     if (first || val > maxval) maxval = val;
    //     if (first || val < minval) minval = val;
    //     first = 0;
    // }

    // printf("Maximum %d\n", maxval);
    // printf("Minimum %d\n", minval);

    // int i;
    // for (i=0; i<5; i++) {
    //     printf("%d\n", i);
    // }

    // char line[1000];
    // FILE *hand;
    // hand = fopen("romeo.txt", "r");
    // while( fgets(line, 1000, hand) != NULL) {
    //     printf("%s", line);
    // }
    // fclose(hand);

    // char line[1000];
    // printf("Enter line\n");
    // scanf("%[^\n]1000s", line);
    // printf("Line: %s\n", line);

    // char name[100];
    // printf("Enter name\n");
    // scanf("%100s", name);
    // printf("Hello %s\n", name);

    // int usf, euf;
    // printf("Enter US Floor\n");
    // scanf("%d", &usf);
    // euf = usf - 1;
    // printf("EU Floor %d\n", euf);

    // printf("Hello world\n");
    // printf("Answer %d\n", 42);
    // printf("Name %s\n", "Sarah");
    // printf("x %.1f i %d\n", 3.5, 100);