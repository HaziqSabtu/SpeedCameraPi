/**
 * @file ThreadPool.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Class Implementation for Background Thread Pool
 * @version 1.0.0
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <Thread/Task/Task.hpp>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <wx/log.h>

class ThreadPool {
  public:
    ThreadPool(int numThreads);
    ~ThreadPool();

    void AddTask(Task *task);
    void AddTaskFront(Task *task);

    bool isBusy();
    bool HasTasks(TaskType type);
    bool isWorkerBusy();
    bool isQueueEmpty();

  private:
    void WorkerThread(int threadId);

    int numThreads;
    bool isStop;

    std::vector<std::thread> threadArray;
    std::vector<bool> threadStatus;
    std::deque<Task *> taskQueue;
    std::mutex m_mutex;
    std::condition_variable cv;
};

#endif