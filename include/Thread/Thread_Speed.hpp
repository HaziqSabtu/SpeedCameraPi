#ifndef SPEED_CALCULATION_THREAD_HPP
#define SPEED_CALCULATION_THREAD_HPP

#include <Algorithm/speed_calculation/speedCalculation.hpp>
#include <Event/Event_Speed.hpp>
#include <Utils/DataStruct.hpp>
#include <Utils/Struct/D_Line.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <wx/thread.h>

class SpeedThread : public wxThread {
  public:
    SpeedThread(wxEvtHandler *parent, std::vector<ImageData> *imgData,
                std::vector<Detection::Line> &selectedLine);
    ~SpeedThread();

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *m_parent;
    std::vector<ImageData> *imgData;
    std::vector<Detection::Line> selectedLine;
};

#endif