#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

void shell(){
  char buf[128];
  char cmd[64];
  char arg[2][64];
  char user[80];
  char companynyaweh[64];

  printString("     *############:      _ _ _     _                   \n");
  printString("    ##:*#:    ## +#:    | | | |___| |___ ___ _____ ___ \n");
  printString("  .##.*#.      ##.=#=   | | | | -_| |  _| . |     | -_|\n");
  printString(" :##.##. -+++++*##*##+  | | | | -_| |  _| . |     | -_|\n");
  printString("  ##-=#=  ...........   |_____|___|_|___|___|_|_|_|___|\n");
  printString("   -#+:##               Running EorzeOS shell v0.1 BETA\n");
  printString("    :############+      Copyright (C) 2025 EorzeOS Team\n");
  printString("         using 'help' to see available commands        \n\n");
  strcpy(user, "user");
  strcpy(companynyaweh, "@eorzeos~");
  while (true) {
    printString(user);
    printString(companynyaweh);
    printString("> ");
    readString(buf);

    parseCommand(buf, cmd, arg);

    if (strcmp(cmd, "clear")) {
      clearScreen();
    } else if (strcmp(cmd, "exit")) {
      printString("Bye!\n");
      break;
    } else if (strcmp(cmd, "yo")){
      printString("gurt\n");
    } else if (strcmp(cmd, "gurt")){
      printString("yo\n");
    } else if (strcmp(cmd, "ping")) {
      printString("pong\n");
    } else if (strcmp(cmd, "pong")) {
      printString("ping\n");
    } else if (strcmp(cmd, "shutdown")) {
      printString("Shutting down...\n");
      interrupt(0x10, 0x0001, 0, 0, 0); // Shutdown command
      break;
    } else if (strcmp(cmd, "reboot")) {
      int i, j, k;
      clearScreen();
      for (i = 0; i < 3; i++) {
        printString("Rebooting");
        for (j = 0; j < 3; j++) {
          printString(".");
          sleep(10); // Sleep for 1 second
        }
        clearScreen();
      }
      interrupt(0x10, 0x0002, 0, 0, 0); // Reboot command
      break;
    } else if (strcmp(cmd, "user")){
      if (arg[0][0] != '\0') {
        // set user to arg[0] + @eorzeos~
        strcpy(user, arg[0]);
        printString("User set to: ");
        printString(user);
        printString("\n");
      } else {
        // kita kembalikan ke user default
        strcpy(user, "user");
        printString("User reset to default: ");
        printString(user);
        printString("\n");
      }
    } else if (strcmp(cmd, "grandcompany")) {
      if (strcmp(arg[0], "maelstrom") == 1) {
        strcpy(companynyaweh, "@Storm~");
        // set warna text jadi merah
        clearScreen();
        interrupt(0x10, 0x0003, 0, 0, 0);
      } else if (strcmp(arg[0], "twinadder") == 1) {
        strcpy(companynyaweh, "@Serpent~");
        // set warna text jadi kuning
        clearScreen();
        interrupt(0x10, 0x0004, 0, 0, 0);
      } else if (strcmp(arg[0], "immortalflames") == 1) {
        strcpy(companynyaweh, "@Flame~");
        // set warna text jadi biru
        clearScreen();
        interrupt(0x10, 0x0005, 0, 0, 0);
      } else if (strcmp(arg[0], "clear") == 1) {
        strcpy(companynyaweh, "@eorzeos~");
        // set warna text jadi default
        clearScreen();
        interrupt(0x10, 0x0002, 0, 0, 0);
      } else {
        printString("Error: No Grand Company specified\n");
      }
    } else if (strcmp(cmd, "add")){
      int x, y, result;
      if (arg[0][0] != '\0' && arg[1][0] != '\0') {
          x = arg[0][0];
          y = arg[1][0];
          printString(x + y);
      } else {
          printString("Error: Invalid arguments\n");
          printString("Usage: add <num1> <num2>\n");
      }
    } else if (strcmp(cmd, "sub")) {
      int x, y, result;
      if (arg[0][0] != '\0' && arg[1][0] != '\0') {
          x = arg[0][0];
          y = arg[1][0];
          printString(x - y);
      } else {
          printString("Error: Invalid arguments\n");
          printString("Usage: sub <num1> <num2>\n");
      }
    } else if (strcmp(cmd, "mul")) {
      int x, y;
      if (arg[0][0] != '\0' && arg[1][0] != '\0') {
          x = arg[0][0];
          y = arg[1][0];
          printString(x * y);
      } else {
          printString("Error: Invalid arguments\n");
          printString("Usage: mul <num1> <num2>\n");
      }
    } else if (strcmp(cmd, "div")) {
      int x, y;
      if (arg[0][0] != '\0' && arg[1][0] != '\0') {
          x = arg[0][0];
          y = arg[1][0];
          if (y != 0) {
              printString(div(x, y));
          } else {
              printString("Error: Division by zero\n");
          }
      } else {
          printString("Error: Invalid arguments\n");
          printString("Usage: div <num1> <num2>\n");
      }
    } else if (strcmp(cmd, "yogurt")){
        int incrementcoi = 1;
        int random = mod(getBiosTick(), incrementcoi+incrementcoi*2); 
        if (random == 0) {
            printString("gurt> yo\n");
            incrementcoi++;
        } else if (random == 1) {
            printString("gurt> ts unami gng </3\n");
            incrementcoi++;
        } else {
            printString("gurt> sygau\n");
            incrementcoi++;
        }
    } else if (strcmp(cmd, "help")) {
      printString("Available commands:\n");
      printString("  clear - Clear the screen\n");
      printString("  exit - Exit the shell\n");
      printString("  help - Show this help message\n");
      printString("  <message> - Print the message to the screen\n");
      printString("  yo - Respond with 'gurt'\n");
      printString("  gurt - Respond with 'yo'\n");
      printString("  ping - Respond with 'pong'\n");
      printString("  pong - Respond with 'ping'\n");
      printString("  shutdown - Shutdown the system\n");
      printString("  reboot - Reboot the system\n");
      printString("  user <username> - Set the username (default: user@eorzeos~)\n");
      printString("  grandcompany <company> - Set the Grand Company (maelstrom, twinadder, immortalflames, clear)\n");
      printString("  add <num1> <num2> - Add two numbers\n");
      printString("  sub <num1> <num2> - Subtract two numbers\n");
      printString("  mul <num1> <num2> - Multiply two numbers\n");
      printString("  div <num1> <num2> - Divide two numbers\n");
      printString("  yogurt - Random response from gurt\n");

    } else {
      printString(buf);
      printString("\n");
    }
  }
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  int i = 0, j = 0;
  int argIndex = 0;

  for(i=0; i<64; i++) cmd[i] = 0;
  for(i=0; i<2; i++)
    for(j=0; j<64; j++)
      arg[i][j] = 0;

  i = 0;
  while (buf[i] != ' ' && buf[i] != '\0' && buf[i] != '\n') {
    cmd[i] = buf[i];
    i++;
  }
  cmd[i] = '\0';

  while (buf[i] != '\0' && buf[i] != '\n' && argIndex < 2) {
    while (buf[i] == ' ') i++;
    if (buf[i] == '\0' || buf[i] == '\n') break;

    j = 0;
    while (buf[i] != ' ' && buf[i] != '\0' && buf[i] != '\n') {
      arg[argIndex][j] = buf[i];
      i++; j++;
      if (j >= 63) break;
    }
    arg[argIndex][j] = '\0';
    argIndex++;
  }
}
