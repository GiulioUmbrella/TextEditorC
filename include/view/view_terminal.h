#pragma once

void die(const char *s);

void disableRawMode(void);
void enableRawMode(void);

void getWindowSize();
int getCursorPosition();

typedef enum {
  SCR_CLEAN,       // clean entire screen
  SCR_CURSOR_TOP,  // move cursor to (0,0)
  SCR_QUERY_CURSOR,
} ScreenOp;

void screenControl(ScreenOp op);

typedef struct 
{
  int rows;
  int cols;
  int cx;
  int cy;

} settings;

const settings* getSettings();


