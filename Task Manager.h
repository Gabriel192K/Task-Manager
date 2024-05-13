#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__

/* Dpendencies */
#include <stdint.h>
#include <stdlib.h> // Include for malloc, calloc, realloc, and free
#include <string.h>
#include "../Time/Time.h"

class TaskManager
{
    public:
        TaskManager(void);
        ~TaskManager();
        const int8_t  begin      (const uint8_t tasksAmount);
        const uint8_t addTask    (void (*task)(void), const uint32_t interval);
        const int8_t  deleteTask (void (*task)(void));
        const int8_t  replaceTask(void (*toDelete)(void), void (*toAdd)(void));
        void          run        (void);
        const uint8_t end        (void);
    private:
        uint8_t began;
        struct Task
        {
            void (*task)(void);
            uint32_t interval;
            uint32_t nextExecutionTime;
        };
        Task* tasks;
        uint8_t tasksAmount;
        uint8_t taskIndex;
};

#endif
