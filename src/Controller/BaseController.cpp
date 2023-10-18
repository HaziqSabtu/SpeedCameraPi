#include <Controller/BaseController.hpp>

/**
 * @brief Construct a new Base Controller:: Base Controller object
 *
 * @param shared
 */
BaseController::BaseController(ResourcePtr shared) : shared(shared) {}

/**
 * @brief Destroy the Base Controller:: Base Controller object
 *
 */
BaseController::~BaseController() {}

/**
 * @brief Endpoint to update the state of the application via UpdateStateEvent
 * @details This method is used to update the state of the application. The
 * AppState of the app is created and submitted to the View components via
 * UpdateStateEvent
 *
 * @param parent the parent wxEvtHandler
 */
void BaseController::e_UpdateState(wxEvtHandler *parent) {
    try {
        AppState state(shared);
        UpdateStateEvent::Submit(parent, state);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint when a panel is shown (Do something when a panel is shown)
 *
 * @param parent the parent wxEvtHandler
 */
void BaseController::e_PanelShow(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        panelShowHandler(parent);
        e_UpdateState(parent);

    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to create a copy of SessionData and store it in
 * TempSessionData
 * @details Use case -> User open a panel, change some data, the data is
 * modified directly in SessionData. If the user cancel the operation, the data
 * must be restored to the previous state. This method is used to create a copy
 * of the current SessionData and store it in TempSessionData.
 *
 * @param parent the parent wxEvtHandler
 */
void BaseController::e_CreateTempSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        createTempSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to restore TempSessionData to SessionData
 *
 * @param parent the parent wxEvtHandler
 */
void BaseController::e_RestoreSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        restoreSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint to save TempSessionData to SessionData
 * @details Save the TempSessionData to SessionData. Refer to
 * BaseController::e_CreateTempSessionData() for more details. Used when user
 * press OK or Accept button.
 *
 * @param parent the parent wxEvtHandler
 */
void BaseController::e_SaveSessionData(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        saveSessionDataHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint when OK button is pressed
 *
 * @param parent the parent wxEvtHandler
 */
void BaseController::e_OKButtonHandler(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        okButtonHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint when Cancel button is pressed
 *
 * @param parent
 */
void BaseController::e_CancelButtonHandler(wxEvtHandler *parent) {
    try {
        checkPreCondition();
        cancelButtonHandler(parent);
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Check if the panelID is the same as the current panelID in
 * SessionData. This methods is to be called before any handler is called.
 * Important to prevent any unnecessary request handling when panel is inactive.
 *
 */
void BaseController::checkPreCondition() {
    auto data = shared->getSessionData();
    if (panelID != data->getPanelID()) {
        throw std::runtime_error("PanelID mismatch");
    }
}

/**
 * @brief Handle request from BasePanel::e_PanelShow()
 * @details When a panel is shown, create a copy of SessionData and store it in
 * TempSessionData to enable restore operation.
 *
 * @param parent the parent wxEvtHandler
 */
void BaseController::panelShowHandler(wxEvtHandler *parent) {
    createTempSessionDataHandler(parent);
}

/**
 * @brief Create a copy of SessionData and store it in TempSessionData
 *
 * @param parent
 */
void BaseController::createTempSessionDataHandler(wxEvtHandler *parent) {
    auto temp = shared->getTempSessionData();

    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    auto data = shared->getSessionData();
    shared->setTempSessionData(*data);
}

/**
 * @brief Handle request to save TempSessionData to SessionData
 *
 * @param parent  the parent wxEvtHandler
 */
void BaseController::saveSessionDataHandler(wxEvtHandler *parent) {
    auto temp = shared->getTempSessionData();

    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    shared->setTempSessionData(SessionData());
}

/**
 * @brief Handle request to restore TempSessionData to SessionData
 *
 * @param parent  the parent wxEvtHandler
 */
void BaseController::restoreSessionDataHandler(wxEvtHandler *parent) {
    auto temp = shared->getTempSessionData();

    if (temp == nullptr) {
        throw std::runtime_error("TempSessionData is nullptr");
    }

    shared->setSessionData(*temp);
}

/**
 * @brief Handle request when OK button is pressed
 * @details This method is used to navigate to the other panel. When navigating
 * first must kill all threads (BaseController::killAllThreads()), then save the
 * data to SessionData, and sumbit ChangePanelEvent.
 *
 * @param parent the parent wxEvtHandler
 */
void BaseController::okButtonHandler(wxEvtHandler *parent) {

    killAllThreads(parent);

    saveSessionDataHandler(parent);

    ChangePanelData data(this->panelID, PanelID::PANEL_CAPTURE);
    ChangePanelEvent::Submit(parent, data);
}

/**
 * @brief Handle request when Cancel button is pressed
 * @details This method is used to navigate to the other panel. When navigating
 * first must kill all threads (BaseController::killAllThreads()), then restore
 * the data to SessionData, and sumbit ChangePanelEvent.
 *
 * @param parent the parent wxEvtHandler
 */
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

/**
 * @brief Construct a new Base Controller With Touch:: Base Controller With
 * Touch object
 *
 * @param shared The Shared pointer to SharedResource
 */
BaseControllerWithTouch::BaseControllerWithTouch(ResourcePtr shared)
    : BaseController(shared) {}

/**
 * @brief Destroy the Base Controller With Touch:: Base Controller With Touch
 * object
 *
 */
BaseControllerWithTouch::~BaseControllerWithTouch() {}

/**
 * @brief Endpoint when left mouse button is pressed
 *
 * @param parent the parent wxEvtHandler
 * @param point the point where the mouse is pressed
 */
void BaseControllerWithTouch::e_LeftDown(wxEvtHandler *parent, wxPoint point) {
    try {
        checkPreCondition();
        leftDownHandler(parent, Utils::wxPointToCvPoint(point));
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint when left mouse button is released
 *
 * @param parent the parent wxEvtHandler
 * @param point the point where the mouse is released
 */
void BaseControllerWithTouch::e_LeftUp(wxEvtHandler *parent, wxPoint point) {
    try {
        checkPreCondition();
        leftUpHandler(parent, Utils::wxPointToCvPoint(point));
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}

/**
 * @brief Endpoint when left mouse button is moved
 *
 * @param parent the parent wxEvtHandler
 * @param point the point where the mouse is moved
 */
void BaseControllerWithTouch::e_LeftMove(wxEvtHandler *parent, wxPoint point) {
    try {
        checkPreCondition();
        leftMoveHandler(parent, Utils::wxPointToCvPoint(point));
    } catch (std::exception &e) {
        ErrorEvent::Submit(parent, e.what());
    }
}