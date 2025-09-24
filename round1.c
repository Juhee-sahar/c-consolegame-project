#include "common.h"    
#include "round1.h"

#define WIDTH 52
#define HEIGHT 22             

#define EMOJI_SET 20 // 사용할 이모지 세트 최대 수
#define EMOJI_LEN 7 // 각 이모지 문자열 길이

#define INIT_TIME 60 // 게임 초기 제한 시간 (초)
#define BONUS_TIME 10 // 하트 획득 시 추가 시간 (초)
#define MOMENTUM_MAX 8 // 운동량 최대치 (움직일수록 증가)
#define MOMENTUM_FREEZE_TICKS 20 // 운동량 최대 도달 시 정지 시간 (틱 단위, 0.1초 간격으로 2초)

// 함수 선언부
// int getch_round1();
int getch_round1(void);
int kbhit_round1();
char getKey();
void print_banner(char banner[3][WIDTH], int momentum);
void print_map(char map[HEIGHT][WIDTH], char emojis_char[EMOJI_SET][EMOJI_LEN], char emoji_map[EMOJI_SET][EMOJI_LEN], int *player, int *heart);
void update_player_position(char move, int *current, int *next);
int apply_player_move(char map[HEIGHT][WIDTH], int *current, int *next, int *heart);

int open_round1(void)
{
    system("clear");  
    print_younghee();
    sleep(2);

    srand(time(NULL));

    char map1_banner[3][WIDTH] = {
        "11111111111111111111111111111111111111111111111111",
        "11111111111111111111111111111111111111111111111111",
        "11111111111111111111111111111111111111111111111111"
    };

    // 0: 이동 가능, 1: 벽, 2/9: 꽃밭, 6: 반짝임, 7: 도착지
    char map1[HEIGHT][WIDTH] = {
        "11111111111111111111111111111111111111111111111111",
        "10000000000000000001110000000111111111111111111111",
        "10000000000000000000001111111001111111111111111111",
        "11111111111100000000111000000000000000000000000001",
        "10000000000000000001100011100011001111111111111111",
        "10000000000000000011001111111001100111111111111111",
        "11111111111111100001100011100011000000000000000001",
        "10000000000000000000111000001110011111111111111111",
        "10000000000000000000001111111100111111111111111111",
        "11111000000000001111000000000000000000000000000001",
        "10000000000000000000000000000000000000000000000001",
        "11111111111111111111111111111000000000000000000001",
        "17600000000000100000000000111111111111011100000001",
        "16600000000001110000000000000011111111000000000001",
        "11110000000011000011100011100011000011000000000001",
        "10000000000110001100000000000011000011000011111111",
        "11111110000001000110110011110011000000000000000001",
        "11111100000011100011011100001011011111000000000001",
        "10000000110000000001100000000011011111000001111111",
        "11111101111111111111110111111000000000000000000001",
        "10000000111100000000000000000000000111000000000001",
        "11111111111111111111111111111111111111111111111111",
    };

    // 플레이어 이모지 및 맵용 이모지
    char emojis_char[EMOJI_SET][EMOJI_LEN] = {"👦", "🧔", "👧", "👵"};
    char emoji_map[EMOJI_SET][EMOJI_LEN] = {
        "🌺", "🌸", "🟪", "⬜", "🟨", "💰", "✨", "💖"
    };

    // int player_emoji = 0; // 현재 사용할 플레이어 이모지 인덱스
    int player_current[2] = {1, 1}; // 현재 위치
    int player_next[2] = {1, 1}; // 이동 시도 위치
    char move = 0; // 입력 키
    int heart_current[2] = {27, 4}; // 하트 위치
    int momentum = 1; // 운동량 초기값
    int freeze_ticks = 0; // 정지 상태 카운터

    time_t start_time = time(NULL); // 시작 시간
    int remaining_time = INIT_TIME; // 남은 시간

    int falg_result = 0;

    while (remaining_time > 0)
    {
        // printf("\033[H");
        system("clear");
        printf("\x1b[H"); // 화면 깜빡임 최소화

        time_t now = time(NULL);
        remaining_time = INIT_TIME - (now - start_time); // 시간 갱신

        // 배너 출력
        print_banner(map1_banner, momentum);    
        // 맵 출력
        print_map(map1, emojis_char, emoji_map, player_current, heart_current); 

        // 입력 키 받아오기
        move = getKey();                        

        // 운동량 최대치에 도달한 경우
        if (momentum == MOMENTUM_MAX)           
        {
            // system("clear");
            // 정지 틱 증가
            freeze_ticks++;                     
            if (freeze_ticks >= MOMENTUM_FREEZE_TICKS)
            {
                // 운동량
                momentum--;
                // 정지 상태
                freeze_ticks = 0;
            }
        }
        // 입력이 있는 경우
        else if (move)                          
        {
            // 이동 좌표 계산
            update_player_position(move, player_current, player_next); 
            // 실제 이동 적용
            int heart_collected = apply_player_move(map1, player_current, player_next, heart_current); 

            // 하트 획득 여부
            if (heart_collected == 1)
            {
                remaining_time += BONUS_TIME;
                start_time = now - (INIT_TIME - remaining_time);
            }
            else if (heart_collected == 2)
            {
                system("clear");
                maskMan();  
                printf("\n\n                💰 생존! 다음 게임으로 넘어갑니다.💰\n\n\n\n\n\n\n");
                sleep(3);
                falg_result = 1;
                return 1;
                break;
            }

            // 최대가 아니면 운동량 증가
            if (momentum < MOMENTUM_MAX)        
                momentum++;
        }
        else
        {
            // 멈춰있고 정지상태가 아닐 경우dd
            if (momentum > 1 && freeze_ticks == 0) 
                // 운동량 감소
                momentum--;                     
        }

        printf("⏰ 남은 시간 : %02d초\n", remaining_time);
        // printf("게이지 : %d\n\n\n\n\n\n", momentum);

        usleep(100000); // 0.1초 대기
    }
    if (falg_result != 1)
    {
        gun44();
        sleep(3);
        system("clear");
        youDie();
        printf("\n\n               💥 탈락입니다! 💥 \n\n\n\n\n");
        sleep(3);
        return 9;
    }
    
    return 1;
}

