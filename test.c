#include <stdio.h>
#include <stdlib.h>

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
    while (i < strlen(str) && counter < n) {
        if (str[i] == c) 
            counter++;
        i++;
    }
    return i;
}

int main() {

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