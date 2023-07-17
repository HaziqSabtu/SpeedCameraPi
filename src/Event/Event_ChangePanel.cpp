#include <Event/Event_ChangePanel.hpp>

wxDEFINE_EVENT(c_CHANGE_PANEL_EVENT, ChangePanelEvent);

ChangePanelEvent::ChangePanelEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

ChangePanelEvent::ChangePanelEvent(const ChangePanelEvent &e)
    : wxCommandEvent(e) {
    this->SetPanelData(e.GetPanelData());
}

wxEvent *ChangePanelEvent::Clone() const { return new ChangePanelEvent(*this); }

void ChangePanelEvent::SetPanelData(const ChangePanelData &data) {
    this->panelData = data;
}

ChangePanelData ChangePanelEvent::GetPanelData() const {
    return this->panelData;
}