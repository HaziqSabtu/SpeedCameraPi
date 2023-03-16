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

/**
 * @brief Construct a new Thread Pool:: Thread Pool object
 *
 * @param numThreads number of threads/workers to create
 */
ThreadPool::ThreadPool(const int numThreads)
    : numThreads(numThreads), isStop(false) {
    wxLogMessage("Creating %d threads for ThreadPool", numThreads);
    for (int i = 0; i < numThreads; i++) {
        threadArray.push_back(std::thread(&ThreadPool::WorkerThread, this, i));
        taskMap[i] = NULL;
    }
    threadStatus.resize(numThreads, false);
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
    for (auto &thread : threadArray) {
        thread.join();
    }
}

/**
 * @brief Add Task to the queue
 *
 * @param task pointer to Task object
 */
void ThreadPool::AddTask(Task *task) {
    std::unique_lock<std::mutex> lock(m_mutex);
    taskQueue.push_back(task);
    cv.notify_one();
}

void ThreadPool::AddTaskFront(Task *task) {
    std::cout << "Adding task to front" << std::endl;
    std::unique_lock<std::mutex> lock(m_mutex);
    taskQueue.push_front(task);
    for (auto &task : taskQueue) {
        std::cout << task->GetName() << std::endl;
    }
    cv.notify_one();
}

/**
 * @brief Thread Worker
 * @details This method will be called automatically during thread creation
 *
 * @param threadId thread id
 */
void ThreadPool::WorkerThread(int threadId) {
    while (true) {
        Task *task = NULL;
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            cv.wait(lock, [this] { return isStop || !taskQueue.empty(); });
            if (isStop && taskQueue.empty()) {
                return;
            }

            task = taskQueue.front();
            taskQueue.pop_front();
            threadStatus[threadId] = true;
            taskMap[threadId] = task;
        }
        // std::cout << "Worker " << threadId
        //   << " executing task: " << task->GetName() << std::endl;
        task->Execute();
        // std::cout << "Worker " << threadId
        //           << " finished task: " << task->GetName() << std::endl;
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            delete task;
            threadStatus[threadId] = false;
            taskMap[threadId] = NULL;
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
    for (bool status : threadStatus) {
        if (status) {
            return true;
        }
    }
    return false;
}

bool ThreadPool::isWorkerBusy(TaskProperty property) {
    // std::cout << "Checking if worker is busy" << std::endl;
    std::unique_lock<std::mutex> lock(m_mutex);
    for (auto &task : taskMap) {
        if (task.second != NULL && task.second->GetProperty() == property) {
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
 * @return false if the task queue does not have a task of the specified type
 */
bool ThreadPool::HasTasks(TaskProperty property) {
    // std::cout << "Checking if task queue has tasks" << std::endl;
    std::unique_lock<std::mutex> lock(m_mutex);
    for (auto &task : taskQueue) {
        if (task->GetProperty() == property) {
            return true;
        }
    }
    return false;
}

bool ThreadPool::HasTasks2(TaskProperty &property) {
    // std::cout << "Checking if task queue has tasks2" << std::endl;
    std::unique_lock<std::mutex> lock(m_mutex);
    for (auto &task : taskQueue) {
        if (task->GetProperty() == property) {
            return true;
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