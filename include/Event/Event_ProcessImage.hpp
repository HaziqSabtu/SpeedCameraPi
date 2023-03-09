#ifndef PROCESS_IMAGE_EVENT_HPP
#define PROCESS_IMAGE_EVENT_HPP

#include <opencv2/opencv.hpp>
#include <string>
#include <wx/event.h>

class ProcessImageEvent;
wxDECLARE_EVENT(c_PROCESS_IMAGE_EVENT, ProcessImageEvent);

class ProcessImageEvent : public wxCommandEvent {
  public:
    ProcessImageEvent(wxEventType eventType = c_PROCESS_IMAGE_EVENT,
                      int id = 0);
    ProcessImageEvent(const ProcessImageEvent &e);
    virtual wxEvent *Clone() const;

    // Define a method to set the image data
    void SetImageData(const cv::Mat &image);

    // Define a method to get the image data
    cv::Mat GetImageData() const;

  private:
    cv::Mat m_imageData;
};

typedef void (wxEvtHandler::*ProcessImageFunction)(ProcessImageEvent &);
#define ProcessImageHandler(func)                                              \
    wxEVENT_HANDLER_CAST(ProcessImageFunction, func)
#define EVT_PROCESSIMAGE(id, func)                                             \
    wx__DECLARE_EVT1(c_PROCESS_IMAGE_EVENT, id, ProcessImageHandler(func))
#endif