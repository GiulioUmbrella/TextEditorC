#pragma once

typedef enum {
  SCR_CLEAN,       // clean entire screen
  SCR_CURSOR_TOP,  // move cursor to (0,0)
} ScreenOp;

void die(const char *s);
void disableRawMode(void);
void enableRawMode(void);
void editorRefreshScreen();
void modifyScreen(ScreenOp op);

