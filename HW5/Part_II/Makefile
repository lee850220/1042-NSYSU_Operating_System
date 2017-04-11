SRC= main.c test.c
OBJ= $(SRC:.c=.o)

C= gcc
CPP= g++
OPTION= -c -g

all: .PHONY

.PHONY: main clean

%.o:%.c
	$(C) $^ $(OPTION)

main:$(OBJ)
	$(C) main.o -o main.exe
	$(C) test.o -o test.exe

clean:
	@rm -rf *.o *.*~ *~
