#include "common.h"    
#include "round2.h"
#define WIDTH 50
#define HEIGHT 25

char map_round2[HEIGHT][WIDTH+1] = {
"16716716716716716716716716716716716716716716716167",
"10000000000000000000000000000000000000000000000001",
"60000000000000000000000000000000000000000000000006",
"70000000000000000000000000000000000000000000000007",
"10000000000000000003333333333333000000000000000001",
"60000000000000000003333333333333000000000000000006",
"70000000000000000003333333333333000000000000000007",
"10000000000000000003333333333333000000000000000001",
"60000000000000000003333333333333000000000000000006",
"70000000000000000003333333333333000000000000000007",
"10000000000000000003333333333333000000000000000001",
"60000000000000000003333333333333000000000000000006",
"70000000000000000003333333333333000000000000000007",
"10000000000000000003333333333333000000000000000001",
"60000000000000000003333333333333000000000000000006",
"70000000000000000000000000000000000000000000000007",
"10000000000000000000000000000000000000000000000001",
"60000000000000000000000000000000000000000000000006",
"70000000000000000000000000000000000000000000000007",
"10000000000000000000000000000000000000000000000001",
"60000000000000000000000000000000000000000000000006",
"70000000000000000000000000000000000000000000000007",
"10000000000000000000000000000000000000000000000001",
"60000000000000000000000000000000000000000000000006",
"16716716716716716716716716716716716716716716716167"
};

char correct_shape[HEIGHT][WIDTH+1];

#define SHAPE_START_Y 5
#define SHAPE_START_X 15

int star_shape[11][21] = {
{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

int triangle_shape[11][21] = {
{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0}
};

int umbrella_shape[11][21] = {
{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

int zero_positions_x[1000];
int zero_positions_y[1000];
int zero_count = 0;

struct termios orig_termios;

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int kbhit_with_timeout(int timeout_sec) {
    struct timeval tv;
    fd_set readfds;

    tv.tv_sec = timeout_sec;
    tv.tv_usec = 0;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    return select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
}

void find_zero_positions() {
    zero_count = 0;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (map_round2[y][x] == '0') {
                zero_positions_x[zero_count] = x;
                zero_positions_y[zero_count] = y;
                zero_count++;
            }
        }
    }
}

void place_random_4_and_5() {
    int count_4 = rand() % 5 + 1;
    int count_5 = rand() % 5 + 1;

    for (int i = 0; i < count_4 && zero_count > 0; i++) {
        int idx = rand() % zero_count;
        int x = zero_positions_x[idx];
        int y = zero_positions_y[idx];
        map_round2[y][x] = '4';

        zero_positions_x[idx] = zero_positions_x[zero_count - 1];
        zero_positions_y[idx] = zero_positions_y[zero_count - 1];
        zero_count--;
    }
    for (int i = 0; i < count_5 && zero_count > 0; i++) {
        int idx = rand() % zero_count;
        int x = zero_positions_x[idx];
        int y = zero_positions_y[idx];
        map_round2[y][x] = '5';

        zero_positions_x[idx] = zero_positions_x[zero_count - 1];
        zero_positions_y[idx] = zero_positions_y[zero_count - 1];
        zero_count--;
    }
}

void draw_map(int px, int py) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == px && y == py)
            {
                if (playerstate.emoji == 0)
                    printf("👦");
                else if (playerstate.emoji == 1)
                    printf("🧔");
                else if (playerstate.emoji == 2)
                    printf("👧");
                else if (playerstate.emoji == 3)
                    printf("👵");
            }
            else if (map_round2[y][x] == '1')
                printf("🟦");
            else if (map_round2[y][x] == '6')
                printf("🟨");
            else if (map_round2[y][x] == '7')
                printf("🟩");
            else if (map_round2[y][x] == '3')
                printf("🔲");
            else if (map_round2[y][x] == '2')
                printf("🟥");
            else if (map_round2[y][x] == '4')
                printf("👾");
            else if (map_round2[y][x] == '5')
                printf("🧛");
            else
                printf("🟫");
        }
        printf("\n");
    }
}

void reset_correct_shape() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            correct_shape[y][x] = map_round2[y][x];
        }
        correct_shape[y][WIDTH] = '\0';
    }
}

void copy_shape(int shape[11][21]) {
    for (int y = 0; y < 11; y++) {
        for (int x = 0; x < 21; x++) {
            int map_y = SHAPE_START_Y + y;
            int map_x = SHAPE_START_X + x;

            if (map_y < HEIGHT && map_x < WIDTH && map_round2[map_y][map_x] == '3') {
                if (shape[y][x] == 1)
                    correct_shape[map_y][map_x] = '2';
                else
                    correct_shape[map_y][map_x] = '3';
            } else {
                if (map_y < HEIGHT && map_x < WIDTH)
                    correct_shape[map_y][map_x] = map_round2[map_y][map_x];
            }
        }
    }
}

