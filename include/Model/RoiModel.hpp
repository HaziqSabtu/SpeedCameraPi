#pragma once

#include "Model/SessionData.hpp"
#include <Model/SharedModel.hpp>

class RoiModel {
  public:
    RoiModel(std::shared_ptr<SharedModel> sharedModel);
    ~RoiModel();

    void endPoint(wxEvtHandler *parent, PanelID panelID, wxRect rect);
    void endPoint(wxEvtHandler *parent, ModelEnum::ModelIDs id);

  private:
    const PanelID panelID = PanelID::PANEL_ROI;

    std::shared_ptr<SharedModel> shared;

    ProcessThread *processThread;

    void initThreads();
    void deleteThreads();

    void startProcessHandler(wxEvtHandler *parent);

    void switchPanelHandler(wxEvtHandler *parent);
    bool isRequirementFulfilled();

    template <typename T>
    T *stopAndDeleteThread(T *threadPtr);
};