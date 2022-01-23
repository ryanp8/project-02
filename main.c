#include "editor.h"
#include "console.h"

#define EDIT 0
#define CONSOLE 1

int main(int argc, char *argv[]) {

	int mode = EDIT;
    
    if (argc > 1) {

		off_t fs = 1; // start at 1 so there's trailing 0;
		off_t console_len = 1;

		char *content = calloc(fs, sizeof(char));
		off_t console_input_len = 1;		
		char *console_input = calloc(console_input_len, sizeof(char));
		char *console_content = calloc(console_len, sizeof(char));

		int x = 0;
		int y = 0;

		int console_x = 0;
		int console_y = 0;

		int editor_max_x;
		int editor_max_y;

		int console_max_x;
		int console_max_y;

		int term_x = 0;
		int term_y = 0;

		int editor_top_row = 0;
		int console_top_row = 0;

		initscr();
		noecho();
		cbreak();
		getmaxyx(stdscr, term_y, term_x);
        WINDOW *editor = open_editor(argv[1], &fs, content, (int) (term_y * 0.7));
		if (fs > 1) {
			content = calloc(fs, sizeof(char));
			int fd = open(argv[1], O_RDONLY);
			read(fd, content, fs);
			draw_text(editor, content, 0, 0, fs);
			draw_border(editor);
			draw_line_nums(editor, strcount(content, '\n') + 2, editor_top_row);
			wmove(editor, 0, WINDOW_X);
		}
		getmaxyx(editor, editor_max_y, editor_max_x);

		WINDOW *console = open_console(editor_max_y);
		getmaxyx(console, console_max_y, console_max_x);


		int c;
		while (1) {
			if (mode == EDIT) {
				c = read_input(editor, &content, &mode, &fs, &x, &y, &editor_top_row, editor_max_x, editor_max_y);
				if (c == 27) {
					mode = CONSOLE;
				}
				draw_border(editor);
				draw_line_nums(editor, strcount(content, '\n') + 2, editor_top_row);
				wmove(editor, y, x + WINDOW_X);
			}
			if (mode == CONSOLE) {
				c = read_input(console, &console_input, &mode, &console_input_len, &console_x, &console_y, &console_top_row, console_max_x, console_max_y);
				if (c == 27) {
					mode = EDIT;
					wclear(console);
				}
				if (c == '\n') {

					char *output;
					int shmd;
					shmd = shmget(KEY, OUTPUT_LEN, IPC_CREAT | 0640);
					output = shmat(shmd, 0, 0);

					char *tmp = calloc(console_input_len, sizeof(char));
					strcpy(tmp, console_input);
					tmp[console_input_len - 2] = 0;					
					run_command(tmp, output, content, argv[1], fs);

					
					console_input_len = 1;
					console_input = calloc(console_input_len, sizeof(char));
					console_x = 0;
					console_y = 0;

					char *tmp2 = output;

					// int i;
					// for (i = console_len + strlen(output); i >= 0; i--) {
					// 	if (tmp2[i] != 0) {
					// 		add_char(&console_content, tmp2[i], &console_len, console_x, console_top_row + console_y);
					// 		if (tmp[i] == '\n') {
					// 			console_x = 0;
					// 			if (console_y + 2 == console_max_y) { // max_y is the border line
					// 				console_top_row++;
					// 				display_content(console, console_content, char_instance(console_content, '\n', console_top_row) + 1, console_top_row, console_len);
					// 			}
					// 			else {
					// 				console_y++;
					// 			}
					// 		}
					// 		else {
					// 			console_x++;
					// 		}
					// 		wmove(console, console_y, console_x + WINDOW_X);
					// 	}
					// }

					shmdt(output);
					shmctl(shmd, IPC_RMID, 0);

				}

			}
		}

		endwin();	
		free(content);
    }

    return 0;
}
