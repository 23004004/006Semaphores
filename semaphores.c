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

    pthread_mutex_lock(&stats_mutex);
    waiting[id] = id;
    waiting_count++;
    pthread_mutex_unlock(&stats_mutex);

    draw_dashboard();
    pthread_mutex_unlock(&log_mutex);
}

void car_park(int id) {
    time_t start = time(NULL);
    
    sem_wait(&parking_semaphore);

    pthread_mutex_lock(&stats_mutex);
    waiting[id] = -1;
    waiting_count--;
    pthread_mutex_unlock(&stats_mutex);

    double waited = difftime(time(NULL), start);
    wait_times[id] = waited;
    
    int duration = (rand() % 5) + 1;
    
    pthread_mutex_lock(&log_mutex); 
    print_timestamp();
    printf("Car %d: Parked successfully (waited %.2f seconds)\n", id, waited);
    for (int i = 0; i < NUM_SPACES; i++) {
        if (spaces[i] == -1) { spaces[i] = id; break; }
    }
    draw_dashboard();
    pthread_mutex_unlock(&log_mutex);

    sleep(duration);
}

void car_leave(int id) {
    sem_post(&parking_semaphore);
    pthread_mutex_lock(&log_mutex);
    print_timestamp();
    printf("Car %d: Leaving parking lot\n", id);
    for (int i = 0; i < NUM_SPACES; i++) {
        if (spaces[i] == id) { spaces[i] = -1; break; }
    }
    draw_dashboard();
    pthread_mutex_unlock(&log_mutex);
}

void draw_dashboard(void) {
    printf("  ║ Parking: ");
    for (int i = 0; i < NUM_SPACES; i++) {
        if (spaces[i] == -1)
            printf("[ %d: --- ] ", i + 1);
        else
            printf("[ %d: Car%-2d] ", i + 1, spaces[i]);
    }
    printf("║\n");

    printf("  ║ Arrived: ");
    if (waiting_count == 0) {
        printf("EMPTY");
    } else {
        for (int i = 0; i < NUM_CARS; i++) {
            if (waiting[i] != -1)
                printf("Car%d ", waiting[i]);
        }
    }
    printf("\n");
    printf("\n");
}