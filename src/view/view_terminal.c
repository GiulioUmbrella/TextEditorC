#include "view_terminal.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>   // for TIOCGWINSZ, get windows size
#include <termios.h>     // for terminal managemente
#include <unistd.h>


static struct termios origin_termios;

static settings screenSetting;

const settings* getSettings() {
  return &screenSetting;
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



void getWindowSize() {
  struct winsize ws;

  if( ioctl(STDERR_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0 ) {
        die("windows size");
  } else {
    screenSetting.rows = ws.ws_row;
    screenSetting.cols = ws.ws_col;    
  
  }
}
  
int getCursorPosition() {
  char buf[32];
  unsigned int i = 0;
  
  screenControl(SCR_QUERY_CURSOR);

  while (i < 32) {
    if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
    if (buf[i] == 'R') break;
    i++;
  }
  buf[i] = '\0'; 
  
  if(buf[0] != '\x1b' || buf[1] != '[' ) return -1;
  if(sscanf(&buf[2],"%d,%d",&screenSetting.cx,&screenSetting.cy) != 2 ) return -1;

  return 0;
}

