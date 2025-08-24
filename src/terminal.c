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
    raw.c_lflag &= ~(ECHO | ICANON );

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}