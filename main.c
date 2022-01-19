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

		initscr();
        WINDOW *editor = open_editor(argv[1]);

		int c;
		while (running) {
			content = read_input(editor, content, &fs, &x, &y);
			// display_content(editor, content, fs);
			// print_content(editor, fs);
		}

		endwin();
    }

    return 0;
}
