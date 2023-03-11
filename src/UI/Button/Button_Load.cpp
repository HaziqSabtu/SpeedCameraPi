#include <UI/Button/Button_Load.hpp>

ButtonLoad::ButtonLoad(wxWindow *parent, wxWindowID id, ThreadPool *pool)
    : ButtonWState(parent, id, "Load", "Loading", "Load", false),
      loadThread(nullptr), pool(pool) {
    Bind(wxEVT_BUTTON, &ButtonLoad::OnButton, this);
    Bind(c_CAPTURE_IMAGE_EVENT, &ButtonLoad::OnCaptureImage, this);
    std::unique_ptr<AppConfig> config = std::make_unique<AppConfig>();
    filePath = config->GetLoadFileName();
}

ButtonLoad::~ButtonLoad() {
    clearPointer();
    pool = nullptr;
}

void ButtonLoad::OnButton(wxCommandEvent &e) {
    state ? stopLoad() : startLoad();
    toggleState();
    e.Skip();
}

void ButtonLoad::OnCaptureImage(CaptureImageEvent &e) {
    if (e.GetId() == CAPTURE_START) {
        Disable();
    } else if (e.GetId() == CAPTURE_END) {
        Enable();
        toggleState();
    }
    e.Skip();
}

void ButtonLoad::render() {
    // state ? Enable() : Disable();
    ButtonWState::render();
}

void ButtonLoad::startLoad() {
    clearPointer();
    loadThread = new LoadFileThread(this, pool, filePath);
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