#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct dnode
{
    char *key;
    char *value;
    struct dnode *next;
};

struct pydict
{
    struct dnode *head;
    struct dnode *tail;
    int count;
};

struct pydict *pydict_new()
{
    struct pydict *p = malloc(sizeof(*p));
    p->head = NULL;
    p->tail = NULL;
    p->count = 0;
    return p;
}

int pydict_len(const struct pydict *self)
{
    return (self->count);
}

void pydict_del(struct pydict *self)
{
    struct dnode *cur, *next;
    cur = self->head;
    while (cur)
    {
        free(cur->key);
        free(cur->value);
        next = cur->next;
        free(cur);
        cur = next;
    }
    free((void *)self);
}

struct dnode *pydict_find(struct pydict *self, char *key)
{
    struct dnode *cur;
    cur = self->head;
    while (cur)
    {
        if (strcmp(cur->key, key) == 0)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void pydict_put(struct pydict *self, char *key, char *value)
{
    struct dnode *cur;
    cur = pydict_find(self, key);
    if (cur)
    {
        char *new_value = malloc(strlen(value) + 1);
        if (!new_value)
        {
            fprintf(stderr, "Memory reallocation failed\n");
            return;
        }
        free(cur->value);
        cur->value = new_value;
        strcpy(cur->value, value);
        return;
    }

    struct dnode *new_node = malloc(sizeof(*new_node));
    if (!new_node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->next = NULL;

    new_node->key = malloc(strlen(key) + 1);
    if (!new_node->key)
    {
        fprintf(stderr, "Memory reallocation failed\n");
        free(new_node);
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->key, key);

    new_node->value = malloc(strlen(value) + 1);
    if (!new_node->value)
    {
        fprintf(stderr, "Memory reallocation failed\n");
        free(new_node->key);
        free(new_node);
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->value, value);

    if (self->head == NULL)
    {
        self->head = new_node;
        self->tail = new_node;
    }
    else
    {
        self->tail->next = new_node;
        self->tail = new_node;
    }
    self->count++;
}

char *pydict_get(struct pydict *self, char *key)
{
    struct dnode *cur;
    cur = pydict_find(self, key);
    if (cur)
        return cur->value;
    return NULL;
}

void pydict_print(struct pydict *self)
{
    struct dnode *cur;
    cur = self->head;
    printf("{");
    while (cur)
    {
        printf("'%s': '%s'", cur->key, cur->value);
        cur = cur->next;
        if (cur)
            printf(", ");
    }
    printf("}\n");
}

int main(void)
{
    struct pydict *dct = pydict_new();
    pydict_put(dct, "z", "Catch phrase");
    pydict_print(dct);
    pydict_put(dct, "z", "W");
    pydict_print(dct);
    pydict_put(dct, "y", "B");
    pydict_put(dct, "c", "C");
    pydict_put(dct, "a", "D");
    pydict_print(dct);
    printf("Length=%d\n", pydict_len(dct));

    printf("z=%s\n", pydict_get(dct, "z"));
    printf("x=%s\n", pydict_get(dct, "x"));

    printf("\nDump\n");
    for (struct dnode *cur = dct->head; cur != NULL; cur = cur->next)
    {
        printf("%s=%s\n", cur->key, cur->value);
    }
    pydict_del(dct);
}

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
