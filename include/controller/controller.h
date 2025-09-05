#pragma once

void editorRefreshScreen();
void editorDrawRows();
void initEditor();

typedef struct {
  char *b;
  int len;
} appendBuffer;

#define ABUF_INIT {NULL, 0}
