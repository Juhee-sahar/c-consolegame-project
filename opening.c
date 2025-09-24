#include "common.h"    
#include "opening.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4  // 선택 (스페이스바)

int menuDraw();
int keyControl();
void init();
void titleDraw();
void gotoxy(int,int);
void infoDraw();   //게임정보
// void charicter();
int chari();
void charicter_choice();
int getch_opening();

GameState playerstate = {
    .emoji = 0,
    .point = 0 
};


int open_opening()       /////////////////////////////메인창////////////////////////////////////
{
    init();
    
    squidGame_5();  // 아트 출력
    sleep(2);
    system("clear");
    first();
    sleep(3);
    system("clear");

    while(1)
    {
        titleDraw();
        int menuCode = menuDraw();
        if (menuCode == 0)  // 게임시작
        {
            charicter_choice();
            return 1;
        }
        else if (menuCode == 1)
        {
            infoDraw();  // 게임정보
        }
        else if (menuCode == 2)
        {
            return 0;   // 종료
        }
        system("clear");
    }


    return 0;
}

int keyControl()
{
    char temp = getch_opening();

    if (temp == 'w' || temp == 'W'){ 
        return UP; 
    } else if (temp == 'a' || temp == 'A'){
        return LEFT;
    } else if (temp == 's' || temp == 'S'){
        return DOWN;
    } else if (temp == 'd' || temp == 'D'){
        return RIGHT;
    } else if (temp == ' '){   // 스페이스바(공백)이 선택 버튼
        return SUBMIT;
    }

    return -1;
}



void titleDraw()
{
    printf("\n\n\n\n");
    printf("⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\n");
    printf("⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\n");
    printf("⬛⬛⭐️⭐️⭐️⭐️⬛⬛⭐️⭐️⭐️⬛⬛⭐️⬛⬛⬛⭐️⬛⬛⭐️⬛⭐️⭐️⭐️⭐️⬛⬛⬛⬛⭐️⭐️⭐️⭐️⬛⬛⬛⭐️⬛⬛⬛⭐️⬛⬛⬛⭐️⬛⭐️⭐️⭐️⭐️⭐️⬛\n");
    printf("⬛⭐️⬛⬛⬛⬛⬛⭐️⬛⬛⬛⭐️⬛⭐️⬛⬛⬛⭐️⬛⬛⭐️⬛⭐️⬛⬛⬛⭐️⬛⬛⭐️⬛⬛⬛⬛⬛⬛⭐️⬛⭐️⬛⬛⭐️⭐️⬛⭐️⭐️⬛⭐️⬛⬛⬛⬛⬛\n");
    printf("⬛⬛⭐️⭐️⭐️⭐️⬛⭐️⬛⬛⬛⭐️⬛⭐️⬛⬛⬛⭐️⬛⬛⭐️⬛⭐️⬛⬛⬛⭐️⬛⬛⭐️⬛⭐️⭐️⬛⬛⭐️⭐️⭐️⭐️⭐️⬛⭐️⬛⭐️⬛⭐️⬛⭐️⭐️⭐️⭐️⭐️⬛\n");
    printf("⬛⬛⬛⬛⬛⭐️⬛⭐️⬛⬛⭐️⬛⬛⭐️⬛⬛⬛⭐️⬛⬛⭐️⬛⭐️⬛⬛⬛⭐️⬛⬛⭐️⬛⬛⬛⭐️⬛⭐️⬛⬛⬛⭐️⬛⭐️⬛⬛⬛⭐️⬛⭐️⬛⬛⬛⬛⬛\n");
    printf("⬛⭐️⭐️⭐️⭐️⬛⬛⬛⭐️⭐️⬛⭐️⬛⬛⭐️⭐️⭐️⬛⬛⬛⭐️⬛⭐️⭐️⭐️⭐️⬛⬛⬛⬛⭐️⭐️⭐️⬛⬛⭐️⬛⬛⬛⭐️⬛⭐️⬛⬛⬛⭐️⬛⭐️⭐️⭐️⭐️⭐️⬛\n");
    printf("⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\n");
    printf("⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\n");


}

void init()    // 프로그램 실행직후 초기화 작업card_art()
{
    system("clear");   // 화면 지우기
    printf("\033[?25l"); // 커서 숨기기 (필요 시)
    // printf("\033[?25h");   //커서 다시 보이게
}


void gotoxy(int x, int y)   // 커서 위치 이동하는 함수
{
    printf("\033[%d;%dH", y, x);
}

