# Typo

Ryan Poon, Pd 4

### Description
Terminal-based text editor that allows the user to create and modify files. The editor and file information can be interacted with through separate commands.

### Required Libraries
* ncurses
    * ```sudo apt-get install libncurses5-dev libncursesw5-dev```

### Instructions
Compile with ```make```
Run: ```./editor [filename]```
If the file exists, the editor will open with its contents. If it does not exist, it will be created after writing the changes (explained later). Arrow keys are used to navigate around the editor. To enter commands, hit the ESC key. This will move the cursor to the shell portion of the editor. Here, commands are run using fork and execvp, and arguments can be provided with a single space separating them. Only single commands are supported. To save the file, use the custom "write" command. Exit using ctrl-C. 

Running the command will move the cursor the the command output section of the editor. Here, the arrow keys can be used to navigate the output if it is too long for the screen. To go back into command-input mode, use backspace or delete. When in either the command input or the command output, hit ESC to return to the editor.

### Topics used
* Allocating memory
* Working with files
* Info about files
* Processes
* Unnamed pipes

### Planned additions
* allow for either line wrapping or horizontal scrolling
* syntax highlight
* multiple simultaneous users

### Bugs
* when command output is multiple lines, too many characters are written/read, resulting in random characters appearing at the end
