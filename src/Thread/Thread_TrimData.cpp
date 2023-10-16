#include "Event/Event_Calibration.hpp"
#include "Event/Event_Error.hpp"
#include "Event/Event_Replay.hpp"
#include "Event/Event_RequestUpdateState.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/CalibrationData.hpp"
#include "Model/SessionData.hpp"
#include "UI/Layout/StatusPanel.hpp"
#include "Utils/Config/AppConfig.hpp"
#include <Thread/Thread_TrimData.hpp>
#include <opencv2/imgproc.hpp>
#include <wx/event.h>
#include <wx/utils.h>

TrimDataThread::TrimDataThread(wxEvtHandler *parent, DataPtr data)
    : BaseThread(parent, data), PreviewableThread(),
      MAX_FRAME(data->getCaptureData().size()) {
    this->parent = parent;

    startPos = 0;
    endPos = MAX_FRAME - 1;
}

TrimDataThread::~TrimDataThread() {}

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

ThreadID TrimDataThread::getID() const { return threadID; }

void TrimDataThread::incrementStartPos() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (startPos < MAX_FRAME - 1) {
        startPos++;
    }
}

void TrimDataThread::decrementStartPos() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (startPos > 0) {
        startPos--;
    }
}

bool TrimDataThread::isStartIncrementable() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return getFrameRange() > MIN_ALLOWED_FRAME;
}

bool TrimDataThread::isStartDecrementable() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return startPos > 0;
}

void TrimDataThread::incrementEndPos() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (endPos < MAX_FRAME - 1) {
        endPos++;
    }
}

void TrimDataThread::decrementEndPos() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (endPos > 0) {
        endPos--;
    }
}

bool TrimDataThread::isEndIncrementable() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return endPos < MAX_FRAME - 1;
}

bool TrimDataThread::isEndDecrementable() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return getFrameRange() > MIN_ALLOWED_FRAME;
}

void TrimDataThread::setStatus(TrimDataThreadCurrentStatus status) {
    std::lock_guard<std::mutex> lock(m_mutex);
    this->status = status;
}

TrimDataThreadCurrentStatus TrimDataThread::getStatus() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return this->status;
}

int TrimDataThread::getFrameRange() { return abs(endPos - startPos) + 1; }