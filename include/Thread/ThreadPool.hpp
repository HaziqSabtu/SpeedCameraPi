#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <Thread/Task.hpp>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <wx/log.h>

class ThreadPool {
  public:
    ThreadPool(int numThreads);
    ~ThreadPool();

    void AddTask(Task *task);

  private:
    void WorkerThread();

    int numThreads;
    bool isStop;

    std::vector<std::thread> threadArray;
    std::queue<Task *> taskQueue;
    std::mutex m_mutex;
    std::condition_variable cv;
};

#endif