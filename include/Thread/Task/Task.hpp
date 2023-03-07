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

#include <string>

/**
 * @brief Enum for TaskType
 *
 */
enum TaskType {
    TASK_TYPE_NONE,
    TASK_CAPTURE,
    TASK_LOAD,
    TASK_SIFT,
    TASK_HOUGHLINE,
};

/**
 * @brief Enum for TaskPriority
 *
 */
enum TaskPriority {
    TASK_PRIORITY_LOW = 0,
    TASK_PRIORITY_NORMAL = 1,
    TASK_PRIORITY_HIGH = 2,
};

/**
 * @brief Interface Class for TaskPool Task
 *
 */
class Task {
  public:
    virtual ~Task() {}
    virtual void Execute() = 0;
    virtual TaskType GetType() const = 0;
    virtual std::string GetName() const = 0;
};

#endif