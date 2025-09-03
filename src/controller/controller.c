#include "controller.h"
#include "view_screen.h"

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
      screenClean();
      MoveCursorTop();
      exit(0);
      break;
    }
  }

void editorDrawRows() {
  
  for (int y = 0; y < getSecreeRows() - 2; y++)
  {
    writeToScreen("~\r\n");
  }
  for (int i = 0; i < getScreenCols(); i++)
  {
    writeToScreen("_");
  }

  char buffer[100];
  sprintf(buffer, "Number of columns is %d, Number of rows %d cursor x %d cursor y %d",getScreenCols(), getSecreeRows(), getCursorX(), getCursorY() );
  writeToScreen(buffer);
    
}

void editorRefreshScreen() {
  updateWindowSize();
  updateCursorPosition();
  
  screenClean();
  MoveCursorTop();

  editorDrawRows();

  MoveCursorTop();
}

void initEditor() {
    setScreen();
  }
