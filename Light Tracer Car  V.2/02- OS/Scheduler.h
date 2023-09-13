/*
 * Scheduler.h
 *
 *  Created on: Sep 10, 2023
 *      Author: eme
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "std_types.h"

#define NUM_OF_TASKS 3

void Task1(void);
void Task2(void);
void Task3(void);
void Task4(void);
void create_task (void (*TaskFunction)(), uint32 ms_periodicity );
void tasks_scheduler(void);
void Systick_Handler (void);
void sheduler_init(void);

typedef struct {
    uint32 Periodicity;
    void (*TaskFunction)(void);
}Task_TCB;


Task_TCB TASKS[NUM_OF_TASKS];

#endif /* SCHEDULER_H_ */
