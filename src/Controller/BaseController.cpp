#include <Controller/BaseController.hpp>

BaseController::BaseController(ModelPtr sharedModel) : shared(sharedModel) {}

BaseController::~BaseController() {}

void BaseController::e_UpdateState(wxEvtHandler *parent) {
    try {
        AppState state(shared);
        UpdateStateEvent::Submit(parent, state);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void BaseController::e_PanelShow(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        panelShowHandler(parent);
        e_UpdateState(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void BaseController::e_CreateTempSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        createTempSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void BaseController::e_RestoreSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        restoreSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void BaseController::e_SaveSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        saveSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void BaseController::e_OKButtonHandler(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        okButtonHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void BaseController::e_CancelButtonHandler(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        cancelButtonHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

void BaseController::checkPreCondition() {
    auto data = shared->getSessionData();
    if (panelID != data->getPanelID()) {
        throw std::runtime_error("PanelID mismatch");
    }
}

void BaseController::panelShowHandler(wxEvtHandler *parent) {
    createTempSessionDataHandler(parent);
}

void BaseController::createTempSessionDataHandler(wxEvtHandler *parent) {
    auto temp = shared->getTempSessionData();

    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    auto data = shared->getSessionData();
    shared->setTempSessionData(*data);
}

void BaseController::saveSessionDataHandler(wxEvtHandler *parent) {
    auto temp = shared->getTempSessionData();

    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    shared->setTempSessionData(SessionData());
}

void BaseController::restoreSessionDataHandler(wxEvtHandler *parent) {
    auto temp = shared->getTempSessionData();

    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    shared->setSessionData(*temp);
}

void BaseController::okButtonHandler(wxEvtHandler *parent) {

    killAllThreads(parent);

    saveSessionDataHandler(parent);

    ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
    ChangePanelEvent::Submit(parent, data);
}

void BaseController::cancelButtonHandler(wxEvtHandler *parent) {

    if (shared->isSessionDataChanged()) {
        auto dialog = CancelDialog(nullptr);
        if (dialog.ShowModal() == wxID_NO) {
            return;
        }
    }

    killAllThreads(parent);

    restoreSessionDataHandler(parent);

    ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
    ChangePanelEvent::Submit(parent, data);
}