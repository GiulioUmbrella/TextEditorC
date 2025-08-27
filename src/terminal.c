#include "terminal.h"

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

static struct termios origin_termios;

void disableRawMode(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &origin_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &origin_termios);
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

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}