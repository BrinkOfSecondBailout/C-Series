#include <stdio.h>

static int day_tab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};









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