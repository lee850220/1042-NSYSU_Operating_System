SRC= philo.cpp philo.h
OBJ= $(SRC:.cpp=.o)

CPP= g++
OPTION= -c -g

all: .PHONY

.PHONY: philo clean

%.o:%.c
	$(CPP) $^ $(OPTION) -pthread 

philo:$(OBJ)
	$(CPP) $^ -o $@.exe -pthread

clean:
	@rm -rf *.o *.*~ *~
