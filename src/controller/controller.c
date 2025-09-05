#include "controller.h"
#include "controller_keyboard.h"
#include "view_screen.h"

#include <stdio.h>







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

  char c = editorReadKey();
  editorProcessKeypress(c);
}

void initEditor() {
    setScreen();
  }
