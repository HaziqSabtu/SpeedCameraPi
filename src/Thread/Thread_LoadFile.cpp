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

#include <Event/Event.hpp>
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
LoadFileThread::LoadFileThread(wxEvtHandler *parent, DataPtr data,
                               std::string path)
    : BaseThread(parent, data), PreviewableThread(), path(path) {}

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
        wxCommandEvent startLoadEvent(c_LOAD_IMAGE_EVENT, LOAD_START_FILE);
        wxPostEvent(parent, startLoadEvent);

        if (!data->isCaptureDataEmpty()) {
            throw std::runtime_error("Capture data is not empty");
        }

        Utils::FileReadWrite().ReadFile(data, path);
        auto captureData = data->getCaptureData();

        for (int i = 0; i < captureData.size(); i++) {
            cv::Mat frame = captureData.at(i).image;
            UpdatePreviewEvent::Submit(parent, frame);
            wxMilliSleep(200);
        }

    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
        wxCommandEvent errorLoadEvent(c_LOAD_IMAGE_EVENT, LOAD_ERROR_FILE);
        wxPostEvent(parent, errorLoadEvent);

        return 0;
    }

    wxCommandEvent stopLoadEvent(c_LOAD_IMAGE_EVENT, LOAD_END_FILE);
    wxPostEvent(parent, stopLoadEvent);
    return 0;
}

/**
 * @brief Get the Thread Id object
 *
 * @return ThreadID
 */
ThreadID LoadFileThread::getID() const { return id; }

// unique_ptr is a smart pointer that guarantees deletion of the object it
// points to, either on destruction of the unique_ptr or via an explicit
// reset(). It is a move-only type - it cannot be copied, only moved. It is
// typically used to transfer ownership of a dynamically allocated object
// (i.e. heap allocated) out of a function that returns a unique_ptr by
// value.
//