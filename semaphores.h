#ifndef SEMAPHORES_H
#define SEMAPHORES_H

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_CARS   10
#define NUM_SPACES  2

extern int available_spaces;
extern sem_t parking_semaphore;
extern double wait_times[NUM_CARS];
extern pthread_mutex_t log_mutex;
extern pthread_mutex_t stats_mutex;

void print_timestamp(void);
void car_arrive(int id);
void car_park(int id);
void car_leave(int id);
void parking(void);
void *cars(void *arg); 

#endif