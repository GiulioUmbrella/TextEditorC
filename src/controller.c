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

  switch (c) {
    case CTRL_KEY('q'):
      modifyScreen(SCR_CLEAN);
      modifyScreen(SCR_CURSOR_TOP);
      exit(0);
      break;
    }
  }

void editorDrawRows() {
  for (int y = 0; y < 10; y++)
  {
    writeToScreen("~\r\n");
  }
  for (int i = 0; i < 20; i++)
  {
    writeToScreen("_");
  }
}

void editorRefreshScreen() {
  modifyScreen(SCR_CLEAN);
  modifyScreen(SCR_CURSOR_TOP);

  editorDrawRows();

  modifyScreen(SCR_CURSOR_TOP);
}
void initEditor() {
  enableRawMode();
  getWindowSize();
  
}
