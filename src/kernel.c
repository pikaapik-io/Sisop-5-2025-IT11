#include "shell.h"
#include "kernel.h"

int main() {
  clearScreen();
  shell();
  haloin();

}

void haloin() {
  char* str = "Halo";
  int i = 0;

  for (i = 0; i < 4; i++) {
    char warna = 0x5;
    putInMemory(0xB000, 0x8000 + i * 2, str[i]);
    putInMemory(0xB000, 0x8001 + i * 2, warna);
  }

  while (1);
}


void printString(char *str)
{
  //TODO: Implementasi fungsi untuk mencetak string
}

void readString(char *buf)
{
  //TODO: Implementasi fungsi untuk membaca string
}

void clearScreen()
{
  int i;
  for (i = 0; i < 80 * 25; i++) {
    putInMemory(0xB000, i * 2, ' ');
    putInMemory(0xB000, i * 2 + 1, 0x0); // Warna hitam
  }
}