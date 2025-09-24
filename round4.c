#include "common.h"    
#include "round4.h"

int kbhit_round4() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
}

int getch_nonblock() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    if (kbhit_round4()) {
        ch = getchar();
    } else {
        ch = -1;  // 입력 없을 때는 -1 리턴
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int getch()   // 한글자 입력을 바로 받을 수 있게 해주는 함수
{
    int c;
    struct termios oldattr, newattr;

    tcgetattr(STDIN_FILENO, &oldattr); // 현재 터미널 설정 읽음
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);        // CANONICAL과 ECHO 끔
    newattr.c_cc[VMIN] = 1;                     // 최소 입력 문자 수를 1로 설정
    newattr.c_cc[VTIME] = 0;                    // 최소 읽기 대기 시간을 0으로 설정
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr); // 터미널에 설정 입력
    c = getchar();                              // 키보드 입력 읽음
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr); // 원래의 설정으로 복구
    return c;
}

#define WIDTH 51
#define HEIGHT 25
#define LIGHT_RADIUS 1   // 1칸 반경 밝기 (3x3 범위)

char map1[HEIGHT][WIDTH] = {    // 징검다리 랜덤
    "11111111111111111111111111111111111111111111111111",
    "1################################################1",
    "1#####################070########################1",
    "1####################00000#######################1",
    "1###################5600065######################1",
    "1@@@@@@@@@@@@@@@@@@@5604065@@@@@@@@@@@@@@@@@@@@@@1",
    "1@@@@@@@@@@@@@@@@@@@5600065@@@@@@@@@@@@@@@@@@@@@@1",
    "1@@@@@@@@@@@@@@@@@@@5604065@@@@@@@@@@@@@@@@@@@@@@1",
    "1@@@@@@@@@@@@@@@@@@@5600065@@@@@@@@@@@@@@@@@@@@@@1",
    "1@@@@@@@@@@@@@@@@@@@5604065@@@@@@@@@@@@@@@@@@@@@@1",
    "1@@@@@@@@@@@@@@@@@@@5600065@@@@@@@@@@@@@@@@@@@@@@1",
    "1@@@@@@@@@@@@@@@@@@@5604065@@@@@@@@@@@@@@@@@@@@@@1",
    "1@@@@@@@@@@@@@@@@@@@5600065@@@@@@@@@@@@@@@@@@@@@@1",
    "1@@@@@@@@@@@@@@@@@@@5604065@@@@@@@@@@@@@@@@@@@@@@1",
    "1@@@@@@@@@@@@@@@@@@@5600065@@@@@@@@@@@@@@@@@@@@@@1",
    "1@@@@@@@@@@@@@@@@@@@5604065@@@@@@@@@@@@@@@@@@@@@@1",
    "1@@@@@@@@@@@@@@@@@@@5600065@@@@@@@@@@@@@@@@@@@@@@1",
    "1@@@@@@@@@@@@@@@@@@@5604065@@@@@@@@@@@@@@@@@@@@@@1",
    "1@@@@@@@@@@@@@@@@@@@5600065@@@@@@@@@@@@@@@@@@@@@@1",
    "1@@@@@@@@@@@@@@@@@@@5604065@@@@@@@@@@@@@@@@@@@@@@1",
    "1###################5600065######################1",
    "1###################0000000######################1",
    "1####################00000#######################1",
    "11111111111111111111111111111111111111111111111111"
};


