#pragma once

void die(const char *s);
void disableRawMode(void);
void enableRawMode(void);
char editorReadKey();
void editorProcessKeypress();
void editorRefreshScreen();