#include <stdio.h>
#include <stdlib.h>

#include "editor.h"

int main(int argc, char *argv[]) {
    
    if (argc > 1) {

		int running = 1;
		off_t fs = 1; // start at 1 so there's trailing 0;
		char *content = calloc(fs, sizeof(char));
		int x = WINDOW_X;
		int y = WINDOW_Y;
		int max_x, max_y;
		int top_row = 0;

		initscr();
        WINDOW *editor = open_editor(argv[1]);
		getmaxyx(editor, max_y, max_x);

		int c;
		while (running) {
			content = read_input(editor, content, &fs, &x, &y, &top_row, max_x, max_y);
		}

		endwin();
    }

    return 0;
}
