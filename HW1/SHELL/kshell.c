/* To see more information in kshell.h */
#include "kshell.h"

void type_prompt(){						
	char *hostname=create_str(100);
	char *dirpath=create_str(STR_LENG);
	if(hostname==NULL||dirpath==NULL)	exit(EXIT_FAILURE);
	struct passwd *user=NULL;
		
	gethostname(hostname,100);				//取得主機名
	user=getpwuid(getuid());				//取得USER資訊
	getcwd(LOCAL_PATH,STR_LENG);			//取得當前路徑
	strcpy(dirpath,LOCAL_PATH);
	if(user!=NULL&&strlen(hostname)!=0){	//檢查用戶資訊是否取得成功
		check_path(dirpath,user->pw_name);	//省略部份路徑
		if(strcmp(user->pw_name,"root")!=0){
			printf("[Kshell]%s@%s:%s$ ",user->pw_name,hostname,dirpath);
		}else{
			printf("[Kshell]%s@%s:%s# ",user->pw_name,hostname,dirpath);
		}
	}else{
		perror("-Kshell");
	}
	
	free(hostname);
	free(dirpath);
}

void read_command(){
	int x=0,i=0;
	char *piping=NULL, *redir=NULL, *new_str=NULL;
	char *tmp=create_str(STR_LENG);
	char *tok_command[5];
	
	for(i=0; i<5; i++)	tok_command[i]=0x0;
	if(tmp==NULL)	exit(EXIT_FAILURE);
	fgets(tmp,STR_LENG,stdin);
	rm_wspace(tmp);
	if(tmp[0]=='\n'){
		TERMINAL_END=3;						//若無指令返回1，回到迴圈起始位置
	}else{	
		preprocess(tmp);					//命令預處理
		
		/* 檢測PIPING */
		piping=strchr(tmp,'|');
		if(piping!=NULL){
			IS_pipe_on=1;
			for(i=0; i<STR_LENG && pipe_count<5; i++){
				if(tmp[i]=='|')	pipe_count++;
			}
			new_str=strtok(tmp,"|");
			while(new_str!=NULL){
				tok_command[x]=alloc_par(new_str);
				new_str = strtok (NULL,"|");
				x++;
			}
		}else{
			tok_command[0]=tmp;
		}
		
		/* 檢測REDIRECTION */
		redir=strchr(tmp,'>');
		if(redir!=NULL){			
			if(*(redir+1)=='>')	IS_redir=2;
			else IS_redir=1;			
/*			if(IS_pipe_on==1){						//暫不開發同時PIPE & REDIRECTION
				new_str=strtok(tok_command[x],">"*/
			x=0;
			if(IS_redir==1){
				new_str=strtok(tmp,">");
				while(new_str!=NULL){
					tok_command[x]=alloc_par(new_str);
					new_str = strtok (NULL,">");
					x++;
				}
			}else{
				new_str=strtok(tmp,">>");
				while(new_str!=NULL){
					tok_command[x]=alloc_par(new_str);
					new_str = strtok (NULL,">>");
					x++;
				}
			}
			if(strchr(tok_command[1],'/')==NULL){
				strcat(LOCAL_PATH,"/");
				rm_wspace(tok_command[1]);
				strcat(LOCAL_PATH,tok_command[1]);
			}
		}
		
		/* 擷取參數 */
		for(i=0; i<=pipe_count ;i++){
			new_str = strtok(tok_command[i]," ");	
			x=0;			
			while (new_str!=NULL){
				Parameter[i][x]=alloc_par(new_str);
				new_str = strtok (NULL," ");
				x++;	
			}
		}
		
	}	
	free(tmp);
}

