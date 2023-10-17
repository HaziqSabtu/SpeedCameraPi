
#include "Event/Event.hpp"
#include <Thread/Thread_RoiPreview.hpp>

RoiPreviewThread::RoiPreviewThread(wxEvtHandler *parent, DataPtr data)
    : BaseThread(parent, data), PreviewableThread(), ImageSizeDataThread(data) {
}

RoiPreviewThread::~RoiPreviewThread() {}

wxThread::ExitCode RoiPreviewThread::Entry() {

    wxCommandEvent startCaptureEvent(c_PREVIEW_CAPTURE_EVENT, PREVIEW_START);
    wxPostEvent(parent, startCaptureEvent);

    try {
        while (!TestDestroy()) {
            if (data->isCaptureDataEmpty()) {
                throw std::runtime_error("Capture data is empty");
            }

            auto firstData = data->getCaptureData().at(0);
            cv::Mat frame = firstData.image.clone();

            auto roiData = data->getTrackingData();
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

        wxCommandEvent errorCaptureEvent(c_PREVIEW_CAPTURE_EVENT,
                                         PREVIEW_ERROR);
        wxPostEvent(parent, errorCaptureEvent);

        return 0;
    }

    UpdatePreviewEvent::Submit(parent, CLEAR_PREVIEW);

    wxCommandEvent endCaptureEvent(c_PREVIEW_CAPTURE_EVENT, PREVIEW_END);
    wxPostEvent(parent, endCaptureEvent);

    return 0;
}

ThreadID RoiPreviewThread::getID() const { return id; }