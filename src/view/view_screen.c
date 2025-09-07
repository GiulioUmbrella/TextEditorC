#include "view_screen.h"
#include "view_terminal.h"

#include <string.h>
#include <unistd.h>

void writeToScreen(char * str) {
  write(STDOUT_FILENO,str,strlen(str) );
}
 
int getSecreeRows(void){
    return getSettings()->rows;
}

int getScreenCols(void){
    return getSettings()->cols;
}

int getCursorX(void){
    return getSettings()->cx;
}

int getCursorY(void){
    return getSettings()->cy;
}


void updateWindowSize(void){
    getWindowSize();
}
void updateCursorPosition(void){
    getCursorPosition();
}

void screenClean(void){
    screenControl(SCR_CLEAN);
}

void MoveCursorTop(void){
    screenControl(SCR_CURSOR_TOP);
}

void setScreen(void){
    enableRawMode();
    getWindowSize();
}
