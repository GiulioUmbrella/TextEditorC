#pragma once


void writeToScreen(char * str);

int getSecreeRows(void);
int getScreenCols(void);
int getCursorX(void);
int getCursorY(void);

void updateWindowSize(void);
void updateCursorPosition(void);

void screenClean(void);
void MoveCursorTop(void);

void setScreen(void);