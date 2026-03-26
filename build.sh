gcc \
  -Wall -Wextra \
  -fexec-charset=UTF-8 \
  main.c miniaudio.o \
  -lpthread -lm -lncurses \
  -o tocador
