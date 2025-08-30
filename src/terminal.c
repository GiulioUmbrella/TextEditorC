#include "terminal.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>   // for TIOCGWINSZ, get windows size
#include <termios.h>     // for terminal managemente
#include <unistd.h>


static struct termios origin_termios;

int rows;
int cols;

int getSecreeRows() {
  return rows;
}

int getScreenCols() {
  return cols;
}


void die(const char *s) {
  perror(s);
  exit(1);
}

void disableRawMode(void) {
    if( tcsetattr(STDIN_FILENO, TCSAFLUSH, &origin_termios) == -1)
        die("tcsetattr");
}

void enableRawMode() {
    if(tcgetattr(STDIN_FILENO, &origin_termios) == -1)
        die("tcgetattr");

    atexit(disableRawMode);

    struct termios raw = origin_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    #ifndef EDITOR_DEMO
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    #endif

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw))
        die("tcsetattr");
    
}

void getWindowSize() {
  struct winsize ws;

  if( ioctl(STDERR_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0 ) {
        die("windows size");
  } else {
    rows = ws.ws_row;
    cols = ws.ws_col;    
  
  }
}
void getCursorPosition(char *buf) {
  
  unsigned int i = 0;
  
  screenControl(SCR_QUERY_CURSOR);

  while (i < 32) {
    if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
    if (buf[i] == 'R') break;
    i++;
  }
  buf[i] = '\0'; 

}

void writeToScreen(char * str) {
  write(STDOUT_FILENO,str,strlen(str) );
}

void screenControl(ScreenOp op) {
  switch (op)
  {
  case SCR_CLEAN:
    write(STDOUT_FILENO, "\x1b[2J", 4);
    break;
    
  case SCR_CURSOR_TOP:
    write(STDOUT_FILENO, "\x1b[H", 3);
    break;  
  
  case SCR_QUERY_CURSOR:
    write(STDOUT_FILENO, "\x1b[6n", 4);
    break;

  default:
    break;
  }
}

  