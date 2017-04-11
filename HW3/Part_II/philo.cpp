/* ****************************************************************************************************
 * Project Name: PHILOSOPHER DINING PROBLEM
 * Author: Kelvin Lee 李冠霖
 * Language: C++11
 * Environment: Linux
 * Date: 2016/04/24  23:30
 * ****************************************************************************************************/
/*----------------------------------------------PREPROCESS--------------------------------------------*/
#include "philo.h"
/*----------------------------------------------------------------------------------------------------*/
void print(){
	int i=0;
	
	cls();
	for(i=0; i<PHILO; i++){
		cout<<"philosopher "<< i+1 <<" is ";
		switch(state[i]){
		case 0:
			cout<<"THINKING\n";
			break;
		case 1:
			cout<<"HUNGRY\n";
			break;
		case 2:
			cout<<"EATING\n";
			break;
		}
	}
	usleep(10000);
}

void *philosopher(void* i){
    long a=(long)i;
    
    while(1){
        monitor.CritcalRegion();
        monitor.takeForks(a);
        monitor.CritcalRegion();
        monitor.putForks(a);
    }
}

int main(){
	int x=0;
	
	pthread_t philo[PHILO];
	for(x=0; x<PHILO; x++){
		pthread_create(&philo[x], NULL, philosopher, (void*)x);
	}
	while(1){
		print();
		usleep(500000);
	}	
	for(x=0; x<5; x++){
		pthread_join(philo[x], NULL);
	}
	
	
	return 0;
}


