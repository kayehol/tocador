gcc \
  -Wall -Wextra \
  main.c miniaudio.c \
  -lpthread -lm -lncurses \
  -o tocador
