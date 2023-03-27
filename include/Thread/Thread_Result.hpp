/**
 * @file Thread_Result.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom wxThread for displaying result
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef RESULT_THREAD_HPP
#define RESULT_THREAD_HPP

#include <Event/Event_UpdateImage.hpp>
#include <Utils/DataStruct.hpp>
#include <wx/thread.h>
#include <wx/wx.h>

/**
 * @brief Custom wxThread for displaying result
 *
 */
class ResultThread : public wxThread {
  public:
    ResultThread(wxEvtHandler *parent, std::vector<ImageData> *imgData);
    ~ResultThread();

  protected:
    virtual ExitCode Entry();

  private:
    wxEvtHandler *parent;
    std::vector<ImageData> *imgData;
};

#endif