#pragma once

#include <Thread/Thread_Base.hpp>

/**
 * @brief Thread implementation for the ROI
 *
 */
class RoiThread : public BaseThread, PreviewableThread, ImageSizeDataThread {
  public:
    RoiThread(wxEvtHandler *parent, DataPtr data);
    ~RoiThread();

    ThreadID getID() const override;

    void setPoint1(cv::Point point);
    void setPoint2(cv::Point point);

    bool isRectValid();

    cv::Rect getRect();

    cv::Rect getRealRect();

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_ROI;

    std::mutex m_mutex;

    cv::Point p1 = cv::Point(-1, -1);
    cv::Point p2 = cv::Point(-1, -1);
};