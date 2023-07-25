#include <Model/RoiModel.hpp>

RoiModel::RoiModel(std::shared_ptr<SharedModel> sharedModel)
    : shared(sharedModel) {
    initThreads();
}

RoiModel::~RoiModel() {
    try {
        deleteThreads();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void RoiModel::initThreads() { processThread = nullptr; }

void RoiModel::deleteThreads() {
    processThread = stopAndDeleteThread(processThread);
}

void RoiModel::endPoint(wxEvtHandler *parent, PanelID panelID, wxRect rect) {
    try {

        if (panelID != shared->sessionData.currentPanelID) {
            throw std::runtime_error("RoiModel::endPoint() - PanelID mismatch");
        }

        if (panelID == PANEL_ROI) {
            int x = rect.GetX();
            int y = rect.GetY();
            int width = rect.GetWidth();
            int height = rect.GetHeight();
            shared->sessionData.updateRoiData(x, y, width, height);

            std::cout << "Update Success" << std::endl;
            shared->sessionData.roiData.Info();
        }
    } catch (std::exception &e) {
        ErrorEvent errorEvent(c_ERROR_EVENT, wxID_ANY);
        errorEvent.SetErrorData(e.what());
        wxPostEvent(parent, errorEvent);
    }
}

// void RoiModel::endPoint(wxEvtHandler *parent, ModelEnum::ModelIDs id) {
//     try {

//         if (panelID != shared->sessionData.currentPanelID) {
//             throw std::runtime_error("RoiModel::endPoint() - PanelID mismatch");
//         }

//         if (id == ModelEnum::MODEL_START_PROCESS) {
//             startProcessHandler(parent);
//             return;
//         }

//         throw std::runtime_error("Model::endPoint() - Invalid EndPoint");

//     } catch (std::exception &e) {
//         ErrorEvent errorEvent(c_ERROR_EVENT, wxID_ANY);
//         errorEvent.SetErrorData(e.what());
//         wxPostEvent(parent, errorEvent);
//     }
// }

void RoiModel::startProcessHandler(wxEvtHandler *parent) {
    if (processThread != nullptr) {
        throw std::runtime_error("ProcessThread is already running");
    }

    if (shared->sessionData.isImageDataEmpty()) {
        throw std::runtime_error("imageData is empty");
    }

    processThread = new ProcessThread(parent, shared->getThreadPool(),
                                      shared->sessionData.imageData);
    processThread->Run();
}

template <typename T>
T *RoiModel::stopAndDeleteThread(T *threadPtr) {
    if (threadPtr == nullptr) {
        return nullptr;
    }

    threadPtr->Delete();
    delete threadPtr;
    threadPtr = nullptr;

    return threadPtr;
}