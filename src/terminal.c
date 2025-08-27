#include "terminal.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>


static struct termios origin_termios;

void die(const char *s) {
  perror(s);
  exit(1);
}

void disableRawMode(void) {
    if( tcsetattr(STDIN_FILENO, TCSAFLUSH, &origin_termios) == -1)
        die("tcsetattr");
}

void enableRawMode() {
    if(tcgetattr(STDIN_FILENO, &origin_termios) == -1)
        die("tcgetattr");

    atexit(disableRawMode);

    struct termios raw = origin_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    #ifndef EDITOR_DEMO
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    #endif

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw))
        die("tcsetattr");
    
}
  
void editorRefreshScreen() {
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);

}