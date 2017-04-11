/* ****************************************************************************************************
 * Project Name: PHILOSOPHER DINING PROBLEM
 * Author: Kelvin Lee 李冠霖
 * Language: C++
 * Environment: Linux
 * Date: 2016/04/24  23:30
 * ****************************************************************************************************/
 #include "philo.h"
/*------------------------------------------DECLARE VAR & FUNC----------------------------------------*/


/*---------------------------------------------DECLARE END--------------------------------------------*/
void test(int i){
	if(state[i]==HUNGRY && state[LEFT]!= EATING && state[RIGHT]!= EATING){
		state[i]=EATING;
//		sem_up();
	}
}

void take_forks(int i){
	pthread_mutex_lock(&mutex);
	state[i]=HUNGRY;
	test(i);
	pthread_mutex_unlock(&mutex);
//	sem_trywait(s[i]);
}

void put_forks(int i){
	pthread_mutex_lock(&mutex);
	state[i]=THINKING;
	test(LEFT);
	test(RIGHT);
	pthread_mutex_unlock(&mutex);
}

void print(){
	int i=0;
	
	cls();
	for(i=1; i<=5; i++){
		printf("philosopher %d is ",i);
		switch(state[i-1]){
		case 0:
			printf("THINKING\n");
			break;
		case 1:
			printf("HUNGRY\n");
			break;
		case 2:
			printf("EATING\n");
			break;
		}
	}
}

void philosopher(int i){
//	int eat_count=0;
	
	while(1){
//		think();
		take_forks(i);
//		eat();
		put_forks(i);
	}
}

int main(){
	int i=0;

	pthread_t philo[PHILO];
	
	pthread_mutex_init(&mutex, NULL);
	for(i=0; i<5; i++){
//		sem_init(&s[i],0,1);
		pthread_create(&philo[i], NULL, (void*)philosopher, (void *)(intptr_t)i);
	}
	while(1){
		print();
		usleep(100000);
	}
	pthread_join(philo[i], NULL);
	
	return 0;
}


