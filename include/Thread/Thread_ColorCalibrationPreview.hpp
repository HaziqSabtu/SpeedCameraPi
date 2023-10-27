#pragma once

#include <Thread/Thread_Base.hpp>

#include <Utils/Camera/CameraBase.hpp>

#define ColorRange std::pair<cv::Scalar, cv::Scalar>

/**
 * @brief Thread implementation for Preview the result from
 * ColorCalibrationThread
 *
 */
class ColorCalibrationPreviewThread : public BaseThread,
                                      public PreviewableThread,
                                      public CameraAccessor {
  public:
    ColorCalibrationPreviewThread(wxEvtHandler *parent, CameraPtr &camera,
                                  const ColorRange &blueRange,
                                  const ColorRange &yellowRange);
    ~ColorCalibrationPreviewThread();

    ThreadID getID() const override;

  protected:
    virtual ExitCode Entry() override;

    bool isCalibrationComplete();

  private:
    const ThreadID id = THREAD_COLOR_CALIBRATION_PREVIEW;

    ColorRange blueRange;
    ColorRange yellowRange;
};
