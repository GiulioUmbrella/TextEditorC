#include "terminal.h"

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>


#define CTRL_KEY(k) ((k) & 0x1f)

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
char editorReadKey() {
  int nread;
  char c = '\0';
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN) die("read");
  }
  return c;
}

void editorProcessKeypress() {
  char c = editorReadKey();
  
    if (iscntrl(c)) {
        printf("%d\r\n", c);
    } else {
        printf("%d ('%c')\r\n", c, c);
    }
  
  
  switch (c) {
    case CTRL_KEY('q'):
      write(STDOUT_FILENO, "\x1b[2J", 4);
      write(STDOUT_FILENO, "\x1b[H", 3);
      exit(0);
      break;
    }
  }
  
void editorRefreshScreen() {
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);

}