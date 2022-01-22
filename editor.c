#include "editor.h"

WINDOW *open_editor(char *filname) {
    WINDOW *win = newwin(0, 0, WINDOW_X, WINDOW_Y);
    noecho();
    cbreak();
    keypad(win, TRUE);
    wmove(win, WINDOW_Y, WINDOW_X);
    wrefresh(win);

    return win;
}


char* read_input(WINDOW *win, char *content, off_t *fs, int *x, int *y, int *top_row, int max_x, int max_y) {
    int c = wgetch(win);
    off_t pos;
    int space;
    char at_end;
    switch(c) {
        case KEY_UP:
            if (*y == 0 && *top_row > 0) {
                (*top_row)--;
                display_content(win, content, char_instance(content, '\n', *top_row) + 1, *fs);
                wmove(win, WINDOW_Y, *x);
            }
            else if (*y > WINDOW_Y) {
                (*y)--;
                if (*x > line_len(content, *y)) {
                    *x = line_len(content, *y);
                }
                wmove(win, *y, *x);
            }
            // mvwprintw(win, 0, 10, "%d, %d, %d up", *top_row, *y, max_y);
            // wmove(win, *y, *x);
            // wrefresh(win);
            break;
        case KEY_DOWN:

            at_end = (*top_row + *y >= strcount(content, '\n'));
            
            if (*y == max_y - 1 && !at_end) {
                (*top_row)++;
                display_content(win, content, char_instance(content, '\n', *top_row) + 1, *fs);
            }
            else if (!at_end) {
                (*y)++;
                if (*x > line_len(content, *y)) {
                    *x = line_len(content, *y);
                }
                wmove(win, *y, *x);
            }
            // mvwprintw(win, 0, 10, "%d, %d, %d down", *top_row, *y, max_y);
            // wmove(win, *y, *x);
            // wrefresh(win);
            break;
        case KEY_LEFT:
            if (*x > WINDOW_X) {
                wmove(win, *y, --(*x));
            }
            break;
        case KEY_RIGHT:
            if (*x < line_len(content, *y)) {
                wmove(win, *y, ++(*x));
            }
            break;
        case KEY_F0:
        case KEY_BACKSPACE:
        case 127:
        case KEY_DL:
        case '\b':
            pos = char_instance(content, '\n', *y) + *x + 1;
            if (pos > 0) {
                char deleted = content[pos - 1];
                int prev_line_len = line_len(content, *y - 1);
                content[pos - 1] = 0;
                off_t i;
                for (i = pos - 1; i < *fs - 1; i++) {
                    char tmp = content[i];
                    content[i] = content[i + 1];
                    content[i + 1] = tmp;
                }
                (*fs)--;
                display_content(win, content, char_instance(content, '\n', *top_row) + 1, *fs);
                (*x)--;
                if (deleted == '\n') {
                    (*y)--;
                    *x = prev_line_len;
                }
                wmove(win, *y, *x);
                content = realloc(content, *fs);
            }            
            break;
        case '\t':
        case KEY_STAB:
            for (space = 0; space < TAB_WIDTH; space++) {
                add_char(&content, c, fs, *x, *top_row + *y);
                display_content(win, content, char_instance(content, '\n', *top_row) + 1, *fs);
                (*x)++;
                wmove(win, *y, *x);
            }
            break;
        default:
            add_char(&content, c, fs, *x, *top_row + *y);
            display_content(win, content, char_instance(content, '\n', *top_row) + 1, *fs);
            if (c == '\n') {
                *x = WINDOW_X;
                if (*y + 1 == max_y) {
                    (*top_row)++;
                    display_content(win, content, char_instance(content, '\n', *top_row) + 1, *fs);
                }
                else {
                    (*y)++;
                }
            }
            else {
                (*x)++;
            }
            wmove(win, *y, *x);
    }
    wrefresh(win);

    return content;
}


void display_content(WINDOW *win, char *content, int start_pos, off_t fs) {
    wclear(win);
    int x = WINDOW_X;
    int y = WINDOW_Y;
    int i;
    for (i = start_pos; i < fs - 1; i++) { // fs - 1 to exclude trailing 0
        mvwaddch(win, y, x, content[i]);
        if (content[i] == '\n') {
            x = WINDOW_X;
            y++;
        }
        else {
            x++;
        }
    }
    // wprintw(win, content);  
}


void add_char(char **content, char c, off_t *fs, int x, int y) {
    (*fs)++;
    content[0] = realloc(content[0], *fs);
    off_t pos = char_instance(content[0], '\n', y) + x + 1; // current position of cursor in relation to raw text

    off_t i;
    for (i = *fs - 1; i > pos; i--) {
        char tmp = content[0][i];
        content[0][i] = content[0][i - 1];
        content[0][i - 1] = tmp;
    }
    content[0][pos] = (char) c; 
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
    return second - first - 1;
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