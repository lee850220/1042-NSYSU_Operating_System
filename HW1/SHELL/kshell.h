/*Author:Kelvin LEE 李冠霖
 *ID	:B035020026
 *Grade	:CSE 107
 *
*/

/* header files */
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
//#include "getch.h"
#include <sys/stat.h>    
#include <fcntl.h>

#define STR_LENG 1024
#define NO_RESULT
#define STD_INPUT 0
#define STD_OUTPUT 1

/* 試用性功能 */
#ifdef READLINE_ON
#include <readline/readline.h>
#include <readline/history.h>
#endif

/* Environment Variable */

/* Global variable */
int TERMINAL_END;
int IS_nowait;
int IS_pipe_on;
int IS_redir;
int pipe_count;
int process_num;
char*Parameter[5][50];
char LOCAL_PATH[STR_LENG];
char SKIP_DIR[100];

/* Function declartion */
void builtin_cmd();
void preprocess(char *);
void check_path(char *,char *);
void rm_wspace(char *);
void clear_str(char *);
char*move_char(char *,char *);
char*alloc_par(const char *);
char*create_str(int);
int check_symbol(const char *);
void clear_var();
int Debug();


