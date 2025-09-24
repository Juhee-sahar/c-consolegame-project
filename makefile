# 변수 선언 (선택사항)
CC = gcc
CFLAGS = -Wall -g

# 소스 파일 목록
SRCS = main.c common.c opening.c round1.c round2.c round3.c round4.c console_art.c

# 오브젝트 파일 목록 (SRCS의 .c를 .o로 변환)
OBJS = $(SRCS:.c=.o)

# 최종 실행 파일 이름
TARGET = main

# 기본 타겟 (make 명령어만 쳤을 때 실행됨)
all: $(TARGET)

# 실행 파일 만드는 법 (링킹)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 오브젝트 파일 만드는 법 (컴파일)
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# 깨끗하게 빌드하기 (임시파일 삭제)
clean:
	rm -f $(OBJS) $(TARGET)