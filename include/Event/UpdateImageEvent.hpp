#ifndef UPDATE_IMAGE_EVENT_HPP
#define UPDATE_IMAGE_EVENT_HPP

#include <opencv2/opencv.hpp>
#include <string>
#include <wx/event.h>

class SetImageEvent;
wxDECLARE_EVENT(SET_IMAGE_EVENT_TYPE, SetImageEvent);

class SetImageEvent : public wxCommandEvent {
  public:
    SetImageEvent(wxEventType eventType = SET_IMAGE_EVENT_TYPE, int id = 0);
    SetImageEvent(const SetImageEvent &e);
    virtual wxEvent *Clone() const;

    // Define a method to set the image data
    // void SetImageData(const cv::Mat &image);
    void SetImageData(const std::string &image);

    // Define a method to get the image data
    // cv::Mat GetImageData() const;
    std::string GetImageData() const;

  private:
    // cv::Mat m_imageData;
    std::string m_imageData;
};

typedef void (wxEvtHandler::*MyFooEventFunction)(SetImageEvent &);
#define MyFooEventHandler(func) wxEVENT_HANDLER_CAST(MyFooEventFunction, func)
#define EVT_MYFOO(id, func)                                                    \
    wx__DECLARE_EVT1(SET_IMAGE_EVENT_TYPE, id, MyFooEventHandler(func))
#endif