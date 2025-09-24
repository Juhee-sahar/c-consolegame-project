#ifndef COMMON_H
#define COMMON_H

// 표준 라이브러리 헤더
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>        
#include <unistd.h>
#include <termios.h>         
#include <fcntl.h>
#include <stdio_ext.h>
#include <locale.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdbool.h>

// 창작 라이브러리 헤더
#include "player_state.h"
#include "console_art.h"

extern GameState playerstate;

#endif // COMMON_H