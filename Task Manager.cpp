/* Dependencies */
#include "Task Manager.h"

TaskManager::TaskManager()
{
    this->taskIndex = 0;
    this->tasksAmount = 0;
}

TaskManager::~TaskManager()
{
    this->end();
}

/*!
 * @brief  Starting the task manager implementation
 * @param  taskAmount
 *         The amount of tasks to allocate memory for
 * @return Returns 0 if the implementation already began
 * @return Returns -1 if memory allocation failed
 * @return Returns 1 if began successfully
 */
const int8_t TaskManager::begin(const uint8_t tasksAmount)
{
    if (this->began)
        return (0);
    this->began = 1;
    Time.begin();
    this->tasksAmount = tasksAmount;
    this->tasks = (Task*)calloc(this->tasksAmount, sizeof(Task));
    if (this->tasks == NULL)
        return (-1);
    return (1);
}

/*!
 * @brief  Adding a task to the task manager
 * @param  task
 *         The callback to the task function
 * @param  interval
 *         The interval the task will trigger
 * @return Returns 0 if the task manager is full of tasks, otherwise 1
 */
const uint8_t TaskManager::addTask(void (*task)(void), const uint32_t interval)
{
    if (this->taskIndex >= this->tasksAmount) // Task array full
        return (0);
    const uint32_t currentTime = Time.milliseconds();
    this->tasks[this->taskIndex].task = task;
    this->tasks[this->taskIndex].interval = interval;
    this->tasks[this->taskIndex].nextExecutionTime = currentTime + interval;
    this->taskIndex++;
    return (1);
}

/*!
 * @brief  Adding a task to the task manager
 * @param  task
 *         The callback to the task function
 * @return Returns 0 if the task manager is full of tasks, otherwise 1
 */
const uint8_t TaskManager::addTask(void (*task)(void))
{
    return (this->addTask(task, (const uint32_t)0));
}

/*!
 * @brief  Deleting a task to the task manager
 * @param  task
 *         The callback to the task function
 * @return Returns 0 if the task manager is empty of tasks
 *         Returns 1 if the task was successfully found and deleted
 *         Returns -1 if the task was not found inside the task manager
 */
const int8_t TaskManager::deleteTask(void (*task)(void))
{
    if (!this->taskIndex) // Task array empty
        return (0);

    for (uint8_t i = 0; i < this->taskIndex; i++)
    {
        if (this->tasks[i].task != task)                 // Skip this task if it's not the one we want to delete
            continue;
        for (uint8_t j = i; j < this->taskIndex - 1; j++) // Found the task, remove it by shifting other tasks left
            this->tasks[j] = this->tasks[j + 1];
        this->taskIndex--;
        return (1);
    }
    return (-1);
}

/*!
 * @brief  Main running function of task manager
 */
void TaskManager::run(void)
{
    if (!this->taskIndex) // If no tasks do not bother and return
        return;

    const uint32_t currentTime = Time.milliseconds();
    for (uint8_t i = 0; i < this->taskIndex; i++)
    {
        if (currentTime < this->tasks[i].nextExecutionTime)
            continue;
        this->tasks[i].task();
        this->tasks[i].nextExecutionTime += this->tasks[i].interval;
    }
}

/*!
 * @brief  Ending the task manager implementation
 * @return Returns 0 if the implementation already ended, otherwise 1
 */
const uint8_t TaskManager::end(void)
{
    if (!this->began)
        return (0);
    this->began = 0;
    free(this->tasks);
    this->taskIndex = 0;
    this->tasksAmount = 0;
    return (1);
}
