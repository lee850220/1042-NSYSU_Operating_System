SRC= philo.c philo.h
OBJ= $(SRC:.c=.o)

CPP= gcc
OPTION= -c -g -o

all: .PHONY

.PHONY: philo clean

%.o:%.c
	$(CPP) $^ $(OPTION) $@ -pthread

philo: $(OBJ)
	$(CPP) $^ -o $@.exe -pthread

clean:
	@rm -rf *.o *.*~ *~
