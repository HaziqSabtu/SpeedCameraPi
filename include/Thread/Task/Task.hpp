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

#include <Utils/IDGenerator/IDGenerator.hpp>
#include <string>

/**
 * @brief Enum for TaskType
 *
 */
enum TaskType {
    TASK_NONE,
    TASK_CAPTURE,
    TASK_LOAD,
    TASK_SIFT,
    TASK_HOUGHLINE,
    TASK_FLOW,
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

struct TaskProperty {
    TaskType type;
    int id;

    TaskProperty(TaskType type) {
        this->type = type;
        this->id = Utils::IDGenerator::GenerateID();
    }

    bool operator==(const TaskProperty &other) const {
        return (this->type == other.type && this->id == other.id);
    }
};

/**
 * @brief Interface Class for TaskPool Task
 *
 */
class Task {
  public:
    virtual ~Task() {}
    virtual void Execute() = 0;
    virtual TaskProperty GetProperty() const = 0;
    virtual std::string GetName() const = 0;
};

#endif