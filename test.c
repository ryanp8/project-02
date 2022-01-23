#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

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

char **split(char *input, char *tok) {
    int tok_count = strcount(input, tok[0]);
    char **parsed = calloc(tok_count + 2, sizeof(char*));
    int i = 0;
    while(input) {
        parsed[i] = strsep(&input, tok);
        if (input) {
            input += strlen(tok) - 1;
        }
        i++;
    }
    return parsed;
}

int run_command(char *command, char *output) {

    char **parsed = split(command, " ");
    int stdout_dup = dup(STDOUT_FILENO);

    int f = fork();
    if (f) {
        int w, status;
        w = waitpid(f, &status, 0);
        printf("PARENT ENDED\n");
    }
    else {
        int fds[2];
        pipe(fds);
        int f2 = fork();
        if (f2) {
            int w, status;
            w = waitpid(f2, &status, 0);
            close(fds[WRITE]);
            read(fds[READ], output, 1024);
            kill(getpid(), 2);
        }
        else {
            close(fds[READ]);
            dup2(fds[WRITE], STDOUT_FILENO);
            int res = execvp(parsed[0], parsed);
        }
    }
    dup2(stdout_dup, STDOUT_FILENO);
    
    return 0;
}





int main(int argc, char* argv[]) {

    if (argc > 1) {
        // char *output;
        // int shmd;
        // shmd = shmget(24602, 1024, IPC_CREAT | 0640);
        // output = shmat(shmd, 0, 0);

        // // output = shmget(24602, 0, 0);
        // run_command(argv[1], output);

        // int fd = open("test.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
        // write(fd, output, 1024);
        // printf("[%s], %d\n", output, getpid());
        // shmdt(output);
        // shmctl(shmd, IPC_RMID, 0); 
        char *content = malloc(100);
        int fs = 20;
        int fd = open(argv[1], O_RDONLY);
        read(fd, content, fs);
        printf("[%s]\n", content);
    }


    // char* s = calloc(7, 1);

    // strcpy(s, "hello");

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
    // printf("%d\n", line_len("hello\nab", 2));

    
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