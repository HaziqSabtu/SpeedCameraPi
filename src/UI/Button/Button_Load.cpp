#include <UI/Button/Button_Load.hpp>

ButtonLoad::ButtonLoad(wxWindow *parent, wxWindowID id,
                       std::vector<ImageData> *imgData, ThreadPool *pool)
    : ButtonWState(parent, id, "Load", "Loading", "Load", false),
      loadThread(nullptr), imgData(imgData), pool(pool) {
    Bind(wxEVT_BUTTON, &ButtonLoad::OnButton, this);

    std::unique_ptr<AppConfig> config = std::make_unique<AppConfig>();
    filePath = config->GetLoadFileName();
}

ButtonLoad::~ButtonLoad() { clearPointer(); }

void ButtonLoad::OnButton(wxCommandEvent &e) {
    state ? stopLoad() : startLoad();
    toggleState();
    e.Skip();
}

void ButtonLoad::render() {
    state ? Enable() : Disable();
    ButtonWState::render();
}

void ButtonLoad::startLoad() {
    clearPointer();
    loadThread = new LoadFileThread(this, pool, imgData, filePath);
    loadThread->Run();
}

void ButtonLoad::stopLoad() { clearPointer(); }

void ButtonLoad::clearPointer() {
    if (loadThread != nullptr) {
        loadThread->Delete();
        loadThread->Wait();
        delete loadThread;
        loadThread = nullptr;
    }
}