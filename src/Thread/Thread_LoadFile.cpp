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
LoadFileThread::LoadFileThread(wxEvtHandler *parent,
                               std::shared_ptr<ThreadPool> threadPool,
                               std::shared_ptr<std::vector<ImageData>> imgData,
                               std::string path, const int maxFrame)
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
        wxCommandEvent startLoadEvent(c_LOAD_IMAGE_EVENT, LOAD_START);
        wxPostEvent(parent, startLoadEvent);

        if (imgData == nullptr) {
            throw std::runtime_error("imgData is null");
        }

        std::unique_ptr<Task> task = std::make_unique<LoadTask>(imgData, path);

        TaskProperty property = task->GetProperty();
        pool->AddTask(task);

        while (pool->isWorkerBusy(property) || pool->HasTasks(property)) {
            wxMilliSleep(30);
        }

        if (maxFrame < imgData->size() && maxFrame != -1) {
            imgData->erase(imgData->begin() + maxFrame, imgData->end());
        }

        for (int i = 0; i < imgData->size(); i++) {
            cv::Mat frame = imgData->at(i).image;
            UpdatePreviewEvent updatePreviewEvent(c_UPDATE_PREVIEW_EVENT,
                                                  UPDATE_PREVIEW);
            updatePreviewEvent.SetImage(frame);
            wxPostEvent(parent, updatePreviewEvent);
            wxMilliSleep(200);
        }
    } catch (const std::exception &e) {
        ErrorEvent errorEvent(c_ERROR_EVENT, wxID_ANY);
        errorEvent.SetErrorData(e.what());
        wxPostEvent(parent, errorEvent);
    }

    wxCommandEvent stopLoadEvent(c_LOAD_IMAGE_EVENT, LOAD_END_FILE);
    wxPostEvent(parent, stopLoadEvent);
    return 0;
}

// unique_ptr is a smart pointer that guarantees deletion of the object it
// points to, either on destruction of the unique_ptr or via an explicit
// reset(). It is a move-only type - it cannot be copied, only moved. It is
// typically used to transfer ownership of a dynamically allocated object
// (i.e. heap allocated) out of a function that returns a unique_ptr by
// value.
//