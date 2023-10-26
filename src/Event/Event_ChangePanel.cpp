/**
 * @file Event_ChangePanel.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom Event for Changing Panel
 * @version 1.0.0
 * @date 2023-10-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Event/Event_ChangePanel.hpp>

wxDEFINE_EVENT(c_CHANGE_PANEL_EVENT, ChangePanelEvent);

/**
 * @brief Construct a new Change Panel Event:: Change Panel Event object
 *
 * @param eventType
 * @param id Enum of CHANGE_PANEL_EVENT_TYPE
 */
ChangePanelEvent::ChangePanelEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

/**
 * @brief Construct a new Change Panel Event:: Change Panel Event object
 *
 * @param e
 */
ChangePanelEvent::ChangePanelEvent(const ChangePanelEvent &e)
    : wxCommandEvent(e) {
    this->SetPanelData(e.GetPanelData());
}

/**
 * @brief Clone this Event
 *
 * @return wxEvent*
 */
wxEvent *ChangePanelEvent::Clone() const { return new ChangePanelEvent(*this); }

/**
 * @brief Setting Panel Data
 *
 * @param data
 */
void ChangePanelEvent::SetPanelData(const ChangePanelData &data) {
    this->panelData = data;
}

/**
 * @brief Getting Panel Data
 *
 * @return ChangePanelData
 */
ChangePanelData ChangePanelEvent::GetPanelData() const {
    return this->panelData;
}

/**
 * @brief Submitting this Event
 *
 * @param parent View Panel
 * @param data
 * @param id
 */
void ChangePanelEvent::Submit(wxEvtHandler *parent, const ChangePanelData &data,
                              int id) {
    ChangePanelEvent event(c_CHANGE_PANEL_EVENT, id);
    event.SetPanelData(data);
    wxPostEvent(parent, event);
}