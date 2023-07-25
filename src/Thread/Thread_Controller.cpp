#include "Thread/Thread_LoadCapture.hpp"
#include <Thread/Thread_Controller.hpp>
#include <exception>
#include <iostream>
#include <memory>

ThreadController::ThreadController() { initThread(); }

ThreadController::~ThreadController() {
    try {
        deleteThread();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void ThreadController::initThread() {
    captureThread = nullptr;
    loadCaptureThread = nullptr;
    loadFileThread = nullptr;
    replayThread = nullptr;
};

void ThreadController::deleteThread() {
    stopAndDeleteThread(captureThread);
    stopAndDeleteThread(loadCaptureThread);
    stopAndDeleteThread(loadFileThread);
    stopAndDeleteThread(replayThread);
};

bool ThreadController::isThreadNullptr(ThreadID threadID) {
    if (threadID == ThreadID::THREAD_CAPTURE) {
        return captureThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_LOAD_CAPTURE) {
        return loadCaptureThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_LOAD_FILE) {
        return loadFileThread == nullptr;
    }

    if (threadID == ThreadID::THREAD_REPLAY) {
        return replayThread == nullptr;
    }

    throw std::runtime_error(
        "ThreadController::isThreadNullptr() - Invalid ThreadID");
}

bool ThreadController::isThreadOwner(ThreadID threadID, PanelID panelID) {
    if (owner.find(threadID) == owner.end()) {
        return false;
    }
    return owner[threadID] == panelID;
}

bool ThreadController::isThreadsWithCameraNullptr() {
    return captureThread == nullptr && loadCaptureThread == nullptr;
}

void ThreadController::startCaptureHandler(wxEvtHandler *parent,
                                           std::unique_ptr<CameraBase> &camera,
                                           PanelID panelID) {

    captureThread = new CaptureThread(parent, camera);
    captureThread->Run();

    owner[captureThread->getID()] = panelID;
}

void ThreadController::endCaptureHandler() {
    captureThread = stopAndDeleteThread(captureThread);
}

void ThreadController::startLoadCaptureHandler(
    wxEvtHandler *parent, std::unique_ptr<CameraBase> &camera,
    std::shared_ptr<std::vector<ImageData>> imgData, const int maxFrame,
    PanelID panelID) {

    loadCaptureThread =
        new LoadCaptureThread(parent, camera, imgData, maxFrame);
    loadCaptureThread->Run();

    owner[loadCaptureThread->getID()] = panelID;
}

void ThreadController::endLoadCaptureHandler() {
    loadCaptureThread = stopAndDeleteThread(loadCaptureThread);
}

void ThreadController::startReplayHandler(
    wxEvtHandler *parent, std::shared_ptr<std::vector<ImageData>> imgData,
    PanelID panelID) {

    replayThread = new ReplayThread(parent, imgData);
    replayThread->Run();

    owner[replayThread->getID()] = panelID;
}

void ThreadController::endReplayHandler() {
    replayThread = stopAndDeleteThread(replayThread);
}

CaptureThread *ThreadController::getCaptureThread() { return captureThread; }

LoadCaptureThread *ThreadController::getLoadCaptureThread() {
    return loadCaptureThread;
}

LoadFileThread *ThreadController::getLoadFileThread() { return loadFileThread; }

ReplayThread *ThreadController::getReplayThread() { return replayThread; }

void ThreadController::startLoadFileHandler(wxEvtHandler *parent, int maxFrame,
                                            std::string path, PanelID panelID) {

    // loadFileThread = new LoadFileThread(parent, maxFrame, path);
    // loadFileThread->Run();

    // owner[loadFileThread->getID()] = panelID;
    throw std::runtime_error("Not Implemented");
}

void ThreadController::endLoadFileHandler() {
    loadFileThread = stopAndDeleteThread(loadFileThread);
}

template <typename T>
T *ThreadController::stopAndDeleteThread(T *threadPtr) {
    if (threadPtr == nullptr) {
        return nullptr;
    }

    threadPtr->Delete();
    delete threadPtr;
    threadPtr = nullptr;

    return threadPtr;
}

void ThreadController::killAllThreads() { deleteThread(); }

// TODO: Cleanup
// Maybe Required for testing
// CaptureThread *
// CaptureModel::initCaptureThread(wxEvtHandler *parent,
//                                 std::unique_ptr<CameraBase> &camera) {
//     return new CaptureThread(parent, camera);
// }
