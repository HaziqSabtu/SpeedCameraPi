#include "Event/Event_Calibration.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/CalibrationData.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_Base.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "Utils/CommonUtils.hpp"
#include "Utils/Config/AppConfig.hpp"
#include <Thread/Thread_Roi.hpp>
#include <opencv2/imgproc.hpp>
#include <wx/utils.h>

RoiThread::RoiThread(wxEvtHandler *parent, DataPtr data)
    : BaseThread(parent, data), PreviewableThread(), ImageSizeDataThread(data) {
}

RoiThread::~RoiThread() {}

wxThread::ExitCode RoiThread::Entry() {

    wxCommandEvent startCalibrationEvent(c_CALIBRATION_EVENT,
                                         CALIBRATION_CAMERA_START);
    wxPostEvent(parent, startCalibrationEvent);

    try {

        if (data->isCaptureDataEmpty()) {
            throw std::runtime_error("capture data is empty");
        }

        while (!TestDestroy()) {
            auto firstData = data->getCaptureData().at(0);
            cv::Mat firstFrame = firstData.image.clone();

            cv::resize(firstFrame, firstFrame, pSize);

            if (isRectValid()) {
                cv::rectangle(firstFrame, getRect(), cv::Scalar(0, 255, 0), 2);
            }

            UpdatePreviewEvent::Submit(parent, firstFrame);

            wxMilliSleep(50);
        }

    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }

    UpdatePreviewEvent::Submit(parent, CLEAR_PREVIEW);

    wxCommandEvent endCalibrationEvent(c_CALIBRATION_EVENT,
                                       CALIBRATION_CAMERA_END);
    wxPostEvent(parent, endCalibrationEvent);
    return 0;
}

ThreadID RoiThread::getID() const { return threadID; }

void RoiThread::setPoint1(cv::Point point) { this->p1 = point; }

void RoiThread::setPoint2(cv::Point point) { this->p2 = point; }

bool RoiThread::isRectValid() {
    return p1.x != -1 && p1.y != -1 && p2.x != -1 && p2.y != -1;
}

cv::Rect RoiThread::getRect() {
    cv::Point start, end;

    if (p1.x < p2.x) {
        start.x = p1.x;
        end.x = p2.x;
    } else {
        start.x = p2.x;
        end.x = p1.x;
    }

    if (p1.y < p2.y) {
        start.y = p1.y;
        end.y = p2.y;
    } else {
        start.y = p2.y;
        end.y = p1.y;
    }

    return cv::Rect(start, end);
}

cv::Rect RoiThread::getRealRect() {
    cv::Rect rect = getRect();
    return Utils::scaleRect(rect, pSize, imageSize);
}