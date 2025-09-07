#pragma once

void editorRefreshScreen(void);
void editorDrawRows(void);
void initEditor(void);

typedef struct {
  char *b;
  int len;
} appendBuffer;

#define ABUF_INIT {NULL, 0}
