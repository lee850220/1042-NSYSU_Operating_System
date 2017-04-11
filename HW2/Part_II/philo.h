/* ****************************************************************************************************
 * Project Name: PHILOSOPHER DINING PROBLEM
 * Author: Kelvin Lee 李冠霖
 * Language: C
 * Environment: Linux
 * Date: 2016/04/24  23:30
 * ****************************************************************************************************/
 
/*------------------------------------------DECLARE VAR & FUNC----------------------------------------*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#define PHILO 5
#define LEFT (i+PHILO-1)%PHILO
#define RIGHT (i+1)%PHILO
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define cls() printf("\033[H\033[J")

/* Declare Global Var */
int state[PHILO];
pthread_mutex_t mutex;
sem_t s[PHILO];

/* Declare Functions */


/*---------------------------------------------DECLARE END--------------------------------------------*/



