# To see more information in kshell.h 
#***** Argument *****
CC= gcc
Option= -g -Wall
Arg= 

Obj= ${Soc:.c=.o}
Soc= kshell.c custom_func.c builtin.c
#*****    End   *****

all: kshell clean
	
kshell: ${Obj}
	${CC} ${Obj} ${Option} -o $@

debug: ${Soc}
	${CC} ${Soc} ${Option} -o $< -D DEBUG

clean:
	@rm -rf *.o
	
help:
	@echo
	@echo
	@cat help.txt
