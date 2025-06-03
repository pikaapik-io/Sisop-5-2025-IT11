#include "shell.h"
#include "kernel.h"

int main() {
  clearScreen();
  shell();
}

void printString(char *str)
{
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] == '\n') {
      // Move cursor to beginning of next line
      interrupt(0x10, 0x0E00 + '\r', 0, 0, 0); // Carriage return
      interrupt(0x10, 0x0E00 + '\n', 0, 0, 0); // Newline
    } else {
      interrupt(0x10, 0x0E00 + str[i], 0, 0, 0);
      // set warna
    }
    i++;
  }
}

void readString(char *buf)
{
  int i = 0;
  char c;
  do {
    c = interrupt(0x16, 0, 0, 0, 0);
    if (c == '\r') {
      break;
    } else if (c == '\b') {
      if (i > 0) {
        i--;
        printString("\b \b");
      }
    } else {
      buf[i++] = c;
      interrupt(0x10, 0x0E00 + c, 0, 0, 0);
    }
  } while (i < 127);

  buf[i] = '\0';
  printString("\n");
}

void clearScreen()
{
  int i, j;
  for (i = 0; i < 25; i++) {
    for (j = 0; j < 80; j++) {
      interrupt(0x10, 0x0E00 + ' ', 0, 0, 0);
    }
    interrupt(0x10, 0x0E00 + '\n', 0, 0, 0);
  }
  // move cursor to the top left corner
  interrupt(0x10, 0x0002, 0, 0, 0);
}

