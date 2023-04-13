/**
 * @file Thread_LoadFile.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom wxThread for loading ImageData from file
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Thread/Thread_LoadFile.hpp>

/**
 * @brief Construct a new Load File Thread:: Load File Thread object
 *
 * @param parent parent wxEvtHandler
 * @param threadPool pointer to ThreadPool
 * @param imgData pointer to ImageData vector
 * @param path path to file
 * @param maxFrame maximum number of frame to load
 */
LoadFileThread::LoadFileThread(
  wxEvtHandler* parent,
  std::shared_ptr<ThreadPool> threadPool,
  std::shared_ptr<std::vector<ImageData>> imgData,
  wxString path,
  const int maxFrame)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), pool(threadPool),
      imgData(imgData), path(path), maxFrame(maxFrame) {}

/**
 * @brief Destroy the Load File Thread:: Load File Thread object
 *
 */
LoadFileThread::~LoadFileThread() {
    if (parent != nullptr) {
        parent = nullptr;
    }
}

/**
 * @brief Entry point of the thread
 * @details This function will be called when the thread is started
 * <ul>
 * <li>LoadTask is created and added to the thread pool</li>
 * <li>Wait for the thread pool to finish loading the file</li>
 * </ul>
 *
 *
 * @return wxThread::ExitCode
 */
wxThread::ExitCode LoadFileThread::Entry() {
    try {
        CaptureImageEvent startCaptureEvent(c_CAPTURE_IMAGE_EVENT,
                                            CAPTURE_START);
        wxPostEvent(parent, startCaptureEvent);

        std::string stringPath = Utils::wxStringToString(this->path);

        std::unique_ptr<Task> task =
          std::make_unique<LoadTask>(imgData, stringPath);

        TaskProperty property = task->GetProperty();
        pool->AddTask(task);

        while (imgData->empty()) {
            wxMilliSleep(30);
        }

        cv::Mat frame = imgData->at(0).image;
        UpdateImageEvent event(c_UPDATE_IMAGE_EVENT, UPDATE_IMAGE);
        event.SetImageData(frame);
        wxPostEvent(parent, event);

        while (pool->isWorkerBusy(property) || pool->HasTasks(property)) {
            wxMilliSleep(30);
        }

        if (maxFrame < imgData->size() && maxFrame != -1) {
            imgData->erase(imgData->begin() + maxFrame, imgData->end());
        }

        for (int i = 1; i < imgData->size(); i++) {
            cv::Mat frame = imgData->at(i).image;
            UpdateImageEvent updateImageEvent(c_UPDATE_IMAGE_EVENT,
                                              UPDATE_IMAGE);
            updateImageEvent.SetImageData(frame);
            wxPostEvent(parent, updateImageEvent);
            wxMilliSleep(100);
        }
    } catch (const std::exception& e) {
        std::cout << "LoadFileThread::Entry() - Error: \n"
                  << e.what() << std::endl;
    }

    cv::Mat first = imgData->at(0).image;
    UpdateImageEvent updateImageEvent(c_UPDATE_IMAGE_EVENT, UPDATE_IMAGE);
    updateImageEvent.SetImageData(first);
    wxPostEvent(parent, updateImageEvent);

    CaptureImageEvent stopCaptureEvent(c_CAPTURE_IMAGE_EVENT, CAPTURE_END);
    // stopCaptureEvent.SetImageData(imgData.release());
    wxPostEvent(parent, stopCaptureEvent);
    return 0;
}

// unique_ptr is a smart pointer that guarantees deletion of the object it
// points to, either on destruction of the unique_ptr or via an explicit
// reset(). It is a move-only type - it cannot be copied, only moved. It is
// typically used to transfer ownership of a dynamically allocated object
// (i.e. heap allocated) out of a function that returns a unique_ptr by
// value.
//