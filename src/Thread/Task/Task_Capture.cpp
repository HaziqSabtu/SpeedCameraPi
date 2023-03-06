#include <Thread/Task/Task_Capture.hpp>

CaptureTask::CaptureTask(std::vector<ImageData> *imgData, cv::VideoCapture *cap,
                         const int maxCapture)
    : type(TaskType::TASK_CAPTURE), imgData(imgData), cap(cap),
      maxCapture(maxCapture) {}

void CaptureTask::Execute() {
    for (int i = 0; i < maxCapture; i++) {
        cv::Mat frame;
        cap->read(frame);
        imgData->push_back(ImageData(frame));
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

TaskType CaptureTask::GetType() const { return type; }