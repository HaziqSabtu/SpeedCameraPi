#include <Event/Event.hpp>
#include <Thread/Thread_TrimData.hpp>

/**
 * @brief Construct a new Trim Data Thread:: Trim Data Thread object
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 */
TrimDataThread::TrimDataThread(wxEvtHandler *parent, DataPtr data)
    : BaseThread(parent, data), PreviewableThread(),
      MAX_FRAME(data->getCaptureData().size()) {
    this->parent = parent;

    startPos = 0;
    endPos = MAX_FRAME - 1;
}

/**
 * @brief Destroy the Trim Data Thread:: Trim Data Thread object
 *
 */
TrimDataThread::~TrimDataThread() {}

/**
 * @brief Process the trim data
 * @details This function will be called when the thread is started
 * <ul>
 * <li>Check if capture data is empty</li>
 * <li>Check if startPos or endPos is -1</li>
 * <li>Check if startPos > endPos</li>
 * <li>Check if frame range is less than MIN_ALLOWED_FRAME</li>
 * <li>Resize the capture data</li>
 * <li>Update the capture data</li>
 * </ul>
 *
 *
 * @return wxThread::ExitCode
 */
void TrimDataThread::processTrimData() {
    auto captureData = data->getCaptureData();

    if (captureData.empty()) {
        throw std::runtime_error("capture data is empty");
    }

    if (startPos == -1 || endPos == -1) {
        throw std::runtime_error("startPos or endPos is -1");
    }

    if (startPos > endPos) {
        throw std::runtime_error("startPos > endPos");
    }

    if (getFrameRange() < MIN_ALLOWED_FRAME) {
        throw std::runtime_error("getFrameRange() < MIN_ALLOWED_FRAME");
    }

    // resize capture data
    std::vector<CaptureData> trimData;
    for (int i = startPos; i <= endPos; i++) {
        auto data = captureData.at(i);
        cv::Mat frame = data.image.clone();
        trimData.push_back(CaptureData(frame, data.time));
    }

    // update capture data
    data->setCaptureData(trimData);
}

/**
 * @brief Entry point of the Thread
 * @details Send the start event to the View. Then perform the trim data task.
 * If an error occurs, send the error event to the View. Finally send the end
 * event to the View.
 *
 * @return ExitCode
 */
wxThread::ExitCode TrimDataThread::Entry() {
    try {
        if (data->isCaptureDataEmpty()) {
            throw std::runtime_error("capture data is empty");
        }

        while (!TestDestroy()) {
            int startPos;
            int endPos;
            TrimDataThreadCurrentStatus status;
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                startPos = this->startPos;
                endPos = this->endPos;
                status = this->status;
            }

            if (status == TRIM_PREVIEW) {
                if (startPos == -1 || endPos == -1) {
                    throw std::runtime_error("startPos or endPos is -1");
                }

                if (startPos > endPos) {
                    throw std::runtime_error("startPos > endPos");
                }

                if (getFrameRange() < MIN_ALLOWED_FRAME) {
                    throw std::runtime_error(
                        "getFrameRange() < MIN_ALLOWED_FRAME");
                }

                for (int i = startPos; i <= endPos; i++) {
                    auto data = this->data->getCaptureData().at(i);
                    cv::Mat frame = data.image.clone();
                    cv::resize(frame, frame, pSize);
                    UpdatePreviewEvent::Submit(parent, frame);
                    wxMilliSleep(MILLI_SLEEP);
                }
                {
                    std::lock_guard<std::mutex> lock(m_mutex);
                    this->status = TRIM_NONE;
                }
                wxCommandEvent event(c_REQUEST_UPDATE_STATE_EVENT,
                                     REQUEST_UPDATE_STATE);
                wxPostEvent(parent, event);
            }

            if (status == TRIM_START) {
                if (startPos == -1) {
                    throw std::runtime_error("startPos is -1");
                }

                if (startPos > MAX_FRAME - 1) {
                    throw std::runtime_error("startPos > MAX_FRAME - 1");
                }

                if (getFrameRange() < MIN_ALLOWED_FRAME) {
                    throw std::runtime_error(
                        "getFrameRange() < MIN_ALLOWED_FRAME");
                }

                auto data = this->data->getCaptureData().at(startPos);
                cv::Mat frame = data.image.clone();
                cv::resize(frame, frame, pSize);
                UpdatePreviewEvent::Submit(parent, frame);
            }

            if (status == TRIM_END) {
                if (endPos == -1) {
                    throw std::runtime_error("endPos is -1");
                }

                if (endPos > MAX_FRAME - 1) {
                    throw std::runtime_error("endPos > MAX_FRAME - 1");
                }

                if (getFrameRange() < MIN_ALLOWED_FRAME) {
                    throw std::runtime_error(
                        "getFrameRange() < MIN_ALLOWED_FRAME");
                }

                auto data = this->data->getCaptureData().at(endPos);
                cv::Mat frame = data.image.clone();
                cv::resize(frame, frame, pSize);
                UpdatePreviewEvent::Submit(parent, frame);
            }

            wxString msg = wxString::Format(
                "[%d, %d] --> [%d, %d] -- %d frames", 0, MAX_FRAME - 1,
                this->startPos, this->endPos, getFrameRange());
            UpdateStatusEvent::Submit(parent, msg);

            wxMilliSleep(MILLI_SLEEP);
        }

    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
    UpdatePreviewEvent::Submit(parent, CLEAR_PREVIEW);
    return 0;
}

