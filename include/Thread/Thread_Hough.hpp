/**
 * @file Thread_Hough.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom wxThread for Hough Line Transform
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef HOUGH_THREAD_HPP
#define HOUGH_THREAD_HPP

#include <Event/Event_Hough.hpp>
#include <Thread/Task/Task_HoughLine.hpp>
#include <Thread/ThreadPool.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/Struct/D_Hough.hpp>
#include <memory>
#include <opencv2/opencv.hpp>
#include <string>
#include <wx/thread.h>

class HoughThread : public wxThread {
  public:
    HoughThread(wxEvtHandler *parent, ThreadPool *pool, ImageData &imgData,
                CannyConfig cannyConfig, HoughConfig houghConfig);
    ~HoughThread();

  protected:
    ExitCode Entry();

  private:
    wxEvtHandler *m_parent;
    ThreadPool *pool;
    ImageData &imgData;
    CannyConfig cannyConfig;
    HoughConfig houghConfig;
};

#endif