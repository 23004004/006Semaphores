#include "semaphores.h"

int available_spaces = NUM_SPACES;

int main(void){
    srand(time(NULL));
    parking();
    return 0;
}

void parking(void){
    pthread_t threads[NUM_CARS];
    int ids[NUM_CARS];

    int total_parked = 0;
    double total_wait = 0.0;

    printf("Parqueo abierto\n");

    for (int i = 0; i < NUM_CARS; i++)
    {
        ids[i] = i;
        pthread_create(&threads[i], NULL, cars, &ids[i]);
        total_parked++;
        total_wait += 0.0;
    }

    for (int i = 0; i < NUM_CARS; i++)
    {
        pthread_join(threads[i], NULL);
    }


    printf("\nTotal cars parked: %d\n", total_parked);
    printf("Average wait time: %.2f seconds\n", total_wait / total_parked);
}

void *cars(void *arg){
    int id = *(int *)arg;
    
    car_arrive(id);
    car_park(id);
    car_leave(id);
    
    return NULL;
}