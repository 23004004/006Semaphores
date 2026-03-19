#include "semaphores.h"

pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t stats_mutex = PTHREAD_MUTEX_INITIALIZER;

void print_timestamp(void) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", t);
    printf("[%s] ", buffer);
}

void car_arrive(int id) {
    pthread_mutex_lock(&log_mutex);
    print_timestamp();
    printf("Car %d: Arrived at parking lot\n", id);
    pthread_mutex_unlock(&log_mutex);
}

void car_park(int id) {
    time_t start = time(NULL);
    
    sem_wait(&parking_semaphore);

    double waited = difftime(time(NULL), start);
    wait_times[id] = waited;
    
    int duration = (rand() % 5) + 1;
    
    pthread_mutex_lock(&log_mutex); 
    print_timestamp();
    printf("Car %d: Parked successfully (waited %.2f seconds)\n", id, waited);
    pthread_mutex_unlock(&log_mutex);

    sleep(duration);
}

void car_leave(int id) {
    sem_post(&parking_semaphore);
    pthread_mutex_lock(&log_mutex);
    print_timestamp();
    printf("Car %d: Leaving parking lot\n", id);
    pthread_mutex_unlock(&log_mutex);
}