#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

class ThreadPool {
  public:
    ThreadPool(int numThreads) : m_numThreads(numThreads), m_stop(false) {
        wxLogMessage("Creating %d threads for ThreadPool", m_numThreads);
        for (int i = 0; i < m_numThreads; i++) {
            m_threads.push_back(std::thread(&ThreadPool::WorkerThread, this));
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_stop = true;
        }
        m_condition.notify_all();
        for (auto &thread : m_threads) {
            thread.join();
        }
    }

    void AddTask(Task *task) {
        wxLogMessage("Adding task to ThreadPool");
        std::unique_lock<std::mutex> lock(m_mutex);
        m_tasks.push(task);
        m_condition.notify_one();
    }

  private:
    void WorkerThread() {
        while (true) {
            Task *task = NULL;
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                m_condition.wait(lock,
                                 [this] { return m_stop || !m_tasks.empty(); });
                if (m_stop && m_tasks.empty()) {
                    return;
                }
                task = m_tasks.front();
                m_tasks.pop();
            }

            task->Execute();
            delete task;
        }
    }

    int m_numThreads;
    std::vector<std::thread> m_threads;
    std::queue<Task *> m_tasks;
    std::mutex m_mutex;
    std::condition_variable m_condition;
    bool m_stop;
};

#endif