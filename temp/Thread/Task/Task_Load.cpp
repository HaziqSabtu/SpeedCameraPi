/**
 * @file Task_Load.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Task Implementation for Loading H264 to ImageData
 * @version 1.0.0
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */

/**
 * @brief Construct a new Load Task:: Load Task object
 *
 * @param imgData pointer to vector of ImageData
 * @param path path to file
 * @param maxCapture maximum number of capture to load
 */
LoadTask::LoadTask(std::shared_ptr<std::vector<ImageData>> imgData,
                   std::string path)
    : property(TaskType::TASK_LOAD), imgData(imgData), path(path) {}

/**
 * @brief Execute Load Task
 * @details This method will be called automatically by the thread worker
 * <ul>
 * <li> 1. Check file extension
 * <li> 2. Load file
 * </ul>
 */
void LoadTask::Execute() {
    Utils::FileExtension ext = Utils::GetFileExtension(path);

    switch (ext) {
        case Utils::FileExtension::H264:
            FILEH264::ReadFile(path, imgData);
            break;
        case Utils::FileExtension::BIN: FILEWR::ReadFile(path, imgData); break;
        default: throw std::runtime_error("File extension not supported");
    }
}

/**
 * @brief Get the Type object
 *
 * @return TaskType
 */
TaskProperty LoadTask::GetProperty() const { return property; }

/**
 * @brief Get the Name object
 *
 * @return std::string
 */
std::string LoadTask::GetName() const { return "LoadTask"; }