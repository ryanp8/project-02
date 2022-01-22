#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printc(char *c, int fs) {
    printf("[");
    for (int i = 0; i < fs; i++) {
        printf("%c", c[i]);
    }
    printf("]\n");
}

off_t char_instance(char *str, char c, off_t n) {
    off_t counter = 0;
    off_t i = 0;
    while (i < strlen(str)) {
        if (str[i] == c) {
            counter++;
            if (counter == n) return i;
        }
        i++;
    }
    return -1;
}

int strcount(char *str, char c) {
    int count = 0;
    while (*str) {
        if (*str == c) {
            count++;
        }
        str++;
    }
    return count;
}

int line_len(char *content, int y) {
    y++;
    if (y == 1) {
        int f = (int) char_instance(content, '\n', 1);
        if (f == -1) {
            return strlen(content);
        }
        return f;
    }
    int first = (int) char_instance(content, '\n', y - 1);
    int second = (int) char_instance(content, '\n', y);
    if (second == -1) {
        return strlen(content + first) - 1;
    }
    return second - first;
}


int main() {

    char* s = calloc(7, 1);

    strcpy(s, "hello");

    // int i;
    // for (i = 8; i > 3; i--) {
    //     char tmp = s[i];
    //     s[i] = s[i - 1];
    //     s[i - 1] = tmp;
    // }
    // s[3] = 'b';
    // printf("%d\n", i);

    // printf("%s\n", s);

    // printf("%d\n", strcount("aaa", 'a'));

    // printf("%d\n", line_len("hello\ngoodbye\nhello again", 0));
    printf("%d\n", line_len("hello\nab", 2));

    
    // char *a = "int i = 10;\nint j = 20;\nhello";
    // int i = char_instance(a, '\n', 2);
    // printf("%d\n", i);

    // char *c = calloc(0, sizeof(char));
    // int fs = 0;

    // for (int i = 0; i < 10; i++) {
    //     printf("%d\n", fs);
    //     fs++;
    //     c = realloc(c, fs * sizeof(char));
    //     c[fs - 1] = 'a';
    // }

    // printc(c, fs);



    return 0;
}