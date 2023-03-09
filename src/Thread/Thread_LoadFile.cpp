#include <Thread/Thread_LoadFile.hpp>

LoadFileThread::LoadFileThread(wxEvtHandler *parent, ThreadPool *threadPool,
                               std::vector<ImageData> *imgData, wxString path)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), pool(threadPool), path(path),
      imgData(imgData) {}

LoadFileThread::~LoadFileThread() {}

wxThread::ExitCode LoadFileThread::Entry() {
    try {
        pool->AddTask(new LoadTask(imgData, path, 5));

        while (imgData->empty()) {
            wxMilliSleep(30);
        }

        cv::Mat frame = imgData->at(0).image;
        UpdateImageEvent event(c_UPDATE_IMAGE_EVENT, UPDATE_IMAGE);
        event.SetImageData(frame);
        wxPostEvent(parent, event);

        while (pool->isWorkerBusy() || pool->HasTasks(TaskType::TASK_LOAD)) {
            wxMilliSleep(30);
        }

        int limit = 5;
        imgData->erase(imgData->begin() + limit, imgData->end());

        for (int i = 1; i < imgData->size(); i++) {
            cv::Mat frame = imgData->at(i).image;
            UpdateImageEvent event(c_UPDATE_IMAGE_EVENT, UPDATE_IMAGE);
            event.SetImageData(frame);
            wxPostEvent(parent, event);
            wxMilliSleep(100);
        }
    } catch (const std::exception &e) {
        std::cout << "LoadFileThread::Entry() - Error: \n"
                  << e.what() << std::endl;
    }

    cv::Mat first = imgData->at(0).image;
    UpdateImageEvent event(c_UPDATE_IMAGE_EVENT, UPDATE_IMAGE);
    event.SetImageData(first);
    wxPostEvent(parent, event);

    ProcessImageEvent event2(c_PROCESS_IMAGE_EVENT);
    wxPostEvent(parent, event2);
    return 0;
}