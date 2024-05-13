/*
 * Task Manager - Basic.cpp
 *
 * Created: 5/9/2024 10:41:51 AM
 * Author : rotes
 */ 

/* Dependencies */
#include "Task Manager/Task Manager.h"

/* Macros */
#define TASKS (const uint8_t)10

/* Objects */
TaskManager taskManager;

/* Prototypes */
void task1(void);
void task2(void);

int main(void)
{
	const int8_t rc = taskManager.begin(TASKS);
    taskManager.addTask(task1, 1000); // Add a task that will run every 1000 ms
    taskManager.addTask(task2, 2000); // Add a task that will run every 2000 ms
    // taskManager.deleteTask(task1); // Delete task
    // taskManager.deleteTask(task2); // Delete task
    while (1) 
    {
        taskManager.run();
    }
}

void task1(void)
{
    /* Run task 1 */
}

void task2(void)
{
    /* Run task 2 */
}

