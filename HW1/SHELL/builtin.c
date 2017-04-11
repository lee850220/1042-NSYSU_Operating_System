#include "kshell.h"

void builtin_cmd(){
	char *tmp=create_str(STR_LENG);
	
	if(strcmp(Parameter[0][0],"exit")==0||strcmp(Parameter[0][0],"quit")==0){
		printf("\nGOOD BYE!\n");
		TERMINAL_END=2;
	}
	
	if(strcmp(Parameter[0][0],"cd")==0){
		chdir(Parameter[0][1]);
		TERMINAL_END=1;
	}
	
	if(strcmp(Parameter[0][0],"ll")==0){
		strcpy(Parameter[0][0],"ls");
		strcpy(Parameter[0][0],"ls");
		if(Parameter[0][1]!=0x0){
			Parameter[0][2]=create_str(4);
			strcpy(Parameter[0][2],"-al");
		}else{
			Parameter[0][1]=create_str(4);
			strcpy(Parameter[0][1],"-al");
		}
	}	
	
	free(tmp);	
}
