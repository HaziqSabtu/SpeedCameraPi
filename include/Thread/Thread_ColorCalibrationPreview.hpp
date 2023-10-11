#pragma once

#include "Model/ExtraModel.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_Base.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Preview.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Utils/Camera/CameraBase.hpp>

#include <memory>
#include <string>

#include <opencv2/opencv.hpp>

#include <wx/thread.h>

#define ColorRange std::pair<cv::Scalar, cv::Scalar>

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

    // CCModelPtr ccExtraModel;
};
