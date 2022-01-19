#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>

#ifndef EDITOR_H
#define EDITOR_H

#define WINDOW_X 1
#define WINDOW_Y 1

WINDOW *open_editor(char *filename);
char* read_input(WINDOW *win, char *content, off_t *fs, int *x, int *y);
void display_content(WINDOW *win, char *content, off_t fs, int *x, int *y);
off_t char_instance(char *str, char c, off_t n);



#endif