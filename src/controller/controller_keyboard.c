#include "controller_keyboard.h"
#include "view_screen.h"

#include <stdlib.h>
#include <unistd.h>

#define CTRL_KEY(k) ((k) & 0x1f)

char editorReadKey() {
  int nread;
  char c = '\0';
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    // if (nread == -1 && errno != EAGAIN) die("read");
  }
  return c;
}

void editorProcessKeypress(char c) {

  switch (c) {
    case CTRL_KEY('q'):
      screenClean();
      MoveCursorTop();
      exit(0);
      break;
    }
  }
