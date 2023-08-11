
#include "Event/Event_Error.hpp"
#include <Thread/Thread_CalibPreviewCapture.hpp>
#include <memory>
#include <opencv2/core/types.hpp>

CalibCapturePreviewThread::CalibCapturePreviewThread(wxEvtHandler *parent,
                                                     DataPtr data)
    : wxThread(wxTHREAD_JOINABLE), data(data) {
    this->parent = parent;

    AppConfig config;
    auto previewConfig = config.GetPreviewConfig();
    int pWidth = previewConfig.width;
    int pHeight = previewConfig.height;
    this->pSize = cv::Size(pWidth, pHeight);

    if (data->isCaptureDataEmpty()) {
        throw std::runtime_error("Capture data is empty");
    }

    auto captureData = data->getCaptureData();
    auto firstData = captureData.front();
    int iWidth = firstData.image.cols;
    int iHeight = firstData.image.rows;
    this->imageSize = cv::Size(iWidth, iHeight);
}

CalibCapturePreviewThread::~CalibCapturePreviewThread() {}

// TODO: do only one loop
wxThread::ExitCode CalibCapturePreviewThread::Entry() {

    wxCommandEvent startCaptureEvent(c_CAPTURE_EVENT, CAPTURE_START);
    wxPostEvent(parent, startCaptureEvent);

    try {
        cv::Mat firstFrame;
        auto captureData = data->getCaptureData();
        auto firstData = captureData.front();
        firstFrame = firstData.image.clone();

        if (firstFrame.empty()) {
            throw std::runtime_error("Frame is empty");
        }

        cv::resize(firstFrame, firstFrame, pSize);

        while (!TestDestroy()) {

            cv::Mat prevFrame = firstFrame.clone();

            auto isLineNull = data->isCalibDataEmpty();
            if (!isLineNull) {
                auto calibData = data->getCalibData();
                cv::Scalar yellow(0, 255, 255);
                cv::Scalar blue(255, 0, 0);

                Detection::Line left = calibData.lineLeft;
                Detection::Line right = calibData.lineRight;

                left = left.Scale(imageSize, pSize);
                right = right.Scale(imageSize, pSize);

                cv::line(prevFrame, left.p1, left.p2, yellow, 2);
                cv::line(prevFrame, right.p1, right.p2, blue, 2);
            }

            UpdatePreviewEvent::Submit(parent, prevFrame);
        }
    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }

    UpdatePreviewEvent clearPreviewEvent(c_UPDATE_PREVIEW_EVENT, CLEAR_PREVIEW);
    wxPostEvent(parent, clearPreviewEvent);

    wxCommandEvent endCaptureEvent(c_CAPTURE_EVENT, CAPTURE_END);
    wxPostEvent(parent, endCaptureEvent);

    return 0;
}

ThreadID CalibCapturePreviewThread::getID() const { return id; }