// 운동량에 따라 출력 길이가 변하는 상단 배너
void print_banner(char banner[3][WIDTH], int momentum)
{
    int filled_cols = (momentum * WIDTH) / MOMENTUM_MAX;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < filled_cols; j++)
        {
            if (banner[i][j] == '1')
                printf("%s", "🧊");
        }
        printf("\n");
    }
}

// 게임 맵 출력
void print_map(char map[HEIGHT][WIDTH], char emojis_char[EMOJI_SET][EMOJI_LEN], char emoji_map[EMOJI_SET][EMOJI_LEN], int *player, int *heart)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            // 플레이어
            if (i == player[1] && j == player[0]) 
            {
                // 꽃밭
                if (map[i][j] == '9')
                    printf("%s", emoji_map[rand() % 2]);
                else
                    printf("%s", emojis_char[playerstate.emoji]);
            }
            // 하트
            else if (i == heart[1] && j == heart[0])
                printf("%s", emoji_map[7]);
            // 벽
            else if (map[i][j] == '1')
                printf("%s", emoji_map[2]);
            // 이동 가능
            else if (map[i][j] == '0')
                printf("%s", emoji_map[3]);
            // 꽃밭
            else if (map[i][j] == '2' || map[i][j] == '9')
                printf("%s", emoji_map[rand() % 2]);
            // 돈다발
            else if (map[i][j] == '7')
                printf("%s", emoji_map[5]);
            // 반짝이
            else if (map[i][j] == '6')
                printf("%s", emoji_map[6]);
            // 널값 체크
            else
                printf(" ");
        }
        printf("\n");
    }
}

