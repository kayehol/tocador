#include "miniaudio.h"
#include <libgen.h>
#include <ncurses.h>

void init_ncurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
}

int main() {
  ma_result result;
  ma_engine engine;
  ma_sound sound;
  char *path = "/home/kaye/Músicas/radar-punk/Crass - So What.mp3";
  char *filename = basename(path);

  init_ncurses();

  result = ma_engine_init(NULL, &engine);
  if (result != MA_SUCCESS) {
    return -1;
  }

  result = ma_sound_init_from_file(&engine, path, 0, NULL, NULL, &sound);
  if (result != MA_SUCCESS) {
    return -1;
  }

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
