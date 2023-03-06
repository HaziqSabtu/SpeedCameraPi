/**
 * @file Task/Task.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Interface for TaskPool Task
 * @version 1.0.0
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef TASK_HPP
#define TASK_HPP

/**
 * @brief Enum for task type
 *
 */
enum TaskType {
    TASK_CAPTURE,
    TASK_LOAD,
    TASK_SIFT,
};

/**
 * @brief Interface for TaskPool Task
 *
 */
class Task {
  public:
    virtual ~Task() {}
    virtual void Execute() = 0;
    virtual TaskType GetType() const = 0;
};

#endif