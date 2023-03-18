/**
 * @file Thread_Result.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom wxThread for displaying result
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Thread/Thread_Result.hpp>

/**
 * @brief Construct a new Result Thread:: Result Thread object
 *
 * @param parent parent wxEvtHandler
 * @param imgData vector of ImageData
 */
ResultThread::ResultThread(wxEvtHandler *parent,
                           std::vector<ImageData> *imgData)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), imgData(imgData) {}

/**
 * @brief Destroy the Result Thread:: Result Thread object
 *
 */
ResultThread::~ResultThread() {}

/**
 * @brief Entry point of the thread
 * @details This function will be called when the thread is started. This loop
 * will display the result of the calculation
 *
 * <ul>
 * <li>Post UpdateImageEvent to parent wxEvtHandler</li>
 * <li>Wait for 500ms before posting the next event</li>
 * </ul>
 * @return wxThread::ExitCode
 */
wxThread::ExitCode ResultThread::Entry() {
    try {
        for (int i = 1; i < imgData->size(); i++) {
            UpdateImageEvent event(c_UPDATE_IMAGE_EVENT, UPDATE_IMAGE);
            event.SetImageData(imgData->at(i));
            wxPostEvent(parent, event);
            if (TestDestroy()) {
                break;
            }
            wxMilliSleep(500);
        }
    } catch (const std::exception &e) {
        std::cout << "ResultThread::Entry() - Error: \n"
                  << e.what() << std::endl;
    }
    return 0;
}