void generate_shape() {
    int shape_type = rand() % 10;

    if (shape_type == 0 || shape_type == 1 || shape_type == 2) {
        printf("출제 도형: ⭐ 별\n");
        copy_shape(star_shape);
    } else if (shape_type == 3 || shape_type == 4 || shape_type == 5) {
        printf("출제 도형: 🔺 삼각형\n");
        copy_shape(triangle_shape);
    } else {
        printf("출제 도형: ☂️ 우산\n");
        copy_shape(umbrella_shape);
    }
}

void show_shape_preview() {
    system("clear");
    printf("🐙 도형을 외워주세요! (5초)\n\n");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (correct_shape[y][x] == '2') printf("🟥");
            else if (map_round2[y][x] == '1') printf("🟦");
            else if (map_round2[y][x] == '6') printf("🟨");
            else if (map_round2[y][x] == '7') printf("🟩");
            else if (map_round2[y][x] == '3') printf("🔲");
            else printf("🟫");
        }
        printf("\n");
    }
    sleep(5);
    system("clear");
}

int check_answer() {
    int correct = 0, total = 0;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (correct_shape[y][x] == '2') {
                total++;
                if (map_round2[y][x] == '2') correct++;
            }
        }
    }

    double accuracy = (double)correct / total * 100.0;
    printf("정확도: %.2f%%\n", accuracy);

    if (accuracy >= 90.0) return 1;
    else return 0;
}

int run_game() {
    int px = 1, py = 1;

    // printf("게임 설명: 랜덤 도형을 기억해서 바닥 색을 맞추세요!\n");
    // printf("준비가 되면 'y'를 누르세요.\n");

    // while (1) {
    //     int ch = getchar();
    //     if (ch == 'y' || ch == 'Y') break;
    // }

    find_zero_positions();
    place_random_4_and_5();

    reset_correct_shape(); // 이전 도형 흔적 없애기 위해 초기화

    generate_shape();

    show_shape_preview();

    time_t start_time = time(NULL);
    double limited_time = 60.0;

    while (1) {
        time_t current_time = time(NULL);
        double elapsed_time = difftime(current_time, start_time);

        if (elapsed_time >= limited_time) {
            printf("⏰ 타임오버! 시간이 초과되었습니다.⏰!\n");
            return 0;
        }

        system("clear");
        draw_map(px, py);

        printf("이동: w a s d | 스페이스: 색 바꾸기 | 엔터: 완료 | q: 종료\n");
        printf("🕰️ 남은 시간: %.0f초\n", limited_time - elapsed_time);

        int ret = kbhit_with_timeout(5);

        if (ret == 0) {
            printf("입력 시간 초과!💣\n");
            sleep(1);
            continue;
        } else if (ret == -1) {
            perror("select error");
            return 0;
        }

        int ch = getchar();
        int nx = px, ny = py;

        if (ch == 'w' || ch == 'W') ny--;
        else if (ch == 's' || ch == 'S') ny++;
        else if (ch == 'd' || ch == 'D') nx++;
        else if (ch == 'a' || ch == 'A') nx--;
        else if (ch == 'q' || ch == 'Q') return 0;
        else if (ch == ' ') {
            if (map_round2[py][px] == '3') map_round2[py][px] = '2';
            else if (map_round2[py][px] == '2') map_round2[py][px] = '3';
        }
        else if (ch == '\n' || ch == '\r') {
            if (check_answer()) {
                system("clear");
                maskMan();  
                printf("\n\n               💰 생존! 다음 게임으로 넘어갑니다.💰\n");
                sleep(3);
                return 1;
            } else {
                gun44();
                sleep(3);
                system("clear");
                youDie();
                printf("\n\n               💥 탈락입니다! 💥\n");
                sleep(2);
                return 0;
            }
        }

        if (map_round2[ny][nx] != '1' && map_round2[ny][nx] != '6' && map_round2[ny][nx] != '7') {
            px = nx;
            py = ny;
        }
    }

    return 0;
}


int open_round2() {
    system("clear");
    dalgona();
    sleep(3);


    setlocale(LC_ALL, "");

    srand(time(NULL));
    enable_raw_mode();

    int result = run_game();  // run_game()이 1이면 성공, 아니면 실패

    disable_raw_mode();
    // printf("게임을 종료합니다.\n");

    if (result == 1)
        return 1;   // 성공
    else
        return 9;   // 실패
}