void run_process(){
	FILE *fp=NULL;
	int status=0;	
	int pipe_fd[2];												
	pid_t pid1=0,pid2=0;
	
	if(IS_pipe_on==1){									//當有PIPE
		if(pipe(pipe_fd)==-1)	perror("-Kshell");
		pid1=fork();
		if(pid1>0){											//In Parent
			pid2=fork();
			if(pid2==0){									//process2
				close(pipe_fd[1]);
				close(STD_INPUT);
				dup2(pipe_fd[0],0);
				close(pipe_fd[0]);
				execvp(Parameter[1][0],Parameter[1]);
			}else if(pid2>0){
				close(pipe_fd[0]);
				close(pipe_fd[1]);
				waitpid(pid2,NULL,0);
			}	
		}else if(pid1==0){									//process1
			close(pipe_fd[0]);
			close(STD_OUTPUT);
			dup2(pipe_fd[1],1);
			close(pipe_fd[1]);
			execvp(Parameter[0][0],Parameter[0]);
		}
	}else if(IS_redir>0){								//當有重定向
		if(IS_redir==1)	fp=fopen(LOCAL_PATH,"w");
		else 	fp=fopen(LOCAL_PATH,"a");
		
		pid1=fork();										
		if(pid1>0){											//In Parent
			if(IS_nowait==0)
				waitpid(-1,&status,0);
			else{
				process_num++;
				printf("[%d] %d\n",process_num,pid1);
			}
		}else if(pid1==0){									//In Child
			close(STD_OUTPUT);
			dup2(fileno(fp),1);
			execvp(Parameter[0][0],Parameter[0]);			//執行命令
		}else{
			perror("-Kshell");
		}
		fclose(fp);
	}else{											//正常執行
		pid1=fork();										
		if(pid1>0){											//In Parent
			if(IS_nowait==0){
				waitpid(pid1,NULL,0);
			}else{
				process_num++;
				printf("[%d] %d\n",process_num,pid1);
			}
		}else if(pid1==0){									//In Child
			if(execvp(Parameter[0][0],Parameter[0])==-1){	//執行命令
				exit(0);
				
			}
		}else{
			perror("-Kshell");
		}
	}
}
/*-------------------------------------------------------MAIN--------------------------------------------------------*/
int main(){
	int i=0,j=0;
				
	for(i=0; i<5; i++)
		for(j=0; j<50 ; j++)
			Parameter[i][j]=NULL;
	
	while(1){		
		type_prompt();			//顯示提示符
		read_command();			//讀取命令
		if(TERMINAL_END==3){
			clear_var();
			continue;
		}
		builtin_cmd();		
		
		/* DEBUG */
		if(Debug()){				
			clear_var();
			continue;
		}
				
		if(TERMINAL_END==1)	;
		else if(TERMINAL_END==2)	break;
		else{
			run_process();		//執行命令
		}
		clear_var();			//清空變數
	}
	return 0;
}
/*-------------------------------------------------------END---------------------------------------------------------*/
void preprocess(char *str){
	int i=0;
	char *tmp=create_str(STR_LENG), *new_str=NULL, *ampersand=NULL;
	char *skip_symb=strchr(str,'~');
	
	/* 捨棄換行符 */
	for(i=0; i<STR_LENG ; i++){		
		if(str[i]=='\n'){
			str[i]='\0';
			break;
		}
	}
	
	/* 檢測後台運行 */
		ampersand=strchr(str,'&');		
		if(ampersand!=NULL && *(ampersand-1)==' ')	{
			IS_nowait=1;
			*ampersand='\0';
		}
	
	/* 替換'~'為絕對路徑 */
	if(skip_symb!=NULL && check_symbol(skip_symb)){
		new_str=move_char(str,skip_symb-1);
		strcpy(tmp,new_str);
		strcat(tmp,SKIP_DIR);
		free(new_str);
		new_str=move_char(skip_symb+1,str+STR_LENG-1);
		strcat(tmp,new_str);
		free(new_str);
		memset(str,'\0',STR_LENG);
		strcpy(str,tmp);
	}
	free(tmp);
}

void clear_var(){		//格式化變數
	int i=0,j=0;
	while(i<5){
		if(Parameter[i][0]==0x0)	break;
		for(j=0; j<50 ;j++){
			if(Parameter[i][j]==0x0)	break;
			free(Parameter[i][j]);
			Parameter[i][j]=0x0;
		}
		i++;
	}
	memset(LOCAL_PATH,'\0',STR_LENG);
	IS_nowait=0;
	IS_pipe_on=0;
	IS_redir=0;	
	pipe_count=0;
	TERMINAL_END=0;
}






