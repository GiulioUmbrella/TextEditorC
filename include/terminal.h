#pragma once

typedef enum {
  SCR_CLEAN,       // clean entire screen
  SCR_CURSOR_TOP,  // move cursor to (0,0)
  SCR_QUERY_CURSOR,
} ScreenOp;

void die(const char *s);
void disableRawMode(void);
void enableRawMode(void);
void screenControl(ScreenOp op);
void getWindowSize();
void writeToScreen(char * str);

int getSecreeRows();
int getScreenCols();
void getCursorPosition(char *);