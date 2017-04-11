#include "kshell.h"

void check_path(char *dirpath,char *username){			//辨識路徑(自動刪減)
	int skip_length=0,dir_length=0;
	char *dir_skip=(char*)malloc(sizeof(char)*100);
	char *move_str=NULL;
	
	if(dir_skip==NULL)	exit(EXIT_FAILURE);
	
	/* 配置欲省略之路徑 */
	memset(dir_skip,'\0',100);
	strcpy(dir_skip,"/home/");
	strcat(dir_skip,username);							
	memset(SKIP_DIR,'\0',100);
	strcpy(SKIP_DIR,dir_skip);	
							
	skip_length=strlen(dir_skip);
	dir_length=strlen(dirpath);
	if(strncmp(dirpath,dir_skip,skip_length)==0){		//比對相同部份並省略		
		dirpath[skip_length-1]='~';
		move_str=move_char(strchr(dirpath,'~'),dirpath+dir_length);
		memset(dirpath,'\0',STR_LENG);
		strcpy(dirpath,move_str);
	}
	free(move_str);
	free(dir_skip);
}

char *alloc_par(const char *str){						//分配記憶體給擷取的字串
	int i=0;
	char *tmp=create_str(50);
	for(i=0;i<50;i++) tmp[i]='\0';
	strcpy(tmp,str);
	return tmp;
}

char *create_str(int length){				//動態分配字串空間並格式化
	char *tmp=malloc(sizeof(char)*length);
	if(tmp!=NULL)	memset(tmp,'\0',length);
	return tmp;
}

char *move_char(char *start_point, char *end_point){	//擷取字串
	int char_space=0,x=0;
	char *tmp=NULL,*i=NULL;
	
	for(i=start_point; i!=end_point+1; i++)	char_space++;
	tmp=create_str(char_space+1);
	if(tmp==NULL)	exit(EXIT_FAILURE);
	memset(tmp,'\0',char_space);
	for(i=start_point; i!=end_point+1; i++){
		tmp[x]=*i;
		x++;
	}
	return tmp;
}

void rm_wspace(char* str){					//刪除多餘空白字元
	int x=0;
	char *tmp=create_str(STR_LENG);
	
	memset(tmp,'\0',STR_LENG);
	if(tmp==NULL)	exit(EXIT_FAILURE);
	if(str[0]==' '){
		while(str[x]==' ')	x++;			//計算空白長度		
		tmp=move_char(str+x,str+STR_LENG-1);
		memset(str,'\0',STR_LENG);
		strcpy(str,tmp);
	}
	free(tmp);
}

int check_symbol(const char *symb){
	if(*(symb-1)==' ' && *(symb+1)==' ')	return 1;
	else if(*(symb-1)==' ' && *(symb+1)!=' ')	return 1;
	else return 0;
}

void clear_str(char *str){
	int i=0;
	
	while(1){
		if(str[i]=='\0' && str[i+1]=='\0') break;
		str[i]='\0';
	}
}

int Debug(){
#ifdef DEBUG
	int i=0,j=0;

	while(i<5){
		if(Parameter[i][0]==0x0)	break;
		for(j=0; j<50 ;j++){
			if(Parameter[i][j]==0x0)	break;
			printf("arg%d[%d]=%s",i,j,Parameter[i][j]);
		}
		i++;
	}
	printf("\n");	
#ifdef NO_RESULT
	return 1;
#endif
#endif
	return 0;
}
