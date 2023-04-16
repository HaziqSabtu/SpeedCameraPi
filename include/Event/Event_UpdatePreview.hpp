
#pragma once

#include <Utils/wxUtils.hpp>
#include <opencv2/core/mat.hpp>
#include <wx/bitmap.h>
#include <wx/event.h>

class UpdatePreviewEvent;
wxDECLARE_EVENT(c_UPDATE_PREVIEW_EVENT, UpdatePreviewEvent);

enum UPDATE_PREVIEW_TYPE { UPDATE_PREVIEW = 1, CLEAR_PREVIEW };

class UpdatePreviewEvent : public wxCommandEvent {
  public:
    UpdatePreviewEvent(wxEventType eventType = c_UPDATE_PREVIEW_EVENT,
                       int id = 1);
    UpdatePreviewEvent(const UpdatePreviewEvent& e);
    virtual wxEvent* Clone() const;

    // Define a method to set the image data
    void SetImage(const wxBitmap& image);
    void SetImage(const cv::Mat& cvImage);

    // Define a method to get the image data
    wxBitmap GetImage() const;

  private:
    wxBitmap image;
};

typedef void (wxEvtHandler::*UpdatePreviewFunction)(UpdatePreviewEvent&);
#define UpdatePreviewHandler(func)                                        \
    wxEVENT_HANDLER_CAST(UpdatePreviewFunction, func)
#define EVT_UPDATE_PREVIEW(id, func)                                      \
    wx__DECLARE_EVT1(c_UPDATE_PREVIEW_EVENT,                              \
                     id,                                                  \
                     UpdatePreviewHandler(func))
