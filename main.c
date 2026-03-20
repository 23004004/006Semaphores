#include "semaphores.h"

sem_t parking_semaphore;
double wait_times[NUM_CARS];
int spaces[NUM_SPACES];
int waiting[NUM_CARS];
int waiting_count = 0;

int main(void){
    srand(time(NULL));
    sem_init(&parking_semaphore, 0, NUM_SPACES);
    for (int i = 0; i < NUM_SPACES; i++) spaces[i] = -1;
    for (int i = 0; i < NUM_CARS; i++) waiting[i] = -1;
    parking();
    sem_destroy(&parking_semaphore);
    return 0;
}

void parking(void){
    pthread_t threads[NUM_CARS];
    int ids[NUM_CARS];


    printf("Parqueo abierto\n");

    for (int i = 0; i < NUM_CARS; i++)
    {
        ids[i] = i;
        pthread_create(&threads[i], NULL, cars, &ids[i]);
    }

    for (int i = 0; i < NUM_CARS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    double total_wait = 0.0;
    for (int i = 0; i < NUM_CARS; i++) {
        total_wait += wait_times[i];
    }



    printf("\nTotal cars parked: %d\n", NUM_CARS);
    printf("Average wait time: %.2f seconds\n", total_wait / NUM_CARS);
}

void *cars(void *arg){
    int id = *(int *)arg;
    
    car_arrive(id);
    car_park(id);
    car_leave(id);
    
    return NULL;
}