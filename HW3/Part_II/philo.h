/* ****************************************************************************************************
 * Project Name: PHILOSOPHER DINING PROBLEM
 * Author: Kelvin Lee 李冠霖
 * Language: C++11
 * Environment: Linux
 * Date: 2016/04/24  23:30
 * ****************************************************************************************************/
 
/*----------------------------------------------PREPROCESS--------------------------------------------*/
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#define PHILO 5
#define LEFT (i+PHILO-1)%PHILO
#define RIGHT (i+1)%PHILO
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define cls() cout<<"\033[H\033[J"
using namespace std;

/* Declare Global Var */
class Monitor{
    public:
        Monitor();
        void takeForks(int);
        void putForks(int);
        void CritcalRegion();
        
    private:
        pthread_mutex_t mutex;
        pthread_cond_t cond;
};

int state[PHILO];

Monitor monitor=Monitor();

/* Declare Functions */
Monitor::Monitor(){
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
}

void Monitor::CritcalRegion(){
    if(pthread_mutex_lock(&mutex)){
        pthread_cond_wait(&cond, &mutex);
    }
    else{
        pthread_cond_signal(&cond);
    }
}

void Monitor::takeForks(int i){
    state[i]=HUNGRY;
    if(state[i]==HUNGRY && state[LEFT]!= EATING && state[RIGHT]!= EATING){
	    state[i]=EATING;
    }
    pthread_mutex_unlock(&mutex);
}

void Monitor::putForks(int i){
    int tmp=i;

    state[i]=THINKING;
    i=LEFT;
    if(state[tmp]==HUNGRY && state[LEFT]!= EATING && state[RIGHT]!= EATING){
	    state[tmp]=EATING;
    }
    i=tmp;
    i=RIGHT;
    if(state[tmp]==HUNGRY && state[LEFT]!= EATING && state[RIGHT]!= EATING){
	    state[tmp]=EATING;
    }
    pthread_mutex_unlock(&mutex);
}


/*----------------------------------------------------------------------------------------------------*/



