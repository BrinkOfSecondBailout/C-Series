#include <stdio.h>


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