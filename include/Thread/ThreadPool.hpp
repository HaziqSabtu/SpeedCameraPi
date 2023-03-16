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
#include <Utils/IDGenerator/IDGenerator.hpp>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>
#include <wx/log.h>

class ThreadPool {
  public:
    ThreadPool(const int numThreads);
    ~ThreadPool();

    void AddTask(Task *task);
    void AddTaskFront(Task *task);

    bool isBusy();
    bool HasTasks(TaskProperty property);
    bool HasTasks2(TaskProperty &property);
    bool isWorkerBusy();
    bool isWorkerBusy(TaskProperty property);
    bool isQueueEmpty();

  private:
    void WorkerThread(int threadId);

    int numThreads;
    bool isStop;

    std::vector<std::thread> threadArray;
    std::vector<bool> threadStatus;
    std::unordered_map<int, Task *> taskMap;
    std::deque<Task *> taskQueue;
    std::mutex m_mutex;
    std::condition_variable cv;
    // IDGenerator idGenerator;
};

#endif