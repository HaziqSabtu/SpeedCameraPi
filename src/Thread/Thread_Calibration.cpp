#include "Event/Event_Calibration.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include <Thread/Thread_Calibration.hpp>
#include <opencv2/imgproc.hpp>
#include <wx/utils.h>

CalibrationThread::CalibrationThread(wxEvtHandler *parent,
                                     std::unique_ptr<CameraBase> &camera,
                                     HSVFilter &hsvFilter, BFS &bfs,
                                     RansacLine &ransac)
    : wxThread(wxTHREAD_JOINABLE), camera(std::move(camera)),
      hsvFilter(hsvFilter), bfs(bfs), ransac(ransac) {
    this->parent = parent;
}

CalibrationThread::~CalibrationThread() {}

wxThread::ExitCode CalibrationThread::Entry() {

    wxCommandEvent startCalibrationEvent(c_CALIBRATION_EVENT,
                                         CALIBRATION_START);
    wxPostEvent(parent, startCalibrationEvent);

    try {

        while (!TestDestroy()) {
            cv::Mat frame;
            camera->getFrame(frame);

            if (frame.empty()) {
                std::cout << "Failed to capture frame" << std::endl;
                continue;
            }

            cv::Size s(320, 240);
            cv::resize(frame, frame, s);

            cv::Mat hsvFrame = hsvFilter.toHSV(frame);
            cv::Mat filteredFrame = bfs.run(hsvFrame);

            auto boundingBox = cv::boundingRect(filteredFrame);
            cv::rectangle(filteredFrame, boundingBox, cv::Scalar(0, 255, 0), 2);

            cv::Mat combined =
                cv::Mat::zeros(frame.rows, frame.cols, frame.type());
            if (!boundingBox.empty()) {
                cv::Mat crop = hsvFrame(boundingBox);

                cv::Mat mask = cv::Mat::zeros(frame.rows, frame.cols, CV_8UC1);
                cv::rectangle(mask, boundingBox, cv::Scalar(255, 255, 255), -1);
                cv::bitwise_and(hsvFrame, hsvFrame, combined, mask);

                cv::Mat mask_yellow = hsvFilter.yellowMask(combined);
                Detection::Line yellowLine =
                    ransac.run(mask_yellow).Extrapolate(mask_yellow);
                if (!yellowLine.isNull()) {
                    cv::line(frame, yellowLine.p1, yellowLine.p2,
                             cv::Scalar(0, 255, 255), 2);
                }

                cv::Mat mask_blue = hsvFilter.blueMask(combined);
                Detection::Line blueLine =
                    ransac.run(mask_blue).Extrapolate(mask_blue);
                if (!blueLine.isNull()) {
                    cv::line(frame, blueLine.p1, blueLine.p2,
                             cv::Scalar(255, 0, 0), 2);
                }

                UpdateStatusEvent updateStatusEvent(c_UPDATE_STATUS_EVENT,
                                                    UPDATE_STATUS);
                updateStatusEvent.SetStatus(
                    StatusCollection::STATUS_LINE_DETECTED);
                wxPostEvent(parent, updateStatusEvent);
            } else {
                UpdateStatusEvent updateStatusEvent(c_UPDATE_STATUS_EVENT,
                                                    UPDATE_STATUS);
                updateStatusEvent.SetStatus(
                    StatusCollection::STATUS_LINE_NOT_DETECTED);
                wxPostEvent(parent, updateStatusEvent);
            }

            UpdatePreviewEvent updatePreviewEvent(c_UPDATE_PREVIEW_EVENT,
                                                  UPDATE_PREVIEW);
            updatePreviewEvent.SetImage(frame);
            wxPostEvent(parent, updatePreviewEvent);

            wxMilliSleep(100);
        }
    } catch (const std::exception &e) {
        ErrorEvent errorEvent(c_ERROR_EVENT);
        errorEvent.SetErrorData(e.what());
        wxPostEvent(parent, errorEvent);
    }

    UpdatePreviewEvent clearPreviewEvent(c_UPDATE_PREVIEW_EVENT, CLEAR_PREVIEW);
    wxPostEvent(parent, clearPreviewEvent);

    wxCommandEvent endCalibrationEvent(c_CALIBRATION_EVENT, CALIBRATION_END);
    wxPostEvent(parent, endCalibrationEvent);
    return 0;
}

std::unique_ptr<CameraBase> CalibrationThread::getCamera() {
    return std::move(camera);
}

void CalibrationThread::setPoint(cv::Point point) { bfs.setStart(point); }