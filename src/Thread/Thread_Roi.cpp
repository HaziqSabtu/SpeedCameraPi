#include <Event/Event.hpp>
#include <Thread/Thread_Roi.hpp>

/**
 * @brief Construct a new Roi Thread:: Roi Thread object
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 */
RoiThread::RoiThread(wxEvtHandler *parent, DataPtr data)
    : BaseThread(parent, data), PreviewableThread(), ImageSizeDataThread(data) {
}

/**
 * @brief Destroy the Roi Thread:: Roi Thread object
 *
 */
RoiThread::~RoiThread() {}

/**
 * @brief Entry point of the Thread
 * @details Send the start event to the View. Then capture the frame from the
 * captured data and send it to the View. Perform the roi selection. If an error
 * occurs, send the error event to the View. Finally send the end event to the
 * View.
 *
 * @return ExitCode
 */
wxThread::ExitCode RoiThread::Entry() {

    wxCommandEvent startRoiEvent(c_ROI_EVENT, ROI_START);
    wxPostEvent(parent, startRoiEvent);

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

        wxCommandEvent errorRoiEvent(c_ROI_EVENT, ROI_ERROR);
        wxPostEvent(parent, errorRoiEvent);

        return 0;
    }

    UpdatePreviewEvent::Submit(parent, CLEAR_PREVIEW);

    wxCommandEvent endRoiEvent(c_ROI_EVENT, ROI_END);
    wxPostEvent(parent, endRoiEvent);
    return 0;
}

/**
 * @brief Get the ID of the Thread
 *
 * @return ThreadID
 */
ThreadID RoiThread::getID() const { return threadID; }

/**
 * @brief Set the first point of the ROI
 *
 * @param point
 */
void RoiThread::setPoint1(cv::Point point) { this->p1 = point; }

/**
 * @brief Set the second point of the ROI
 *
 * @param point
 */
void RoiThread::setPoint2(cv::Point point) { this->p2 = point; }

/**
 * @brief Check if the ROI is valid
 *
 * @return true
 * @return false
 */
bool RoiThread::isRectValid() {
    return p1.x != -1 && p1.y != -1 && p2.x != -1 && p2.y != -1;
}

/**
 * @brief Get the ROI
 *
 * @return cv::Rect
 */
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

/**
 * @brief Get the real ROI
 * @note The ROI is scaled to the original image size
 *
 * @return cv::Rect
 */
cv::Rect RoiThread::getRealRect() {
    cv::Rect rect = getRect();
    return Utils::scaleRect(rect, pSize, imageSize);
}