#include <UI/Button/Button_Capture.hpp>

ButtonCapture::ButtonCapture(wxWindow *parent, wxWindowID id,
                             cv::VideoCapture *camera)
    : ButtonWState(parent, id, "Capture", "Capture", "Capturing", false),
      camera(camera), captureThread(nullptr) {
    Bind(wxEVT_BUTTON, &ButtonCapture::OnButton, this);
}

ButtonCapture::~ButtonCapture() { clearPointer(); }

void ButtonCapture::OnButton(wxCommandEvent &e) {
    state ? stopCapture() : startCapture();
    toggleState();
    e.Skip();
}

void ButtonCapture::render() {
    // state ? Enable() : Disable();
    ButtonWState::render();
}

void ButtonCapture::startCapture() {
    clearPointer();
    captureThread = new CaptureThread(this, camera);
    captureThread->Create();
    captureThread->Run();
}

void ButtonCapture::stopCapture() { clearPointer(); }

void ButtonCapture::clearPointer() {
    if (captureThread != nullptr) {
        captureThread->Delete();
        captureThread->Wait();
        delete captureThread;
        captureThread = nullptr;
    }
}