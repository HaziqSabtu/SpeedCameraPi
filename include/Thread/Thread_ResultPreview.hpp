#pragma once

#include <Thread/Thread_Base.hpp>

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
