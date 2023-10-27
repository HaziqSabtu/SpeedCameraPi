#include "Utils/Enum.hpp"
#include <UI/Button/TextButton/Button_Accept.hpp>
#include <UI/Button/TextButton/Button_Cancel.hpp>
#include <UI/Button/TextButton/Button_Reset.hpp>
#include <UI/Panel/Common/OKCancelPanel.hpp>

/**
 * @brief Construct a new OKCancel Panel::OKCancel Panel object
 *
 * @param parent Pointer to parent window
 */
OKCancelPanel::OKCancelPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY) {
    OKButton = new AcceptTextButton(this, Enum::G_OK_Button_ID);
    CancelButton = new CancelTextButton(this, Enum::G_Cancel_Button_ID);

    main_sizer = new wxBoxSizer(wxHORIZONTAL);
    main_sizer->Add(CancelButton, 1, wxEXPAND | wxRIGHT, 10);
    main_sizer->Add(OKButton, 1, wxEXPAND);

    SetSizer(main_sizer);
    Fit();
}

/**
 * @brief Destroy the OKCancel Panel::OKCancel Panel object
 *
 */
OKCancelPanel::~OKCancelPanel() {}

/**
 * @brief Update the state of the buttons
 *
 * @param okButtonState State of the OK button
 * @param cancelButtonState State of the Cancel button
 */
void OKCancelPanel::update(ButtonState okButtonState,
                           ButtonState cancelButtonState) {
    OKButton->update(okButtonState);
    CancelButton->update(cancelButtonState);
}

/**
 * @brief Construct a new OKCancelReset Panel::OKCancelReset Panel object
 *
 * @param parent Pointer to parent window
 */
OKCancelResetPanel::OKCancelResetPanel(wxWindow *parent)
    : OKCancelPanel(parent) {
    ResetButton = new ResetTextButton(this, Enum::G_Reset_Button_ID);

    main_sizer = new wxBoxSizer(wxHORIZONTAL);
    main_sizer->Add(CancelButton, 1, wxEXPAND | wxRIGHT, 10);
    main_sizer->Add(ResetButton, 1, wxEXPAND | wxRIGHT, 10);
    main_sizer->Add(OKButton, 1, wxEXPAND);

    SetSizer(main_sizer);
    Fit();
}

/**
 * @brief Destroy the OKCancelReset Panel::OKCancelReset Panel object
 *
 */
OKCancelResetPanel::~OKCancelResetPanel() {}

void OKCancelResetPanel::update(ButtonState okButtonState,
                                ButtonState cancelButtonState,
                                ButtonState resetButtonState) {
    OKButton->update(okButtonState);
    CancelButton->update(cancelButtonState);
    ResetButton->update(resetButtonState);
}