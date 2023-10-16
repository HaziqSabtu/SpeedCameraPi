#pragma once

#include "Model/SessionData.hpp"
#include "Thread/Thread_Base.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_ProcessImage.hpp>
#include <Event/Event_UpdatePreview.hpp>
#include <Thread/Task/Task_OpticalFlow.hpp>
#include <Thread/Task/Task_Sift.hpp>
#include <Thread/ThreadPool.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <memory>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <wx/string.h>
#include <wx/thread.h>
#include <wx/wx.h>

class ResultPreviewThread : public BaseThread,
                            public PreviewableThread,
                            public ImageSizeDataThread {
  public:
    ResultPreviewThread(wxEvtHandler *parent, DataPtr data);
    ~ResultPreviewThread();

    ThreadID getID() const override;

    int GetImageIndex() const;
    void SetImageIndex(int index);

    bool GetShowBox() const;
    void SetShowBox(bool show);

    bool GetShowIntersection() const;
    void SetShowIntersection(bool show);

    bool GetShowLanes() const;
    void SetShowLanes(bool show);

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_RESULT_PREVIEW;

    mutable std::mutex mutex;
    int imageIndex = 0;
    bool isShowBox = false;
    bool isShowIntersection = false;
    bool isShowLanes = false;

    int maxImageIndex;

    const int PREVIEW_DELAY = 300;
};