
ButtonLoad::ButtonLoad(wxWindow *parent, wxWindowID id)
    : ButtonWState(parent, id, "Load", "Loading", "Load", false) {
    Bind(wxEVT_BUTTON, &ButtonLoad::OnButton, this);
    Bind(c_LOAD_IMAGE_EVENT, &ButtonLoad::OnLoadImage, this);
}

ButtonLoad::~ButtonLoad() {}

void ButtonLoad::OnButton(wxCommandEvent &e) {
    toggleState();
    e.Skip();
}

void ButtonLoad::OnLoadImage(wxCommandEvent &e) {

    if (e.GetId() == LOAD_END_FILE) {
        state = false;
    }

    render();
    e.Skip();
}

void ButtonLoad::render() {
    // state ? Enable() : Disable();
    ButtonWState::render();
}