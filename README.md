# project-02

## Proposal
Ryan Poon, Pd 4

### Description
Terminal-based text editor that allows the user to create and modify files. The editor and file information can be interacted with through separate commands.

### Usage
After running the executable, the terminal will be cleared, for the user to begin typing. The name of the file to be edited will be passed as a command line argument. There will be a subwindow under the main editor where commands can be entered. "save" will write to the file, "quit" will close the program, "ls" will run ls, and "pwd" will run pwd. If a number is entered, the cursor will jump to that line number. CTRL-T to toggle between entering commands and the editor. Arrow keys will be used to move the cursor. The cursor's position will be displayed in the bottom right corner of the terminal, and line numbers will be at the left of the screen.

### Technical Design
- Allocating memory: used to store what the user types in
- Working with files:
    - reading from stdin
    - writing to a file when saving
    - reading from a file when a file is to be modified
- information about files: use file size to read file contents into editor, display information when custom "info" command is run
- processes: fork off separate processes to run commands
- sockets: time permitting, allow for multiple simultaneous editors

### Libraries
- ncurses

### Timeline
- 1/13 - Become familiar with ncurses
- 1/17 - Finish basic text editor
- 1/20 - Implement command window and custom commands
- 1/21 - Time permitting implement sockets and multiple users

### Data structures/algorithms
- allocated memory 