int open_round4(void)
{
    system("clear");
    final();
    sleep(2);  // 2초대기

    int x = 22, y = 23;    // 플레이어 시작 위치
    char move = 0;
    char (*current_map)[WIDTH] = map1;

    srand(time(NULL)); // 시드 설정

    for (int i=4; i<=20; i++)          // 짝수 줄에'0' 홀수 줄에 '2','3' 중복없이 섞어서 넣기
    {
        for (int j=22; j<=24; j+=2)
        {
            if (i%2==0)
            {
                map1[i][22] = '0';
                map1[i][24] = '0';
            }
            else
            {
                if (rand() % 2 == 0)
                {
                    map1[i][22] = '2';
                    map1[i][24] = '3';
                }
                else
                {
                    map1[i][22] = '3';
                    map1[i][24] = '2';
                }
            }
        }
    }

    // 징검다리 정답 순차 출력 (아래 → 위)
    int reveal_height[HEIGHT] = {0};  // 각 줄에서 징검다리 표시 여부 (0:숨김, 1:표시)
    int delay = 200000;  // 0.2초 = 200,000마이크로초
    int steps = 25;  // HEIGHT 기준

    for (int step = 0; step < steps; step++) {
        printf("\x1b[H");
        system("clear");

        // 아래에서부터 step줄까지 '2' 공개
        for (int i = HEIGHT - 1; i >= HEIGHT - 1 - step; i--) {
            reveal_height[i] = 1;
        }

        // 맵 출력
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                char tile = current_map[i][j];

                if (i == x && j == y)
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
                else if (tile == '2' && reveal_height[i])
                    printf("🟫");  // 징검다리 표시
                else if (tile == '2' && !reveal_height[i])
                    printf("  ");  // 안 보이게 처리
                else if (tile == '@')
                    printf("🌊");
                else if (tile == '#')
                    printf("🌲");
                else if (tile == '1')
                    printf("⬛");
                else if (tile == '3')
                    printf("  ");
                else if (tile == '5')
                    printf("🡹");
                else if (tile == '6')
                    printf("   ");
                else if (tile == '7')
                    printf("🕌");
                else
                    printf("  ");
            }
            printf("\n");
        }

        printf("\n\n정답 경로(징검다리)를 아래에서 위로 표시 중...\n");
        usleep(delay);  // 0.2초 대기
    }
    system("clear");
    