/**
 * @brief Get the ID of the Thread
 *
 * @return ThreadID
 */
ThreadID TrimDataThread::getID() const { return threadID; }

/**
 * @brief Increment the start position
 *
 */
void TrimDataThread::incrementStartPos() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (startPos < MAX_FRAME - 1) {
        startPos++;
    }
}

/**
 * @brief Decrement the start position
 *
 */
void TrimDataThread::decrementStartPos() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (startPos > 0) {
        startPos--;
    }
}

/**
 * @brief Check if the start position is incrementable
 *
 * @return true
 * @return false
 */
bool TrimDataThread::isStartIncrementable() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return getFrameRange() > MIN_ALLOWED_FRAME;
}

/**
 * @brief Check if the start position is decrementable
 *
 * @return true
 * @return false
 */
bool TrimDataThread::isStartDecrementable() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return startPos > 0;
}

/**
 * @brief Increment the end position
 *
 */
void TrimDataThread::incrementEndPos() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (endPos < MAX_FRAME - 1) {
        endPos++;
    }
}

/**
 * @brief Decrement the end position
 *
 */
void TrimDataThread::decrementEndPos() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (endPos > 0) {
        endPos--;
    }
}

/**
 * @brief Check if the end position is incrementable
 *
 * @return true
 * @return false
 */
bool TrimDataThread::isEndIncrementable() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return endPos < MAX_FRAME - 1;
}

/**
 * @brief Check if the end position is decrementable
 *
 * @return true
 * @return false
 */
bool TrimDataThread::isEndDecrementable() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return getFrameRange() > MIN_ALLOWED_FRAME;
}

/**
 * @brief Set the status of the TrimDataThread
 *
 * @param status TrimDataThreadCurrentStatus
 */
void TrimDataThread::setStatus(TrimDataThreadCurrentStatus status) {
    std::lock_guard<std::mutex> lock(m_mutex);
    this->status = status;
}

/**
 * @brief Get the status of the TrimDataThread
 *
 * @return TrimDataThreadCurrentStatus
 */
TrimDataThreadCurrentStatus TrimDataThread::getStatus() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return this->status;
}

/**
 * @brief Get the frame range
 *
 * @return int
 */
int TrimDataThread::getFrameRange() { return abs(endPos - startPos) + 1; }