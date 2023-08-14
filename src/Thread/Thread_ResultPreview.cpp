#include "Event/Event_Error.hpp"
#include "Event/Event_UpdatePreview.hpp"
#include "Event/Event_UpdateState.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/CalibrationData.hpp"
#include "Model/SessionData.hpp"
#include "Thread/ThreadPool.hpp"
#include <Thread/Thread_ResultPreview.hpp>
#include <wx/utils.h>

ResultPreviewThread::ResultPreviewThread(wxEvtHandler *parent, DataPtr data)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), data(data) {}

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

        for (int i = 0; i < allignData.size(); i++) {
            cv::Mat image = allignData.at(i).image;
            cv::Rect rect = roi.at(i);

            cv::rectangle(image, rect, cv::Scalar(0, 255, 0), 2);

            UpdatePreviewEvent::Submit(parent, image);
        }

    } catch (const std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }

    return 0;
}

ThreadID ResultPreviewThread::getID() const { return threadID; }