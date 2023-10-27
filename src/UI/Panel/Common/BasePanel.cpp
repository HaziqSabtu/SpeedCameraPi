#include <UI/Panel/Common/BasePanel.hpp>

/**
 * @brief Construct a new Base Panel:: Base Panel object
 *
 * @param parent Pointer to parent window
 * @param id Window ID
 * @param controller Pointer to BaseController
 */
BasePanel::BasePanel(wxWindow *parent, wxWindowID id, BSCPtr controller)
    : wxPanel(parent, id), controller(controller) {

    img_bitmap = new BaseImagePanel(this);
    status_panel = new StatusPanel(this);

    Hide();
}

/**
 * @brief Destroy the Base Panel:: Base Panel object
 *
 */
BasePanel::~BasePanel() {}

/**
 * @brief Properly set the size of the panel
 *
 */
void BasePanel::size() {
    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(title_panel, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(img_bitmap, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(status_panel, 0, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(button_panel, 1, wxEXPAND | wxALL, 10);

    SetSizer(main_sizer);
    Fit();
}

/**
 * @brief Handle button events
 *
 * @param e Event
 */
void BasePanel::OnButton(wxCommandEvent &e) {

    if (e.GetId() == Enum::G_Cancel_Button_ID) {
        controller->e_CancelButtonHandler(this);
    }

    if (e.GetId() == Enum::G_OK_Button_ID) {
        controller->e_OKButtonHandler(this);
    }

    controller->e_UpdateState(this);

    e.Skip();
}

/**
 * @brief Handle preview update events
 *
 * @param e Event
 */
void BasePanel::OnUpdatePreview(UpdatePreviewEvent &e) {
    if (e.GetId() == UPDATE_PREVIEW) {
        wxBitmap image = e.GetImage();
        img_bitmap->setImage(image);
    }

    if (e.GetId() == CLEAR_PREVIEW) {
        img_bitmap->setNoImage();
    }

    e.Skip();
}

/**
 * @brief Handle state update events
 *
 * @param e Event
 */
void BasePanel::OnUpdateState(UpdateStateEvent &e) {
    try {
        auto state = e.GetState();
        button_panel->update(state);

        Refresh();
        Layout();
    } catch (const std::exception &e) {
        ErrorEvent::Submit(this, e.what());
    }
}

/**
 * @brief Handle status update events
 *
 * @param e Event
 */
void BasePanel::OnUpdateStatus(UpdateStatusEvent &e) {
    try {
        auto status = e.GetStatus();
        status_panel->SetText(status);
        Refresh();
    } catch (const std::exception &e) {
        ErrorEvent::Submit(this, e.what());
    }
}

/**
 * @brief Handle show events
 *
 * @param e Event
 */
void BasePanel::OnShow(wxShowEvent &e) {
    if (e.IsShown()) {
        status_panel->SetText(SC::STATUS_IDLE);
        controller->e_PanelShow(this);
    }
}

/**
 * @brief Handle request update state events
 *
 * @param e Event
 */
void BasePanel::OnRequestUpdateState(wxCommandEvent &e) {
    if (e.GetId() == REQUEST_UPDATE_STATE) {
        controller->e_UpdateState(this);
    }
}

/**
 * @brief Construct a new Base Panel With Touch:: Base Panel With Touch object
 *
 * @param parent Pointer to parent window
 * @param id Window ID
 * @param controller Pointer to BaseControllerWithTouch
 */
BasePanelWithTouch::BasePanelWithTouch(wxWindow *parent, wxWindowID id,
                                       BTCPtr controller)
    : BasePanel(parent, id, controller), controller(controller) {}

/**
 * @brief Destroy the Base Panel With Touch:: Base Panel With Touch object
 *
 */
BasePanelWithTouch::~BasePanelWithTouch() {}

/**
 * @brief Bind left down event
 *
 */
void BasePanelWithTouch::bindLeftDown() {
    img_bitmap->Bind(wxEVT_LEFT_DOWN, &BasePanelWithTouch::OnLeftDown, this);
}

/**
 * @brief Bind motion event
 *
 */
void BasePanelWithTouch::bindMotion() {
    img_bitmap->Bind(wxEVT_MOTION, &BasePanelWithTouch::OnMotion, this);
}

/**
 * @brief Bind left up event
 *
 */
void BasePanelWithTouch::bindLeftUp() {
    img_bitmap->Bind(wxEVT_LEFT_UP, &BasePanelWithTouch::OnLeftUp, this);
}

/**
 * @brief Bind all events (left down, motion, left up)
 *
 */
void BasePanelWithTouch::bindAll() {
    img_bitmap->Bind(wxEVT_LEFT_DOWN, &BasePanelWithTouch::OnLeftDown, this);
    img_bitmap->Bind(wxEVT_MOTION, &BasePanelWithTouch::OnMotion, this);
    img_bitmap->Bind(wxEVT_LEFT_UP, &BasePanelWithTouch::OnLeftUp, this);
}

/**
 * @brief Unbind left down event
 *
 */
void BasePanelWithTouch::unBindLeftDown() {
    img_bitmap->Unbind(wxEVT_LEFT_DOWN, &BasePanelWithTouch::OnLeftDown, this);
}

/**
 * @brief Unbind motion event
 *
 */
void BasePanelWithTouch::unBindMotion() {
    img_bitmap->Unbind(wxEVT_MOTION, &BasePanelWithTouch::OnMotion, this);
}

/**
 * @brief Unbind left up event
 *
 */
void BasePanelWithTouch::unBindLeftUp() {
    img_bitmap->Unbind(wxEVT_LEFT_UP, &BasePanelWithTouch::OnLeftUp, this);
}

/**
 * @brief Unbind all events (left down, motion, left up)
 *
 */
void BasePanelWithTouch::unBindAll() {
    img_bitmap->Unbind(wxEVT_LEFT_DOWN, &BasePanelWithTouch::OnLeftDown, this);
    img_bitmap->Unbind(wxEVT_LEFT_UP, &BasePanelWithTouch::OnLeftUp, this);
    img_bitmap->Unbind(wxEVT_MOTION, &BasePanelWithTouch::OnMotion, this);
}

/**
 * @brief Handle left down event
 *
 * @param e Event
 */
void BasePanelWithTouch::OnLeftDown(wxMouseEvent &e) {
    wxPoint pos = e.GetPosition();
    wxSize size = img_bitmap->GetSize();
    wxSize img_size = img_bitmap->getImageSize();

    if (pos.x > 0 && pos.x < size.x && pos.y > 0 && pos.y < size.y) {
        if (img_size.x > 0 && img_size.y > 0) {
            int x = pos.x * img_size.x / size.x;
            int y = pos.y * img_size.y / size.y;
            controller->e_LeftDown(this, wxPoint(x, y));

            doPostLeftDown();
        }
    }
}

/**
 * @brief Handle motion event
 *
 * @param e Event
 */
void BasePanelWithTouch::OnMotion(wxMouseEvent &e) {
    wxPoint pos = e.GetPosition();
    wxSize size = img_bitmap->GetSize();
    wxSize img_size = img_bitmap->getImageSize();

    if (pos.x > 0 && pos.x < size.x && pos.y > 0 && pos.y < size.y) {
        if (img_size.x > 0 && img_size.y > 0) {
            int x = pos.x * img_size.x / size.x;
            int y = pos.y * img_size.y / size.y;
            controller->e_LeftMove(this, wxPoint(x, y));

            doPostMotion();
        }
    }
}

/**
 * @brief Handle left up event
 *
 * @param e Event
 */
void BasePanelWithTouch::OnLeftUp(wxMouseEvent &e) {
    wxPoint pos = e.GetPosition();
    wxSize size = img_bitmap->GetSize();
    wxSize img_size = img_bitmap->getImageSize();

    if (pos.x > 0 && pos.x < size.x && pos.y > 0 && pos.y < size.y) {
        if (img_size.x > 0 && img_size.y > 0) {
            int x = pos.x * img_size.x / size.x;
            int y = pos.y * img_size.y / size.y;

            controller->e_LeftUp(this, wxPoint(x, y));

            doPostLeftUp();

            controller->e_UpdateState(this);
        }
    }
}

/**
 * @brief Do post left down
 *
 */
void BasePanelWithTouch::doPostLeftDown() {
    unBindLeftDown();
    bindLeftUp();
    bindMotion();
}

/**
 * @brief Do post motion
 *
 */
void BasePanelWithTouch::doPostMotion() {
    // do nothing
}

/**
 * @brief Do post left up
 *
 */
void BasePanelWithTouch::doPostLeftUp() {
    unBindMotion();
    unBindLeftUp();
    bindLeftDown();
}

// clang-format off
BEGIN_EVENT_TABLE(BasePanelWithTouch, BasePanel)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(BasePanel, wxPanel)
    EVT_BUTTON(wxID_ANY, BasePanel::OnButton)
    EVT_UPDATE_PREVIEW(wxID_ANY, BasePanel::OnUpdatePreview)
    EVT_UPDATE_STATUS(wxID_ANY, BasePanel::OnUpdateStatus)
    EVT_UPDATE_STATE(wxID_ANY, BasePanel::OnUpdateState)	
    EVT_SHOW(BasePanel::OnShow)
    EVT_COMMAND(wxID_ANY, c_REQUEST_UPDATE_STATE_EVENT, BasePanel::OnRequestUpdateState)
END_EVENT_TABLE()

