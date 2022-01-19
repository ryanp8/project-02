#include "editor.h"

WINDOW *open_editor(char *filname) {
    WINDOW *win = newwin(0, 0, WINDOW_X, WINDOW_Y);
    noecho();
    cbreak();
    keypad(win, TRUE);
    wmove(win, WINDOW_Y, WINDOW_X);
    box(win, 0, 0);
    wrefresh(win);

    return win;
}


char* read_input(WINDOW *win, char *content, off_t *fs, int *x, int *y) {
    int c = wgetch(win);
    switch(c) {
        case KEY_UP:
            if (*y > WINDOW_Y) {
                wmove(win, --(*y), *x);
                wrefresh(win);
            }
            break;
        case KEY_DOWN:
            wmove(win, ++(*y), *x);
            wrefresh(win);
            break;
        case KEY_LEFT:
            if (*x > WINDOW_X) {
                wmove(win, *y, --(*x));
                wrefresh(win);
            }
            break;
        case KEY_RIGHT:
            wmove(win, *y, ++(*x));
            wrefresh(win);
            break;
        default:
            (*fs)++;
			content = realloc(content, *fs);
            content[*fs - 2] = (char) c; // keep trailing 0
            display_content(win, content, *fs, x, y);
            
    }


    return content;
}

void display_content(WINDOW *win, char *content, off_t fs, int *x1, int *y1) {
    wclear(win);
    box(win, 0, 0);
    int x = WINDOW_X;
    int y = WINDOW_Y;
    int i;
    for (i = 0; i < fs - 1; i++) { // fs - 1 to exclude trailing 0
        mvwaddch(win, y, x++, content[i]);
        if (content[i] == '\n') {
            x = WINDOW_X;
            y++;
            wmove(win, y, x);
        }
    }

    *x1 = x;
    *y1 = y;
    wrefresh(win);
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