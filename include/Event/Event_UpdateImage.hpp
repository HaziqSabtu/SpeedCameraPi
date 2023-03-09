#ifndef UPDATE_IMAGE_EVENT_HPP
#define UPDATE_IMAGE_EVENT_HPP

#include <opencv2/opencv.hpp>
#include <string>
#include <wx/event.h>

class UpdateImageEvent;
wxDECLARE_EVENT(c_UPDATE_IMAGE_EVENT, UpdateImageEvent);

enum UPDATE_IMAGE_TYPE { UPDATE_IMAGE = 1, CLEAR_IMAGE };

class UpdateImageEvent : public wxCommandEvent {
  public:
    UpdateImageEvent(wxEventType eventType = c_UPDATE_IMAGE_EVENT, int id = 1);
    UpdateImageEvent(const UpdateImageEvent &e);
    virtual wxEvent *Clone() const;

    // Define a method to set the image data
    void SetImageData(const cv::Mat &image);

    // Define a method to get the image data
    cv::Mat GetImageData() const;

  private:
    cv::Mat m_imageData;
};

typedef void (wxEvtHandler::*UpdateImageFunction)(UpdateImageEvent &);
#define UpdateImageHandler(func) wxEVENT_HANDLER_CAST(UpdateImageFunction, func)
#define EVT_UPDATEIMAGE(id, func)                                              \
    wx__DECLARE_EVT1(c_UPDATE_IMAGE_EVENT, id, UpdateImageHandler(func))
#endif