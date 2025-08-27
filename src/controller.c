#include "controller.h"
#include "terminal.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CTRL_KEY(k) ((k) & 0x1f)

char editorReadKey() {
  int nread;
  char c = '\0';
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    // if (nread == -1 && errno != EAGAIN) die("read");
  }
  return c;
}

void editorProcessKeypress(char c) {

    if (iscntrl(c)) {
        printf("%d\r\n", c);
    } else {
        printf("%d ('%c')\r\n", c, c);
    }
  
  
  switch (c) {
    case CTRL_KEY('q'):
      modifyScreen(SCR_CLEAN);
      modifyScreen(SCR_CURSOR_TOP);
      exit(0);
      break;
    }
  }

void editorRefreshScreen() {
  modifyScreen(SCR_CLEAN);
  modifyScreen(SCR_CURSOR_TOP);
}