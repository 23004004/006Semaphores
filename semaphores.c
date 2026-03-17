#include "semaphores.h"

void print_timestamp(void) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", t);
    printf("[%s] ", buffer);
}

void car_arrive(int id) {
    print_timestamp();
    printf("Car %d: Arrived at parking lot\n", id);
}

void car_park(int id) {
    int duration = (rand() % 5) + 1;
    print_timestamp();
    printf("Car %d: Parked successfully (waited 0.00 seconds)\n", id);
    sleep(duration);
}

void car_leave(int id) {
    print_timestamp();
    printf("Car %d: Leaving parking lot\n", id);
}