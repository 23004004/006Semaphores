#include "semaphores.h"

int available_spaces = NUM_SPACES;

int main(void){
    srand(time(NULL));
    parking();
    return 0;
}

void parking(void){
    int total_parked = 0;
    double total_wait = 0.0;

    printf("Parqueo abierto\n");

    for (int i = 0; i < NUM_CARS; i++)
    {
        car_arrive(i);
        car_park(i);
        car_leave(i);
        total_parked++;
        total_wait += 0.0;
    }

    printf("\nTotal cars parked: %d\n", total_parked);
    printf("Average wait time: %.2f seconds\n", total_wait / total_parked);
}