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

#include <Thread/Thread_Base.hpp>

#include <Utils/FileReader/fileWR.hpp>

/**
 * @brief Custom wxThread for loading ImageData from file
 *
 */
class LoadFileThread : public BaseThread, public PreviewableThread {
  public:
    LoadFileThread(wxEvtHandler *parent, DataPtr data, std::string path);
    ~LoadFileThread();

    ThreadID getID() const override;

  protected:
    ExitCode Entry() override;

  private:
    const ThreadID id = THREAD_LOAD_FILE;

    std::string path;
};

#endif