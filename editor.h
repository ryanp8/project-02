#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>

#ifndef EDITOR_H
#define EDITOR_H

#define WINDOW_X 0
#define WINDOW_Y 0
#define TAB_WIDTH 4

WINDOW *open_editor(char *filename);
char* read_input(WINDOW *win, char *content, off_t *fs, int *x, int *y, int* top_row, int max_x, int max_y);
void add_char(char **content, char c, off_t *fs, int x, int y);
void display_content(WINDOW *win, char *content, int start_pos, off_t fs);
int line_len(char *content, int y);
int strcount(char *content, char c);
off_t char_instance(char *str, char c, off_t n);



#endif