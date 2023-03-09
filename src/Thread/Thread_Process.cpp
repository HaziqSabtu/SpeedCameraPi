#include <Thread/Thread_Process.hpp>

ProcessThread::ProcessThread(wxEvtHandler *parent, ThreadPool *threadPool,
                             std::vector<ImageData> *imgData)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), pool(threadPool),
      imgData(imgData) {}

ProcessThread::~ProcessThread() {}

wxThread::ExitCode ProcessThread::Entry() {
    try {
        std::cout << "ProcessThread::Entry() - Start" << std::endl;
        for (int i = 1; i < imgData->size(); i++) {
            pool->AddTask(new SiftTask(imgData, i));
        }
        std::cout << "ProcessThread::Entry() - Added Sift Tasks" << std::endl;
        while (pool->isWorkerBusy() || pool->HasTasks(TaskType::TASK_SIFT)) {
            std::cout
                << "ProcessThread::Entry() - Waiting for Sift Tasks to finish"
                << std::endl;
            wxMilliSleep(100);
        }
        std::cout << "ProcessThread::Entry() - Sift Tasks Finished"
                  << std::endl;
        for (int i = 0; i < imgData->size(); i++) {
            cv::Mat frame = imgData->at(i).image;
            UpdateImageEvent event(c_UPDATE_IMAGE_EVENT, UPDATE_IMAGE);
            event.SetImageData(frame);
            wxPostEvent(parent, event);
            wxMilliSleep(100);
        }
        std::cout << "ProcessThread::Entry() - End" << std::endl;
    } catch (const std::exception &e) {
        std::cout << "ProcessThread::Entry() - Error: \n"
                  << e.what() << std::endl;
    }
    UpdateImageEvent event(c_UPDATE_IMAGE_EVENT, CLEAR_IMAGE);
    wxPostEvent(parent, event);
    return 0;
}