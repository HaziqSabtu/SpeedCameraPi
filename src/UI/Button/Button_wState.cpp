#include <UI/Button/Button_wState.hpp>

ButtonWState::ButtonWState(wxWindow *parent, wxWindowID id,
                           const wxString &label, bool initState,
                           const wxPoint &pos, const wxSize &size, long style,
                           const wxValidator &validator, const wxString &name)
    : DefaultButton(parent, id, label, pos, size, style, validator, name),
      state(initState) {
    activeText = "Hide " + label;
    inactiveText = "Show " + label;
    render();
}

ButtonWState::ButtonWState(wxWindow *parent, wxWindowID id,
                           const wxString &label, const wxString &activeText,
                           const wxString &inactiveText, bool initState,
                           const wxPoint &pos, const wxSize &size, long style,
                           const wxValidator &validator, const wxString &name)
    : DefaultButton(parent, id, label, pos, size, style, validator, name),
      state(initState), activeText(activeText), inactiveText(inactiveText) {
    render();
}

ButtonWState::~ButtonWState() {}

void ButtonWState::render() {
    state ? SetLabel(activeText) : SetLabel(inactiveText);
}

void ButtonWState::toggleState() {
    state = !state;
    render();
}

bool ButtonWState::GetState() { return state; }
