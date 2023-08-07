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
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>
#include <wx/log.h>

#define POOLPtr std::shared_ptr<ThreadPool>

/**
 * @brief Class Implementation for Background Thread Pool
 *
 */
class ThreadPool {
  public:
    ThreadPool();
    ThreadPool(const int numThreads);
    ~ThreadPool();

    void setNumThreads(const int numThreads);

    void AddTask(std::unique_ptr<Task> &task);
    void AddTaskFront(std::unique_ptr<Task> task);

    bool isBusy();
    bool HasTasks(TaskProperty &property);
    bool HasTasks(std::vector<TaskProperty> &properties);

    bool isWorkerBusy();
    bool isWorkerBusy(TaskProperty &property);
    bool isWorkerBusy(std::vector<TaskProperty> &properties);
    bool isQueueEmpty();

    int countTasks(std::vector<TaskProperty> &properties);

  private:
    void WorkerThread(int threadId);

    int numThreads;
    bool isStop;

    std::vector<std::thread> threadArray;
    std::unordered_map<int, TaskProperty> taskMap;
    std::deque<std::unique_ptr<Task>> taskQueue;
    std::mutex m_mutex;
    std::condition_variable cv;
};

#endif