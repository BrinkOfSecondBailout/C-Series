#include <stdio.h>







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