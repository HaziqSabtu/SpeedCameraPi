
#include "Thread/Thread_RoiPreview.hpp"
#include "Event/Event_Error.hpp"
#include "Utils/ImageUtils.hpp"
#include <Thread/Thread_RoiPreview.hpp>
#include <memory>
#include <opencv2/core/types.hpp>
#include <wx/utils.h>

RoiPreviewThread::RoiPreviewThread(wxEvtHandler *parent, DataPtr data)
    : wxThread(wxTHREAD_JOINABLE), data(data) {
    this->parent = parent;

    auto config = AppConfig();
    auto previewConfig = config.GetPreviewConfig();
    int pWidth = previewConfig.width;
    int pHeight = previewConfig.height;
    this->pSize = cv::Size(pWidth, pHeight);

    auto cameraConfig = config.GetCameraConfig();
    int iWidth = cameraConfig.Camera_Width;
    int iHeight = cameraConfig.Camera_Height;
    this->imageSize = cv::Size(iWidth, iHeight);
}

RoiPreviewThread::~RoiPreviewThread() {}

wxThread::ExitCode RoiPreviewThread::Entry() {

    wxCommandEvent startCaptureEvent(c_CAPTURE_EVENT, CAPTURE_START);
    wxPostEvent(parent, startCaptureEvent);

    try {
        while (!TestDestroy()) {
            if (data->isCaptureDataEmpty()) {
                throw std::runtime_error("Capture data is empty");
            }

            auto firstData = data->getCaptureData().at(0);
            cv::Mat frame = firstData.image.clone();

            auto roiData = data->getRoiData();
            cv::Rect initRoi = roiData.roi;

            cv::resize(frame, frame, pSize);

            if (initRoi.area() > 0) {
                cv::Rect scaledRect =
                    Utils::scaleRect(initRoi, imageSize, pSize);
                cv::rectangle(frame, scaledRect, cv::Scalar(0, 255, 0), 2);
            }

            UpdatePreviewEvent::Submit(parent, frame);
            wxMilliSleep(500);
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

ThreadID RoiPreviewThread::getID() const { return id; }