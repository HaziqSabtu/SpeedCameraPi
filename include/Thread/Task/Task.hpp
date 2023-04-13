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
 * @details Used to determine the type of the Task
 * <ul>
 * <li>TASK_NONE: No Task</li>
 * <li>TASK_CAPTURE: CaptureTask</li>
 * <li>TASK_LOAD: LoadTask</li>
 * <li>TASK_SIFT: SiftTask</li>
 * <li>TASK_HOUGHLINE: HoughTask</li>
 * <li>TASK_FLOW: FlowTask</li>
 * <li>TASK_SPEED: SpeedTask</li>
 * </ul>
 */
enum TaskType {
    TASK_NONE,
    TASK_CAPTURE,
    TASK_LOAD,
    TASK_SIFT,
    TASK_HOUGHLINE,
    TASK_FLOW,
    TASK_SPEED,
};

/**
 * @brief Enum for TaskPriority
 * @details Used to determine the priority of the Task
 * <ul>
 * <li>TASK_PRIORITY_LOW: Lowest priority</li>
 * <li>TASK_PRIORITY_NORMAL: Normal priority</li>
 * <li>TASK_PRIORITY_HIGH: Highest priority</li>
 * </ul>
 *
 */
enum TaskPriority {
    TASK_PRIORITY_LOW = 0,
    TASK_PRIORITY_NORMAL = 1,
    TASK_PRIORITY_HIGH = 2,
};

/**
 * @brief Struct for TaskProperty
 * @details Used to identify Task in ThreadPool
 *
 */
struct TaskProperty {
    TaskType type;
    int id;

    TaskProperty() : TaskProperty(TASK_NONE) {}

    /**
     * @brief Construct a new Task Property object
     *
     * @param type TaskType to be created
     */
    TaskProperty(TaskType type) {
        this->type = type;
        this->id = Utils::IDGenerator::GenerateID();
    }

    /**
     * @brief Compare TaskProperty with other TaskProperty
     *
     * @param other TaskProperty to be compared with
     * @return true true if both TaskProperty are equal in TaskType and ID
     * @return false false if both TaskProperty are not equal in either
     * TaskType or ID
     */
    bool operator==(const TaskProperty& other) const {
        return (this->type == other.type && this->id == other.id);
    }

    bool isTypeNone() const { return (this->type == TASK_NONE); }
};

/**
 * @brief Interface Class for TaskPool Task
 *
 */
class Task {
  public:
    /**
     * @brief Destroy the Task object
     *
     */
    virtual ~Task() {}

    /**
     * @brief Execute the Task
     * @details Implementations required to override this method
     *
     */
    virtual void Execute() = 0;

    /**
     * @brief Get the Property object
     *
     * @return TaskProperty
     */
    virtual TaskProperty GetProperty() const = 0;

    /**
     * @brief Get the Priority object
     *
     * @return TaskPriority
     */
    virtual std::string GetName() const = 0;
};

#endif