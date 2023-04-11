/**
 * @file Thread_Capture.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom wxThread for capturing image from camera
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CAPTURE_THREAD_HPP
#define CAPTURE_THREAD_HPP

#include <Event/Event_UpdateImage.hpp>
#include <Utils/Camera/CameraBase.hpp>
#include <Utils/DataStruct.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <wx/thread.h>

/**
 * @brief Custom wxThread for capturing image from camera
 *
 */
class CaptureThread : public wxThread {
      public:
        CaptureThread(wxEvtHandler *parent, CameraBase *cap);
        ~CaptureThread();

      protected:
        virtual ExitCode Entry();

      private:
        wxEvtHandler *m_parent;
        CameraBase *m_cap;
};

#endif