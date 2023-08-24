/**
 * @file Thread_LoadFile.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom wxThread for loading ImageData from file
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "Model/SessionData.hpp"
#include "Thread/Thread_ID.hpp"
#include <Event/Event_Error.hpp>
#include <Event/Event_LoadImage.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Thread/ThreadPool.hpp>

#include <Utils/FileReader/fileWR.hpp>
#include <Utils/wxUtils.hpp>

#include <memory>
#include <opencv2/opencv.hpp>

#include <wx/string.h>
#include <wx/thread.h>
#include <wx/wx.h>

/**
 * @brief Custom wxThread for loading ImageData from file
 *
 */
class SaveDataThread : public wxThread {
  public:
    SaveDataThread(wxEvtHandler *parent, DataPtr data);
    ~SaveDataThread();

    ThreadID getID() const;

  protected:
    ExitCode Entry();

  private:
    wxEvtHandler *parent;
    DataPtr data;

    const ThreadID id = THREAD_SAVE_FILE;
};
