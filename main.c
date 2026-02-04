#include "miniaudio.h"
#include <libgen.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void init_ncurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
}

int main(int argc, char *argv[]) {
  ma_result result;
  ma_engine engine;
  ma_sound sound;
  char *path = argv[1];
  char *filename = basename(path);

  if (argc == 1) {
    printf("Missing path argument\n");
    return -1;
  }

  int file_exists = access(path, F_OK);
  if (file_exists == -1) {
    printf("File does not exist on path: %s\n", path);
    return -1;
  }

  result = ma_engine_init(NULL, &engine);
  if (result != MA_SUCCESS) {
    perror("Error on engine init");
    exit(EXIT_FAILURE);
  }

  result = ma_sound_init_from_file(&engine, path, 0, NULL, NULL, &sound);
  if (result != MA_SUCCESS) {
    if (result == MA_INVALID_FILE) {
      fprintf(stderr, "%s", "Invalid file\n");
    } else {
      fprintf(stderr, "Error code [%d]: %s", result, "Error on sound init");
    }
    exit(result);
  }

  init_ncurses();

  ma_sound_start(&sound);
  printw("Playing %s\n", filename);
  printw("q - quit\n");
  printw("[space] - play/pause\n");

  int input;
  int paused = 0;
  while ((input = getch()) != 'q') {
    clear();
    if (input == 32) {
      if (paused) {
        printw("Playing %s\n", filename);
        ma_sound_start(&sound);
      } else {
        printw("Paused %s\n", filename);
        ma_sound_stop(&sound);
      }
      paused = !paused;
    }
    printw("q - quit\n");
    printw("[space] - play/pause\n");
    refresh();
  }
  endwin();
  ma_engine_uninit(&engine);

  return 0;
}
