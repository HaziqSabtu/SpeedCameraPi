/**
 * @file ThreadPool.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Class Implementation for Background Thread Pool
 * @version 1.0.0
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Thread/ThreadPool.hpp>

ThreadPool::ThreadPool() : isStop(false) {}

/**
 * @brief Construct a new Thread Pool:: Thread Pool object
 *
 * @param numThreads number of threads/workers to create
 */
ThreadPool::ThreadPool(const int numThreads) : ThreadPool() {
    setNumThreads(numThreads);
}

/**
 * @brief Destroy the Thread Pool:: Thread Pool object
 * @details This will stop all threads and wait for them to finish
 *       before destroying the object
 */
ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        isStop = true;
    }
    cv.notify_all();
    for (auto& thread : threadArray) {
        thread.join();
    }
}

void ThreadPool::setNumThreads(const int numThreads) {
    this->numThreads = numThreads;
    std::cout << "Creating " << numThreads << " threads for ThreadPool"
              << std::endl;
    for (int i = 0; i < numThreads; i++) {
        threadArray.push_back(
          std::thread(&ThreadPool::WorkerThread, this, i));
        taskMap[i] = TaskProperty(TASK_NONE);
    }
}

/**
 * @brief Add Task to the queue
 *
 * @param task pointer to Task object
 */
void ThreadPool::AddTask(std::unique_ptr<Task> task) {
    std::unique_lock<std::mutex> lock(m_mutex);
    taskQueue.push_back(std::move(task));
    cv.notify_one();
}

/**
 * @brief Add Task to the front of the queue
 *
 * @param task pointer to Task object
 */
void ThreadPool::AddTaskFront(std::unique_ptr<Task> task) {
    std::unique_lock<std::mutex> lock(m_mutex);
    taskQueue.push_front(std::move(task));
    cv.notify_one();
}

/**
 * @brief Thread Worker
 * @details This method will be called automatically during thread creation
 * <ul>
 * <li> 1. The worker thread will run in an infinite loop
 * <li> 2. cv.wait() will block the thread until the condition variable is
 * notified <li> 3. The condition variable will be notified when a new task
 * is added to the queue <li> 4. The worker thread will then pop the task
 * from the queue and execute it <li> 5. Finished task will be deleted
 * </ul>
 *
 * @param threadId thread id
 */
void ThreadPool::WorkerThread(int threadId) {
    while (true) {
        std::unique_ptr<Task> task = nullptr;
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            cv.wait(lock, [this] { return isStop || !taskQueue.empty(); });
            if (isStop && taskQueue.empty()) {
                return;
            }

            task = std::move(taskQueue.front());
            taskQueue.pop_front();
            taskMap[threadId] = task->GetProperty();
        }
        task->Execute();
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            taskMap[threadId] = TASK_NONE;
        }
    }
}

/**
 * @brief Check if the thread pool is busy
 *
 * @return true if there are tasks in the queue or any worker is busy
 * @return false if there are no tasks in the queue and no worker is busy
 */
bool ThreadPool::isBusy() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return !taskQueue.empty() && isWorkerBusy();
}

/**
 * @brief Check if any worker is busy
 *
 * @return true if any worker is busy
 * @return false if all workers are idle
 */
bool ThreadPool::isWorkerBusy() {
    std::unique_lock<std::mutex> lock(m_mutex);
    for (auto& task : taskMap) {
        if (task.second.isTypeNone()) {
            continue;
        }
        return true;
    }
    return false;
}

/**
 * @brief Check if a worker is busy with a specific task
 *
 * @param property task property which is used to identify the task
 * @return true if the worker is busy with the specified task
 * @return false if the worker is not busy with the specified task
 */
bool ThreadPool::isWorkerBusy(TaskProperty& property) {
    std::unique_lock<std::mutex> lock(m_mutex);
    for (auto& task : taskMap) {

        TaskProperty p = task.second;

        if (p.isTypeNone()) {
            continue;
        }

        if (p == property) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Check if any worker is busy with a list of tasks
 *
 * @param properties list of task properties
 * @return true if any worker is busy with a task in the list
 * @return false if all workers are idle
 */
bool ThreadPool::isWorkerBusy(std::vector<TaskProperty>& properties) {
    for (auto property : properties) {
        if (isWorkerBusy(property)) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Check if the task queue is empty
 *
 * @return true if the task queue is empty
 * @return false if the task queue is not empty
 */
bool ThreadPool::isQueueEmpty() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return taskQueue.empty();
}

/**
 * @brief Check if the task queue has a task of a specific type
 *
 * @param type task type from TaskType enum
 * @return true if the task queue has a task of the specified type
 * @return false if the task queue does not have a task of the specified
 * type
 */
bool ThreadPool::HasTasks(TaskProperty& property) {
    std::unique_lock<std::mutex> lock(m_mutex);
    for (auto& task : taskQueue) {
        if (task->GetProperty() == property) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Check if the task queue has a task of a specific type
 *
 * @param properties list of task properties
 * @return true if the task queue has a task of the specified type
 * @return false if the task queue does not have a task of the specified
 * type
 */
bool ThreadPool::HasTasks(std::vector<TaskProperty>& properties) {
    std::unique_lock<std::mutex> lock(m_mutex);
    for (auto& task : taskQueue) {
        for (auto& property : properties) {
            if (task->GetProperty() == property) {
                return true;
            }
        }
    }
    return false;
}

/*
 * Curly Braces in Mutex, Why?
 * -> to define a block of code that should be executed with the lock held
 * -> ensure the lock automatically released when the block is finished
 * -> important to prevent deadlocks
 */

/*
 * Const on Methods
 * -> the method does not modify the state of the object it is called on
 * -> only inspect or retrieve information about the object's state.
 */