#include <Thread/Thread_Speed.hpp>

SpeedThread::SpeedThread(wxEvtHandler *parent, std::vector<ImageData> *imgData,
                         std::vector<Detection::Line> &selectedLine)
    : wxThread(wxTHREAD_JOINABLE), imgData(imgData),
      selectedLine(selectedLine) {
    this->m_parent = parent;
}

SpeedThread::~SpeedThread() {}

wxThread::ExitCode SpeedThread::Entry() {
    std::cout << "Speed Calculation Thread Start" << std::endl;
    SpeedCalculation speedCalc;
    speedCalc.SetImageWidth(imgData->at(0).image.cols);
    std::cout << "Speed Calculation Thread Run" << std::endl;
    speedCalc.runCalculation(imgData, selectedLine);
    SpeedCalcEvent e = SpeedCalcEvent(c_SPEED_CALC_EVENT, CALC_OK);
    e.SetSpeed(speedCalc.GetAvgSpeed());
    wxPostEvent(m_parent, e);
    return 0;
}