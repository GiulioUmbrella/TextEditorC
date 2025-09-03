#include "view_screen.h"
#include "view_terminal.h"

#include <string.h>
#include <unistd.h>

void writeToScreen(char * str) {
  write(STDOUT_FILENO,str,strlen(str) );
}
 
int getSecreeRows(){
    return getSettings()->rows;
}

int getScreenCols(){
    return getSettings()->cols;
}

int getCursorX(){
    return getSettings()->cx;
}

int getCursorY(){
    return getSettings()->cy;
}


void updateWindowSize(){
    getWindowSize();
}
void updateCursorPosition(){
    getCursorPosition();
}

void screenClean(){
    screenControl(SCR_CLEAN);
}

void MoveCursorTop(){
    screenControl(SCR_CURSOR_TOP);
}

void setScreen(){
    enableRawMode();
    getWindowSize();
}