//////////////////////////////정답 맵 출력 완료//////////////////////////////////
#define COLOR_RESET   "\033[0m"
#define COLOR_DIM     "\033[2m"     // 흐린 색상 (dim)
#define COLOR_BRIGHT  "\033[1m"     // 밝은 색상
#define COLOR_GREEN   "\033[32m"
#define COLOR_WHITE   "\033[37m"
    int timeLimit = 60;
    time_t startTime = time(NULL);

    for(;;)
    {
        system("clear");   //화면 클리어
        printf("\x1b[H"); // 화면 깜빡임 최소화

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int dx = abs(i - x);
            int dy = abs(j - y);
            int in_light = (dx <= LIGHT_RADIUS && dy <= LIGHT_RADIUS);

            char tile = current_map[i][j];

            // 빛이 닿는 곳은 밝게 출력, 아니면 흐리게
            if (i == x && j == y)
            {
                if (playerstate.emoji == 0)
                    printf(COLOR_BRIGHT"👦" COLOR_RESET);
                else if (playerstate.emoji == 1)
                    printf(COLOR_BRIGHT"🧔"COLOR_RESET);
                else if (playerstate.emoji == 2)
                    printf(COLOR_BRIGHT"👧"COLOR_RESET);
                else if (playerstate.emoji == 3)
                    printf(COLOR_BRIGHT"👵"COLOR_RESET);
            }
            else if (tile == '1')
                printf("%s⬛%s", in_light ? COLOR_BRIGHT : COLOR_DIM, COLOR_RESET);
            else if (tile == '2')
                printf("%s🟫%s", in_light ? COLOR_BRIGHT : COLOR_DIM, COLOR_RESET);
            else if (tile == '3')
                printf("%s🟫%s", in_light ? COLOR_BRIGHT : COLOR_DIM, COLOR_RESET);
            else if (tile == '4')
                printf("%s🔥%s", in_light ? COLOR_BRIGHT : COLOR_DIM, COLOR_RESET);
            else if (tile == '5')
                printf("%s🡹%s", in_light ? COLOR_BRIGHT : COLOR_DIM, COLOR_RESET);
            else if (tile == '6')
                printf("%s⬛ %s", in_light ? COLOR_BRIGHT : COLOR_DIM, COLOR_RESET);
            else if (tile == '7')
                printf("%s🕌%s", in_light ? COLOR_BRIGHT : COLOR_DIM, COLOR_RESET);
            else if (tile == '#')
                printf("%s🌲%s", in_light ? COLOR_BRIGHT : COLOR_DIM, COLOR_RESET);
            else if (tile == '@')
                printf("%s🌊%s", in_light ? COLOR_BRIGHT : COLOR_DIM, COLOR_RESET);
            else
                printf("  ");
        }
        printf("\n");
    }

        // 위치정보 출력
        printf("\n현재 위치: (%d, %d)\n", x,y);
        printf("이동 키 입력 (w/a/s/d/q/e, 종료는 p) : %c\n", move);

        // 시간 체크 및 종료 조건
        int remaining = timeLimit - (time(NULL) - startTime);

        if (remaining <= 0) {
            printf("\n⏰ 타임오버! 시간이 초과되었습니다.⏰\n\n");
            system("clear");
            gun44();
            sleep(3);
            system("clear");
            youDie();
            printf("\n\n             💥탈락입니다!💥\n");
            sleep(2);
            return 9;
        }

        // 화면 하단에 타이머 출력
        printf("⏰ 남은 시간: %d초 \n", remaining);

        usleep(300000);  // 잠깐 멈춰서 볼 수 있게 (0.3초)

        // 키 입력받기
        move = getch_nonblock();

        //이동처리
        if (move == -1) continue;   // 입력 없으면 다음 루프로 바로 넘어감
        if ((move == 'a' || move == 'A') && y > 0 && (current_map[x][y-1] == '0' ||current_map[x][y-1] == '2' || current_map[x][y-1] == '3'|| current_map[x][y-1] == '7'))
            y--;   //왼쪽으로 한칸이동
        else if ((move == 'd' || move == 'D') && y < WIDTH - 1 && (current_map[x][y + 1] == '0' ||current_map[x][y + 1] == '2' || current_map[x][y + 1] == '3'||current_map[x][y + 1] == '7'))
            y++;   //오른쪽으로 이동r
        else if ((move == 'w' || move == 'W') && x > 0 && (current_map[x - 1][y] == '0' || current_map[x - 1][y] == '2' || current_map[x - 1][y] == '3'||current_map[x - 1][y] == '7'))
            x--;   //위로 이동
        else if ((move == 's' || move == 'S') && x < HEIGHT - 1 && (current_map[x + 1][y] == '0' ||current_map[x + 1][y] == '2' || current_map[x + 1][y] == '3'||current_map[x + 1][y] == '7'))
            x++;   //아래로 이동
        // else if ((move == 'q' || move == 'Q') && x > 0 && y >0 && (current_map[x - 1][y - 1] == '0' ||current_map[x - 1][y - 1] == '2' || current_map[x - 1][y - 1] == '3'|| current_map[x - 1][y - 1] == '5'|| current_map[x - 1][y - 1] == '7')){
        //     x -=1;
        //     y -=1;  //대각선 왼쪽 위
        // }
        // else if ((move == 'e' || move == 'E') && x > 0 && y < WIDTH -1 && (current_map[x - 1][y + 1] == '0' ||current_map[x - 1][y + 1] == '2' || current_map[x - 1][y - 1] == '3'|| current_map[x - 1][y - 1] == '5'|| current_map[x - 1][y - 1] == '7')){
        //     x -=1;
        //     y +=1;  //대각선 오른쪽 위
        // }
        else if (move == 'p' || move == 'P') 
        {
            printf("게임을 종료합니다.\n\n");
            return 0;
        }
        else 
        {
            printf("\n이동할 수 없습니다. 아무 키나 누르세요...\n");
            usleep(1000000);  // 1초 대기
        }

        // 도착지에 도달하면 맵 전환
        if (current_map[x][y] == '7')
        {
            system("clear");
            pig2();
            printf("\n 🎉 축하합니다! 성에 도착했어요!! 🎉 \n");
            printf("💲💲 상금의 주인은 바로... 당신!! 💲💲 \n");
            sleep(3);
            system("clear");
            pride();
            sleep(2);
            system("clear");
            money();
            sleep(2);
            system("clear");
            sung();
            sleep(3);

            printf("계속하려면 아무 키나 누르세요...\n");
            getch();  // 사용자 입력 대기 - 메시지 확인용
            return 1;
        }
        else if (current_map[x][y] == '3')
        {
            system("clear");
            yunghee_2();
            usleep(300000);
            printf("\n          함정에 걸리셨군요...? You Die...☠️\n\n");
            sleep(3);
            system("clear");
            gun44();
            usleep(700000);
            system("clear");
            youDie();
            sleep(3);
            system("clear");


            return 9  ;
        }

        usleep(300000);

    }
    return 0;
}