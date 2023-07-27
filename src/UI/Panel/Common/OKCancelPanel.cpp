#include "Utils/Enum.hpp"
#include <UI/Button/TextButton/Button_Accept.hpp>
#include <UI/Button/TextButton/Button_Cancel.hpp>
#include <UI/Panel/Common/OKCancelPanel.hpp>

OKCancelPanel::OKCancelPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY) {
    OKButton = new AcceptTextButton(this, Enum::G_OK_Button_ID);
    CancelButton = new CancelTextButton(this, Enum::G_Cancel_Button_ID);

    main_sizer = new wxBoxSizer(wxHORIZONTAL);
    main_sizer->Add(CancelButton, 1, wxEXPAND | wxRIGHT, 10);
    main_sizer->Add(OKButton, 1, wxEXPAND);

    SetSizer(main_sizer);
    Fit();
}

OKCancelPanel::~OKCancelPanel() {}

void OKCancelPanel::update(ButtonState okButtonState,
                           ButtonState cancelButtonState) {
    OKButton->update(okButtonState);
    CancelButton->update(cancelButtonState);
}