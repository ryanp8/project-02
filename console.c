#include "console.h"

WINDOW *open_console(int start_y) {
    WINDOW *win = newwin(0, 0, start_y, 0);
    keypad(win, TRUE);
    return win;
}

char *read_console_input(WINDOW *win, char *input, int *mode, int* console_y) {
    echo();
    char *buf = malloc(1024);
    wgetstr(win, buf);
    return buf;
}


int run_command(char *command, char *output, char *content, char *filename, int fs) {

    if (strcmp(command, "w") == 0) {
        int fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        write(fd, content, fs - 1);
    }
    else if (strcmp(command, "q") == 0) {
        exit(0);
    }
    else if (strcmp(command, "wq") == 0) {
        int fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        write(fd, content, fs - 1);
        endwin();
        exit(0);
    }
    else {
        char **parsed = split(command, " ");
        int stdout_dup = dup(STDOUT_FILENO);

        int f = fork();
        if (f) {
            int w, status;
            w = waitpid(f, &status, 0);
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
            }
            else {
                close(fds[READ]);
                dup2(fds[WRITE], STDOUT_FILENO);
                int res = execvp(parsed[0], parsed);
            }
        }
        dup2(stdout_dup, STDOUT_FILENO);
    }

    
    
    return 0;
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
