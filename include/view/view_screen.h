#pragma once


void writeToScreen(char * str);

int getSecreeRows();
int getScreenCols();
int getCursorX();
int getCursorY();

void updateWindowSize();
void updateCursorPosition();

void screenClean();
void MoveCursorTop();

void setScreen();