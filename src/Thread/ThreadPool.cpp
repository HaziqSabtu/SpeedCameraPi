#include <Thread/ThreadPool.hpp>

ThreadPool::ThreadPool(int numThreads) : numThreads(numThreads), isStop(false) {
    wxLogMessage("Creating %d threads for ThreadPool", numThreads);
    for (int i = 0; i < numThreads; i++) {
        threadArray.push_back(std::thread(&ThreadPool::WorkerThread, this));
    }
}

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

void ThreadPool::AddTask(Task *task) {
    std::unique_lock<std::mutex> lock(m_mutex);
    taskQueue.push(task);
    cv.notify_one();
}

void ThreadPool::WorkerThread() {
    while (true) {
        Task *task = NULL;
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            cv.wait(lock, [this] { return isStop || !taskQueue.empty(); });
            if (isStop && taskQueue.empty()) {
                return;
            }
            task = taskQueue.front();
            taskQueue.pop();
        }
        task->Execute();
        delete task;
    }
}

bool ThreadPool::HasTasks() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return !taskQueue.empty();
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