int menuDraw()
{
    int x = 42;   //가로
    int y = 16;    //세로

    gotoxy(x-2, y); // - 2 한 이유는 > 를 출력해야 하기 때문

    printf(">   게 임 시 작 ");
    gotoxy(x, y+1);
    printf("  게 임 정 보");
    gotoxy(x, y+2);
    printf("     종  료    \n");

    while (1)
    {
        int n = keyControl();      //키보드 이벤트를 키값으로 받아오기
        switch(n){
            case UP : {              // 입력된 키의 값이 UP인 경우(W)
                if ( y>16 ){         // y는 12~14까지만 이동
                    gotoxy(x-2, y);  // x-2 하는 이유는 ">"를 두칸 이전에 출력하기 위해
                    printf(" ");      // 원래 위치를 지우고
                    gotoxy(x-2, --y);  // 새로 이동한 위치로 이동하여
                    printf(">");       // 다시 그리기
                }
                break;
            }

            case DOWN : {              // 입력된 키의 값이 DOWN 인 경우(S)
                if ( y < 18 ){        // 최대 14
                    gotoxy(x-2, y);
                    printf(" ");
                    gotoxy(x-2, ++y);
                    printf(">");
                }
                break;
            }

            case SUBMIT : {
                return y-16;     // 스페이스바(선택) 되었을 경우 y-12
                // y 시작 위치가 12였으므로 y-12를 하면 0,1,2 세 숫자를 받을 수 있다
            }
        }
    }

    return 0;
}

void infoDraw()   //게임정보창
{
    system("clear");
    card_art();
    printf("\n\n\n");
    printf("                                [ 조 작 법 ]\n\n");
    printf("                             이 동 : W, A, S, D\n");
    printf("                             선 택 : 스페이스바 \n\n\n\n");
    printf("                 개 발 자 : 데이빗, 라푸라푸, 오야붕, SAHAR\n\n");
    printf("                스페이스바를 누르면 메인화면으로 이동합니다.\n");

    while(1)
    {
        if (keyControl() == SUBMIT)
        {
            break;
        }
    }
}


////////////캐릭터창 방법1//////////////////

int chari() 
{
    int x = 40;   //가로
    int y = 14;    //세로

    gotoxy(x-2, y); // - 2 한 이유는 > 를 출력해야 하기 때문
    printf(">   👦 (성기훈) ");
    gotoxy(x, y+1);
    printf("  🧔 (박영식)");
    gotoxy(x, y+2);
    printf("  👧 (준희)");
    gotoxy(x, y+3);
    printf("  👵 (장금자)");
    // gotoxy(x, y+4);
    // printf("  ↩️  뒤로가기");
    

    while (1)
    {
        int n = keyControl();      //키보드 이벤트를 키값으로 받아오기
        switch(n){
            case UP : {              // 입력된 키의 값이 UP인 경우(W)
                if ( y>14 ){        
                    gotoxy(x-2, y);  // x-2 하는 이유는 ">"를 두칸 이전에 출력하기 위해
                    printf(" ");      // 원래 위치를 지우고
                    gotoxy(x-2, --y);  // 새로 이동한 위치로 이동하여
                    printf(">");       // 다시 그리기
                }
                break;
            }

            case DOWN : {              // 입력된 키의 값이 DOWN 인 경우(S)
                if ( y < 18 ){        
                    gotoxy(x-2, y);
                    printf(" ");
                    gotoxy(x-2, ++y);
                    printf(">");
                }
                break;
            }

            case SUBMIT : {
                return y-14;   
            }
        }
    }
}

void charicter_choice()
{
    system("clear");

    int x = 20;   //가로
    int y = 5;    //세로
    gotoxy(x,y);
    printf("========================================================");
    gotoxy(30,8);
    printf("        캐릭터를 선택해주세요.\n");
    gotoxy(x,10);
    printf("========================================================");
    gotoxy(x,20);
    printf("========================================================");

    int selected = chari();  // 0~3 중 하나 반환됨

    if (selected == 4)
        return;   // 메인메뉴로 돌아감

    system("clear");

    switch (selected)
    {
        case 0:
            gamer456();
            printf("\n           1번 성기훈를 선택하셨습니다.\n");
            playerstate.emoji = 0;

            break;
        case 1:
            gamer007();
            printf("\n           2번 박영식를 선택하셨습니다.\n");
            playerstate.emoji = 1;

            break;
        case 2:
            gamer222();
            printf("\n           3번 준희를 선택하셨습니다.\n");
            playerstate.emoji = 2;

            break;
        case 3:
            gamer149();
            printf("\n           4번 장금자를 선택하셨습니다.\n");
            playerstate.emoji = 3;

            break;

    }

    sleep(2);  // 출력 유지
}

int getch_opening()   // 한글자 입력을 바로 받을 수 있게 해주는 함수
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
