#ifndef SEMAPHORES_H
#define SEMAPHORES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_CARS   10
#define NUM_SPACES  1

extern int available_spaces;

void print_timestamp(void);
void car_arrive(int id);
void car_park(int id);
void car_leave(int id);
void parking(void);
void *cars(void *arg); 

#endif