#include "common.h"    
#include "round3.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 24
#define MAX_TARGETS 5
#define GAME_DURATION 60

#define MAX_GAUGE 100
#define GAUGE_THRESHOLD 90
#define GAUGE_MID 60

#define WEATHER_NONE 0
#define WEATHER_RAIN 1
#define WEATHER_FOG 2

typedef enum {
    NORMAL,
    HIT1,
    HIT2,
    HIT3,
    DEAD
} HitState;

typedef struct {
    int x, y;
    int direction;
    HitState state;
    int hit_timer;
} Target;

typedef struct {
    int x, y;
} Position;

int start_time = 0;
int gauge = 0;
bool gauge_up = true;
int weather = WEATHER_NONE;

int get_time_seconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (int)tv.tv_sec;
}

void clear_screen() {
    printf("\033[2J");
}

void move_cursor(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void disable_buffering() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void enable_buffering() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void draw_player(Position p) {
    move_cursor(p.x, p.y);
    printf("🧍");
    move_cursor(p.x + 2, p.y);
    printf("🪨");
}

void draw_targets(Target targets[]) {
    for (int i = 0; i < MAX_TARGETS; ++i) {
        if (targets[i].state == DEAD) continue;
        move_cursor(targets[i].x, targets[i].y);
        switch (targets[i].state) {
            case NORMAL: printf("🟥"); break;
            case HIT1:   printf("💥"); break;
            case HIT2:   printf("🔥"); break;
            case HIT3:   printf("X "); break;
            default: break;
        }
    }
}

void update_targets(Target targets[]) {
    for (int i = 0; i < MAX_TARGETS; ++i) {
        if (targets[i].state == NORMAL) {
            targets[i].x += targets[i].direction;
            if (targets[i].x <= 10 || targets[i].x >= SCREEN_WIDTH - 5)
                targets[i].direction *= -1;
        } else if (targets[i].state != DEAD) {
            if (targets[i].hit_timer > 0)
                targets[i].hit_timer--;
            else {
                if (targets[i].state == HIT1) {
                    targets[i].state = HIT2;
                    targets[i].hit_timer = 2;
                } else if (targets[i].state == HIT2) {
                    targets[i].state = HIT3;
                    targets[i].hit_timer = 2;
                } else if (targets[i].state == HIT3) {
                    targets[i].state = DEAD;
                }
            }
        }
    }
}

void update_gauge() {
    if (gauge_up) gauge += 5;
    else gauge -= 5;

    if (gauge >= MAX_GAUGE) gauge_up = false;
    else if (gauge <= 0) gauge_up = true;
}

void draw_gauge() {
    move_cursor(1, SCREEN_HEIGHT);
    printf("🎯 Gauge (high accuracy: 90-100): [");
    int bar = gauge / 5;
    for (int i = 0; i < 20; ++i) {
        if (i < bar) printf("█");
        else printf(" ");
    }
    printf("] %3d", gauge);
}

void draw_hud(int score, int time_left) {
    move_cursor(1, 1);
    printf("🏹 Score: %d | ⏱ Time left: %d sec", score, time_left);
    if (weather == WEATHER_RAIN) {
        printf(" | 🌧 Rain");
    } else if (weather == WEATHER_FOG) {
        printf(" | 🌫 Fog");
    }
}

void shoot(Position player, Target targets[], int *score) {
    int bx = player.x + 4;
    int by = player.y;

    if (gauge < GAUGE_THRESHOLD) {
        by += (rand() % 3) - 1;
        if (gauge < GAUGE_MID) {
            bx += (rand() % 3);
        }
    }

    if (weather != WEATHER_NONE) {
        by += (rand() % 3) - 1;
    }

    while (bx < SCREEN_WIDTH - 1) {
        clear_screen();
        draw_hud(*score, GAME_DURATION - (get_time_seconds() - start_time));
        draw_player(player);
        draw_targets(targets);
        draw_gauge();

        move_cursor(bx, by);
        printf("🪨");

        fflush(stdout);
        usleep(30000);

        for (int i = 0; i < MAX_TARGETS; ++i) {
            if (targets[i].state == NORMAL &&
                by == targets[i].y &&
                bx >= targets[i].x && bx <= targets[i].x + 2) {

                targets[i].state = HIT1;
                targets[i].hit_timer = 2;
                (*score)++;
                return;
            }
        }

        bx++;
    }
}

int open_round3() {
    system("clear");  
    stone();
    sleep(3);


    setlocale(LC_ALL, "");
    disable_buffering();
    clear_screen();

    Position player = {5, SCREEN_HEIGHT / 2};
    Target targets[MAX_TARGETS];
    int score = 0;
    start_time = get_time_seconds();

    for (int i = 0; i < MAX_TARGETS; ++i) {
        targets[i].x = SCREEN_WIDTH - 10;
        targets[i].y = 3 + i * 4;
        targets[i].direction = (i % 2 == 0) ? -1 : 1;
        targets[i].state = NORMAL;
        targets[i].hit_timer = 0;
    }

    while (1) {
        int now = get_time_seconds();
        int elapsed = now - start_time;
        int time_left = GAME_DURATION - elapsed;
        if (time_left <= 0) break;

        int alive = 0;
        for (int i = 0; i < MAX_TARGETS; ++i) {
            if (targets[i].state != DEAD) alive++;
        }
        if (alive <= 2 && weather == WEATHER_NONE) {
            weather = (rand() % 2) ? WEATHER_RAIN : WEATHER_FOG;
        }
        if (alive == 0) {
            clear_screen();
            // move_cursor(10, 10);
            system("clear");
            maskMan();  
            printf("\n                 💰 생존! 다음 게임으로 넘어갑니다.💰\n");
            printf("                        >>> Final Score: %d\n", score);
            sleep(2);
            enable_buffering();
            return 1;
        }

        clear_screen();

        fd_set set;
        struct timeval timeout = {0, 0};
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        char ch = 0;
        if (select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout) > 0) {
            read(STDIN_FILENO, &ch, 1);
        }

        if (ch == 27) break;
        if (ch == 'w' && player.y > 2) player.y--;
        else if (ch == 's' && player.y < SCREEN_HEIGHT - 2) player.y++;
        else if (ch == 'a' && player.x > 1) player.x--;
        else if (ch == 'd' && player.x < SCREEN_WIDTH - 10) player.x++;
        else if (ch == ' ') shoot(player, targets, &score);

        update_targets(targets);
        update_gauge();
        draw_hud(score, time_left);
        draw_player(player);
        draw_targets(targets);
        draw_gauge();

        move_cursor(1, SCREEN_HEIGHT);
        fflush(stdout);
        usleep(50000);
    }

    clear_screen();
    move_cursor(10, 10);
    gun44();
    sleep(3);
    system("clear");
    youDie();
    printf("\n\n                💥탈락입니다!💥\n");
    sleep(2);
    enable_buffering();
    
    
    return 9;
}
