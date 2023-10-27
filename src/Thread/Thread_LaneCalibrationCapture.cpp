#include <Event/Event.hpp>
#include <Thread/Thread_LaneCalibrationCapture.hpp>

/**
 * @brief Construct a new Lane Calibration Capture Thread:: Lane Calibration
 * Capture Thread object
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 * @param hsvFilter Pointer to the HSVFilter object
 * @param bfs Pointer to the BFS object
 * @param ransac Pointer to the RansacLine object
 */
LaneCalibrationCaptureThread::LaneCalibrationCaptureThread(
    wxEvtHandler *parent, DataPtr data, HSVFilterPtr hsvFilter, BFSPtr bfs,
    RansacLinePtr ransac)
    : BaseLaneCalibrationThread(parent, data, hsvFilter, bfs, ransac),
      ImageSizeDataThread(data) {}

/**
 * @brief Destroy the Lane Calibration Capture Thread:: Lane Calibration Capture
 * Thread object
 *
 */
LaneCalibrationCaptureThread::~LaneCalibrationCaptureThread() {}

/**
 * @brief Entry point of the Thread
 * @details Send the start event to the View. Then capture the frame from the
 * captured data and send it to the View. Perform the lane calibration. If an
 * error occurs, send the error event to the View. Finally send the end event to
 * the View.
 *
 * @return ExitCode
 */
wxThread::ExitCode LaneCalibrationCaptureThread::Entry() {
    wxCommandEvent startCalibrationEvent(c_CALIBRATION_EVENT,
                                         CALIBRATION_CAPTURE_START);
    wxPostEvent(parent, startCalibrationEvent);

    try {

        cv::Mat firstFrame;

        auto captureData = data->getCaptureData();

        auto firstData = captureData.front();
        firstFrame = firstData.image;

        if (firstFrame.empty()) {
            throw std::runtime_error("Failed to capture frame");
        }

        cv::resize(firstFrame, firstFrame, pSize);

        while (!TestDestroy()) {

            cv::Mat previewImage = firstFrame.clone();

            cv::Mat hsvFrame = hsvFilter->toHSV(previewImage);
            cv::Mat filteredFrame = bfs->run(hsvFrame);

            auto boundingBox = cv::boundingRect(filteredFrame);
            cv::rectangle(filteredFrame, boundingBox, cv::Scalar(0, 255, 0), 2);

            cv::Mat combined = cv::Mat::zeros(
                previewImage.rows, previewImage.cols, previewImage.type());
            if (!boundingBox.empty()) {
                cv::Mat crop = hsvFrame(boundingBox);

                cv::Mat mask = cv::Mat::zeros(previewImage.rows,
                                              previewImage.cols, CV_8UC1);
                cv::rectangle(mask, boundingBox, cv::Scalar(255, 255, 255), -1);
                cv::bitwise_and(hsvFrame, hsvFrame, combined, mask);

                cv::Mat mask_yellow = hsvFilter->yellowMask(combined);
                Line yellowLine =
                    ransac->run(mask_yellow).Extrapolate(mask_yellow);
                if (!yellowLine.isNull()) {
                    updateRightLine(yellowLine);
                    cv::line(previewImage, yellowLine.p1, yellowLine.p2,
                             cv::Scalar(0, 255, 255), 2);
                }

                cv::Mat mask_blue = hsvFilter->blueMask(combined);
                Line blueLine = ransac->run(mask_blue).Extrapolate(mask_blue);
                if (!blueLine.isNull()) {
                    updateLeftLine(blueLine);
                    cv::line(previewImage, blueLine.p1, blueLine.p2,
                             cv::Scalar(255, 0, 0), 2);
                }
                bool isLeftNull = leftLine.isNull();
                bool isRightNull = rightLine.isNull();
                bool isBothNull = isBothLineValid();
                if (isBothLineValid()) {
                    wxCommandEvent lineOKEvent(c_CALIBRATION_EVENT,
                                               CALIBRATION_LINE_FOUND);
                    wxPostEvent(parent, lineOKEvent);
                } else {
                    wxCommandEvent lineNotOKEvent(c_CALIBRATION_EVENT,
                                                  CALIBRATION_LINE_NOT_FOUND);
                    wxPostEvent(parent, lineNotOKEvent);
                }
            }

            if (point != cv::Point(0, 0)) {
                cv::circle(previewImage, point, 5, cv::Scalar(0, 0, 255), -1);
            }

            UpdatePreviewEvent::Submit(parent, previewImage);

            wxMilliSleep(200);
        }
    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());

        wxCommandEvent endCalibrationEvent(c_CALIBRATION_EVENT,
                                           CALIBRATION_CAPTURE_END);
        wxPostEvent(parent, endCalibrationEvent);

        return 0;
    }

    UpdatePreviewEvent::Submit(parent, CLEAR_PREVIEW);

    wxCommandEvent endCalibrationEvent(c_CALIBRATION_EVENT,
                                       CALIBRATION_CAPTURE_END);
    wxPostEvent(parent, endCalibrationEvent);
    return 0;
}

/**
 * @brief Get the ThreadID
 *
 * @return ThreadID
 */
ThreadID LaneCalibrationCaptureThread::getID() const { return threadID; }

/**
 * @brief Get the Calibration Data object
 *
 * @return CalibrationData
 */
CalibrationData LaneCalibrationCaptureThread::getCalibrationData() {
    return CalibrationData(getRealLeftLine(), getRealRightLine());
}

/**
 * @brief Get the Real Right Line object
 * @note The line size is in preview size. Need to convert to original size
 *
 * @return Line
 */
Line LaneCalibrationCaptureThread::getRealRightLine() {
    std::unique_lock<std::mutex> lock(m_mutex);
    auto rl = rightLine.Scale(pSize, imageSize);
    return rl;
}

/**
 * @brief Get the Real Left Line object
 * @note The line size is in preview size. Need to convert to original size
 *
 * @return Line
 */
Line LaneCalibrationCaptureThread::getRealLeftLine() {
    std::unique_lock<std::mutex> lock(m_mutex);
    auto ll = leftLine.Scale(pSize, imageSize);
    return ll;
}