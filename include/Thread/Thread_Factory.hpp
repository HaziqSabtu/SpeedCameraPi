#pragma once

#include "Thread/Thread_CameraPreview.hpp"

static class ThreadFactory {
  public:
    static CaptureThread *
    createCaptureThread(wxEvtHandler *parent,
                        std::shared_ptr<CameraBase> camera) {
        return new CaptureThread(parent, camera);
    }
} ThreadFactory;