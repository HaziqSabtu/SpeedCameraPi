
#include "Event/Event_Error.hpp"
#include "Thread/Thread_Base.hpp"
#include "Utils/Camera/CameraBase.hpp"
#include <Thread/Thread_CalibrationPreviewCamera.hpp>
#include <memory>
#include <opencv2/core/types.hpp>

CalibrationPreviewCameraThread::CalibrationPreviewCameraThread(
    wxEvtHandler *parent, DataPtr data, CameraPtr &camera)
    : BaseThread(parent, data), CameraAccessor(camera), ImageSizeCameraThread(),
      PreviewableThread() {}

CalibrationPreviewCameraThread::~CalibrationPreviewCameraThread() {}

wxThread::ExitCode CalibrationPreviewCameraThread::Entry() {

    wxCommandEvent startCaptureEvent(c_PREVIEW_CAMERA_EVENT, PREVIEW_START);
    wxPostEvent(parent, startCaptureEvent);

    try {
        while (!TestDestroy()) {
            cv::Mat frame;
            camera->getFrame(frame);

            if (frame.empty()) {
                std::cout << "Failed to capture frame" << std::endl;
                continue;
            }

            cv::resize(frame, frame, pSize);

            auto isLineNull = data->isCalibrationDataEmpty();
            if (!isLineNull) {
                auto calibData = data->getCalibrationData();
                cv::Scalar yellow(0, 255, 255);
                cv::Scalar blue(255, 0, 0);

                Line left = calibData.lineLeft;
                Line right = calibData.lineRight;

                left = left.Scale(imageSize, pSize);
                right = right.Scale(imageSize, pSize);

                cv::line(frame, left.p1, left.p2, yellow, 2);
                cv::line(frame, right.p1, right.p2, blue, 2);
            }

            UpdatePreviewEvent::Submit(parent, frame);
        }
    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }

    UpdatePreviewEvent clearPreviewEvent(c_UPDATE_PREVIEW_EVENT, CLEAR_PREVIEW);
    wxPostEvent(parent, clearPreviewEvent);

    wxCommandEvent endCaptureEvent(c_PREVIEW_CAMERA_EVENT, PREVIEW_END);
    wxPostEvent(parent, endCaptureEvent);

    return 0;
}

ThreadID CalibrationPreviewCameraThread::getID() const { return id; }