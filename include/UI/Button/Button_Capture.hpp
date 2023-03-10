#ifndef BUTTON_CAPTURE_HPP
#define BUTTON_CAPTURE_HPP

#include <Thread/Thread_Capture.hpp>
#include <UI/Button/Button_wState.hpp>
#include <opencv2/opencv.hpp>

class ButtonCapture : public ButtonWState {
  public:
    ButtonCapture(wxWindow *parent, wxWindowID id, cv::VideoCapture *camera);
    ~ButtonCapture();

  private:
    void OnButton(wxCommandEvent &e) override;

    void startCapture();
    void stopCapture();
    void clearPointer();

    void render() override;
    cv::VideoCapture *camera;
    CaptureThread *captureThread;
};

#endif