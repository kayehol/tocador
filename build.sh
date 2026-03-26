gcc \
  -Wall -Wextra \
  -fexec-charset=UTF-8 \
  main.c miniaudio.c \
  -lpthread -lm -lncurses \
  -o tocador
