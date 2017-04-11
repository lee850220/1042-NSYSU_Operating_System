SRC= mm.h mm.c
OBJ= $(SRC:.c=.o)

C= gcc
CPP= g++
OPTION= -c -g

all: .PHONY

.PHONY: mm clean

%.o:%.c
	$(C) $^ $(OPTION)

mm:$(OBJ)
	$(C) $^ -o $@.exe

clean:
	@rm -rf *.o *.*~ *~
