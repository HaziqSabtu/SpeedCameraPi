/**
 * @file Thread_Hough.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom wxThread for Hough Line Transform
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <Thread/Thread_Hough.hpp>

/**
 * @brief Construct a new HoughThread::HoughThread object
 *
 * @param parent parent wxEvtHandler/wxPanel
 * @param pool pointer to ThreadPool object
 * @param imgData pointer to ImageData object
 * @param cannyConfig CannyConfig
 * @param houghConfig HoughConfig
 */
HoughThread::HoughThread(wxEvtHandler *parent, ThreadPool *pool,
                         ImageData &imgData, CannyConfig cannyConfig,
                         HoughConfig houghConfig)
    : wxThread(wxTHREAD_JOINABLE), m_parent(parent), imgData(imgData),
      pool(pool), cannyConfig(cannyConfig), houghConfig(houghConfig) {}

/**
 * @brief Destroy the Hough Thread:: Hough Thread object
 *
 */
HoughThread::~HoughThread() {}

/**
 * @brief Entry point for the thread
 * @details  This function will be called when the thread is started
 * <ul>
 * <li>Post HoughEvent to signal that Hough Transform is started</li>
 * <li>Create HoughTask and add it to the ThreadPool</li>
 * <li>Wait for the task to finish</li>
 * <li>Post HoughEvent to signal that Hough Transform is finished</li>
 * </ul>
 *
 * @return wxThread::ExitCode
 */
wxThread::ExitCode HoughThread::Entry() {
    HoughEvent startHoughEvent(c_HOUGH_EVENT, HOUGH_START);
    wxPostEvent(m_parent, startHoughEvent);

    Detection::HoughData *houghData = new Detection::HoughData();
    Task *task = new HoughTask(imgData, houghData, cannyConfig, houghConfig);
    TaskProperty prop = task->GetProperty();
    pool->AddTaskFront(task);
    while (pool->isWorkerBusy(prop) || pool->HasTasks(prop)) {
        wxMilliSleep(30);
    }
    HoughEvent endHoughEvent(c_HOUGH_EVENT, HOUGH_END);
    endHoughEvent.SetHoughData(houghData);
    wxPostEvent(m_parent, endHoughEvent);
    task = NULL;
    houghData = NULL;
    return 0;
}