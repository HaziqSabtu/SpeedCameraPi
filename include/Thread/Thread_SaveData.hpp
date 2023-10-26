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

#include <Thread/Thread_Base.hpp>

#include <Utils/FileReader/fileWR.hpp>

/**
 * @brief Custom wxThread for saving ImageData to file
 *
 */
class SaveDataThread : public BaseThread {
  public:
    SaveDataThread(wxEvtHandler *parent, DataPtr data);
    ~SaveDataThread();

    ThreadID getID() const override;

  protected:
    ExitCode Entry() override;

  private:
    const ThreadID id = THREAD_SAVE_FILE;
};