// 이동 좌표 계산
void update_player_position(char move, int *current, int *next)
{
    next[0] = current[0];
    next[1] = current[1];

    if (move == 'w') next[1]--;
    else if (move == 's') next[1]++;
    else if (move == 'a') next[0]--;
    else if (move == 'd') next[0]++;
}

// 맵 상태에 따른 이동 처리
int apply_player_move(char map[HEIGHT][WIDTH], int *current, int *next, int *heart)
{
    // 이동 가능 지
    if (map[next[1]][next[0]] == '0' || map[next[1]][next[0]] == '9' || map[next[1]][next[0]] == '6' || map[next[1]][next[0]] == '7')
    {
        current[0] = next[0];
        current[1] = next[1];
    }

    // 하트 먹음
    if (next[1] == heart[1] && next[0] == heart[0])
    {
        heart[0] = (rand() % 48) + 1;
        heart[1] = (rand() % 17) + 1;
        return 1;
    }

    // 돈다발
    if (map[next[1]][next[0]] == '7')
        return 2;

    return 0;
}

// 사용자 키 입력 처리 함수들
// 한 글자를 즉시 입력받되, 화면에 표시하지 않음 (에코 끔)
int getch_round1(void)
{
    int c;  // 입력 받은 문자 저장용 변수
    struct termios oldattr, newattr; // 터미널 속성 저장 구조체

    tcgetattr(STDIN_FILENO, &oldattr); // 현재 터미널 설정 읽어옴
    newattr = oldattr;                 // 원본 복사
    newattr.c_lflag &= ~(ICANON | ECHO); // 비표준 모드(ICANON 끔) + 입력 문자 화면에 표시 안 함(ECHO 끔)
    newattr.c_cc[VMIN] = 1;            // 최소 1글자 입력을 기다림
    newattr.c_cc[VTIME] = 0;           // 입력 대기 시간 없음 (즉시 대기)

    tcsetattr(STDIN_FILENO, TCSANOW, &newattr); // 수정된 설정을 즉시 적용
    c = getchar();                    // 문자 1개 입력 받음
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr); // 원래 터미널 설정 복원

    return c;  // 입력 받은 문자 반환
}

// 버퍼에 값이 들어오면 1, 없으면 0
int kbhit_round1(void)
{
    struct termios oldt, newt;  // 터미널 설정 구조체
    int ch;                     // 문자 저장용 변수
    int oldf;                   // 파일 상태 저장용

    tcgetattr(STDIN_FILENO, &oldt); // 현재 터미널 설정 저장
    newt = oldt;                    // 복사
    newt.c_lflag &= ~(ICANON | ECHO); // 비표준 입력 모드 설정
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // 새로운 설정 적용

    oldf = fcntl(STDIN_FILENO, F_GETFL, 0); // 현재 파일 플래그 가져옴
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK); // 논블로킹 모드로 설정

    ch = getchar(); // 입력 시도 (없으면 -1 반환됨)

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // 원래 터미널 설정 복원
    fcntl(STDIN_FILENO, F_SETFL, oldf);      // 원래 파일 플래그 복원

    if (ch != EOF) // 입력이 있었다면
    {
        ungetc(ch, stdin); // 입력값을 다시 버퍼에 넣기
        return 1;          // 키 입력 있음
    }
    return 0; // 키 입력 없음
}

char getKey(void)
{
    __fpurge(stdin);  // 입력 버퍼 비우기 (GNU 확장 함수)
    if (kbhit_round1())      // 키가 눌렸다면
        return getch_round1(); // 해당 키 반환
    return 0;         // 입력이 없으면 0
}        // // 1라운드 성공
        // if (open_round1() == 1)
        // {
        //     // 2라운드 성공
        //     if (open_round2() == 1)
        //     {
        //         // 3라운드 성공   
        //         if (open_round3() == 1)
        //         {
        //             // 4라운드 성공
        //             if (open_round4() == 1)
        //             {
        //                 printf("\n\n\n\nsuccess!!!!!!!\n\n\n\n\n\n");
        //             }
                    
        //         }
                
        //     }
            
        // }