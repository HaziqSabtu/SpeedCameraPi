#pragma once

#include <Thread/Thread_Base.hpp>

enum TrimDataThreadCurrentStatus {
    TRIM_NONE,
    TRIM_START,
    TRIM_END,
    TRIM_PREVIEW,
};

class TrimDataThread : public BaseThread, PreviewableThread {
  public:
    TrimDataThread(wxEvtHandler *parent, DataPtr data);
    ~TrimDataThread();

    ThreadID getID() const override;

    void processTrimData();

    void incrementStartPos();
    void decrementStartPos();

    bool isStartIncrementable();
    bool isStartDecrementable();

    void incrementEndPos();
    void decrementEndPos();

    bool isEndIncrementable();
    bool isEndDecrementable();

    void setStatus(TrimDataThreadCurrentStatus status);
    TrimDataThreadCurrentStatus getStatus();

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_TRIM_DATA;

    const int MILLI_SLEEP = 100;

    TrimDataThreadCurrentStatus status =
        TrimDataThreadCurrentStatus::TRIM_START;

    std::mutex m_mutex;

    int startPos = -1;
    int endPos = -1;

    const int MAX_FRAME;
    const int MIN_ALLOWED_FRAME = 5;

    int getFrameRange();
};