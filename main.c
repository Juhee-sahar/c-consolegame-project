#include <stdio.h>

#include "opening.h"
#include "round1.h"
#include "round2.h"
#include "round3.h"
#include "round4.h"

/**
시작페이지>>

1라운드 >>
2라운드 >>
3라운드 >>
4라운드 >>

라운드별 성공 return 1
라운드별 실페 return 9
 */

int main(void)
{
    for (;;) // 게임 전체 반복 루프
    {
        // // 시작
        if (open_opening() != 1)
        {
            break;
        }

// open_round3();  // 테스트용

        // // 1라운드 성공
        if (open_round1() == 1)
        {
            // 2라운드 성공
            if (open_round2() == 1)
            {
                // 3라운드 성공   
                if (open_round3() == 1)
                {
                    // 4라운드 성공
                    if (open_round4() == 1)
                    {
                        printf("\n\n\n\nsuccess!!!!!!!\n\n\n\n\n\n");
                    }
                    
                }
                
            }
            
        }
        
        
    }

    return 0;
}