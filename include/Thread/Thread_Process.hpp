/**
 * @file Thread_Process.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom wxThread for processing ImageData
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef PROCESS_THREAD_HPP
#define PROCESS_THREAD_HPP

#include <Thread/ThreadPool.hpp>
#include <Thread/Thread_Base.hpp>
#include <Utils/Algorithm/AlgorithmFactory.hpp>

/**
 * @brief Custom wxThread for processing ImageData
 *
 */
class ProcessThread : public BaseThread {
  public:
    ProcessThread(wxEvtHandler *parent, DataPtr data, DetectorPtr detector,
                  TrackerPtr tracker, SpeedCalcPtr speedCalc,
                  POOLPtr threadPool);
    ~ProcessThread();

    ThreadID getID() const override;

  protected:
    virtual ExitCode Entry() override;

  private:
    const ThreadID threadID = ThreadID::THREAD_PROCESS;

    POOLPtr pool;
    SpeedCalcPtr speedCalc;
    TrackerPtr tracker;
    DetectorPtr detector;
};

#endif