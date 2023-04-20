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

#ifndef LOAD_FILE_THREAD_HPP
#define LOAD_FILE_THREAD_HPP

#include <Event/Event_Error.hpp>
#include <Event/Event_LoadImage.hpp>
#include <Event/Event_UpdatePreview.hpp>

#include <Thread/Task/Task_Load.hpp>
#include <Thread/ThreadPool.hpp>

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
class LoadFileThread : public wxThread {
  public:
    LoadFileThread(wxEvtHandler *parent, std::shared_ptr<ThreadPool> pool,
                   std::shared_ptr<std::vector<ImageData>> imgData,
                   std::string path, const int maxFrame);
    ~LoadFileThread();

  protected:
    ExitCode Entry();

  private:
    wxEvtHandler *parent;
    std::shared_ptr<std::vector<ImageData>> imgData;
    std::shared_ptr<ThreadPool> pool;
    std::string path;
    const int maxFrame;
};

#endif