/**
 * @file Event_ChangePanel.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom Event for Changing Panel
 * @version 1.0.0
 * @date 2023-10-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "Model/SessionData.hpp"
#include <wx/event.h>

/**
 * @brief DataEvent for Changing Panel
 * @details Contains PanelID for current and next Panel
 *
 */

class ChangePanelEvent;
wxDECLARE_EVENT(c_CHANGE_PANEL_EVENT, ChangePanelEvent);

/**
 * @brief Enum for Changing Panel
 * @details
 * <table>
 * <tr>
 *  <th>Enum</th>
 *  <th>Event</th>
 * </tr>
 * <tr>
 *   <td>CHANGE_OK</td>
 *   <td>Event for Signaling Changing Panel is Successful</td>
 * </tr>
 * <tr>
 *   <td>CHANGE_ERROR</td>
 *   <td>Event for Signaling Changing Panel is Unsuccessful</td>
 * </tr>
 * </table>
 *
 */
enum CHANGE_PANEL_EVENT_TYPE { CHANGE_OK = 1, CHANGE_ERROR };

/**
 * @brief Custom Data for Changing Panel
 *
 */
struct ChangePanelData {
    PanelID currentPanelID;
    PanelID nextPanelID;

    ChangePanelData() : currentPanelID(PANEL_NONE), nextPanelID(PANEL_NONE) {}

    ChangePanelData(PanelID currentPanelID, PanelID nextPanelID)
        : currentPanelID(currentPanelID), nextPanelID(nextPanelID) {}
};

class ChangePanelEvent : public wxCommandEvent {
  public:
    static void Submit(wxEvtHandler *parent, const ChangePanelData &data,
                       int id = 1);

  public:
    ChangePanelEvent(wxEventType eventType = c_CHANGE_PANEL_EVENT, int id = 1);
    ChangePanelEvent(const ChangePanelEvent &e);
    virtual wxEvent *Clone() const;

    void SetPanelData(const ChangePanelData &data);

    ChangePanelData GetPanelData() const;

  private:
    ChangePanelData panelData;
};

typedef void (wxEvtHandler::*ChangePanelFunction)(ChangePanelEvent &);
#define ChangePanelHandler(func) wxEVENT_HANDLER_CAST(ChangePanelFunction, func)
#define EVT_CHANGEPANEL(id, func)                                              \
    wx__DECLARE_EVT1(c_CHANGE_PANEL_EVENT, id, ChangePanelHandler(func))
