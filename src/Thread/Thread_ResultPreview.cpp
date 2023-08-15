#include "Event/Event_Error.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/CalibrationData.hpp"
#include "Model/SessionData.hpp"
#include "Thread/ThreadPool.hpp"
#include "Utils/Config/AppConfig.hpp"
#include "Utils/ImageUtils.hpp"
#include <Thread/Thread_ResultPreview.hpp>
#include <opencv2/imgproc.hpp>
#include <wx/utils.h>

ResultPreviewThread::ResultPreviewThread(wxEvtHandler *parent, DataPtr data)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), data(data) {
    AppConfig c;
    auto previewConfig = c.GetPreviewConfig();
    int width = previewConfig.width;
    int height = previewConfig.height;
    pSize = cv::Size(width, height);

    if (data->isCaptureDataEmpty()) {
        throw std::runtime_error("Capture Data is empty");
    }

    auto captureData = data->getCaptureData();
    auto firstData = captureData.front();
    auto firstImage = firstData.image;
    imageSize = firstImage.size();
}

ResultPreviewThread::~ResultPreviewThread() {}

wxThread::ExitCode ResultPreviewThread::Entry() {
    try {

        if (data->isCaptureDataEmpty()) {
            throw std::runtime_error("Capture Data is empty");
        }

        if (data->isAllignDataEmpty()) {
            throw std::runtime_error("Allign Data is empty");
        }

        auto allignData = data->getAllignData();

        auto roi = data->getRoiData().trackedRoi;

        if (roi.size() != allignData.size()) {
            int roiSize = roi.size();
            int allignDataSize = allignData.size();
            throw std::runtime_error("Size of roi and allign data not match: " +
                                     std::to_string(roiSize) + " vs " +
                                     std::to_string(allignDataSize));
        }

        if (data->isCalibDataEmpty()) {
            throw std::runtime_error("Calibration Data is empty");
        }

        auto calibData = data->getCalibData();

        if (data->isResultDataEmpty()) {
            throw std::runtime_error("Result Data is empty");
        }

        auto resultData = data->getResultData();

        maxImageIndex = allignData.size();

        while (!TestDestroy()) {
            if (imageIndex >= allignData.size()) {
                wxMilliSleep(PREVIEW_DELAY);
                continue;
            }

            cv::Mat image = allignData.at(imageIndex).image.clone();

            cv::resize(image, image, pSize);

            if (isShowBox) {
                cv::Rect rect = roi.at(imageIndex);
                auto scaledRect = Utils::scaleRect(rect, imageSize, pSize);
                cv::rectangle(image, scaledRect, cv::Scalar(0, 255, 0), 2);
            }

            if (isShowIntersection) {
                auto lines = resultData.intersectingLines.at(imageIndex);
                auto scaledLine = lines.Scale(imageSize, pSize);
                cv::line(image, scaledLine.p1, scaledLine.p2,
                         cv::Scalar(0, 0, 255), 2);
            }

            if (isShowLanes) {
                auto leftLine = calibData.lineLeft;
                auto rightLine = calibData.lineRight;

                auto scaledLeft = leftLine.Scale(imageSize, pSize);
                auto scaledRight = rightLine.Scale(imageSize, pSize);

                cv::line(image, scaledLeft.p1, scaledLeft.p2,
                         cv::Scalar(255, 0, 0), 2);
                cv::line(image, scaledRight.p1, scaledRight.p2,
                         cv::Scalar(0, 255, 255), 2);
            }

            UpdatePreviewEvent::Submit(parent, image);

            imageIndex++;

            wxMilliSleep(PREVIEW_DELAY);
        }
    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }

    UpdatePreviewEvent::Submit(parent, CLEAR_PREVIEW);

    return 0;
}

ThreadID ResultPreviewThread::getID() const { return threadID; }

int ResultPreviewThread::GetImageIndex() const {
    std::unique_lock<std::mutex> lock(mutex);
    return imageIndex;
}

void ResultPreviewThread::SetImageIndex(int index) {
    std::unique_lock<std::mutex> lock(mutex);
    imageIndex = index;
}

bool ResultPreviewThread::GetShowBox() const {
    std::unique_lock<std::mutex> lock(mutex);
    return isShowBox;
}

void ResultPreviewThread::SetShowBox(bool show) {
    std::unique_lock<std::mutex> lock(mutex);
    isShowBox = show;
    imageIndex = imageIndex == maxImageIndex ? 0 : imageIndex;
}

bool ResultPreviewThread::GetShowIntersection() const {
    std::unique_lock<std::mutex> lock(mutex);
    return isShowIntersection;
}

void ResultPreviewThread::SetShowIntersection(bool show) {
    std::unique_lock<std::mutex> lock(mutex);
    isShowIntersection = show;
    imageIndex = imageIndex == maxImageIndex ? 0 : imageIndex;
}

bool ResultPreviewThread::GetShowLanes() const {
    std::unique_lock<std::mutex> lock(mutex);
    return isShowLanes;
}

void ResultPreviewThread::SetShowLanes(bool show) {
    std::unique_lock<std::mutex> lock(mutex);
    isShowLanes = show;
    imageIndex = imageIndex == maxImageIndex ? 0 : imageIndex;
}