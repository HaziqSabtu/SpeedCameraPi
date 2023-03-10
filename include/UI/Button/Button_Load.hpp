#ifndef BUTTON_LOAD_HPP
#define BUTTON_LOAD_HPP

#include <Thread/ThreadPool.hpp>
#include <Thread/Thread_LoadFile.hpp>
#include <UI/Button/Button_wState.hpp>
#include <Utils/Config/AppConfig.hpp>
#include <Utils/DataStruct.hpp>

#include <memory>

class ButtonLoad : public ButtonWState {
  public:
    ButtonLoad(wxWindow *parent, wxWindowID id, std::vector<ImageData> *imgData,
               ThreadPool *pool);
    ~ButtonLoad();

  private:
    void OnButton(wxCommandEvent &e) override;

    void startLoad();
    void stopLoad();
    void clearPointer();

    void render() override;
    std::vector<ImageData> *imgData;
    ThreadPool *pool;
    wxString filePath;
    LoadFileThread *loadThread;
};

#endif