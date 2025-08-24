#include "terminal.h"

#include <ctype.h>
#include <stdio.h>
#include <unistd.h>



#ifdef EDITOR_DEMO
int main() {
  enableRawMode();
  
  char c;
  while (read(STDIN_FILENO, &c,1) == 1 && c != 'q' ) {
    if (iscntrl(c)) {
      printf("%d\n", c);
    } else {
      printf("%d ('%c')\n", c,c);
    }
  }

  return 0;
}

#else
int main() {
  return 42;
}

#endif