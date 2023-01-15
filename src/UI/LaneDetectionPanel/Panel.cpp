#include <UI/LaneDetectionPanel/Panel.hpp>

LaneDetectionPanel::LaneDetectionPanel(wxWindow *parent, wxWindowID id,
                                       const std::vector<ImgData> &imgData)
    : wxPanel(parent, id) {

    button_panel = new LaneDetectionPanelButton(this, Enum::LD_BUTTON_PANEL_ID);
    img_panel =
        new LaneDetectionPanelImage(this, Enum::LD_IMG_PANEL_ID, imgData);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_panel, 1, wxEXPAND);

    SetSizer(main_sizer);
    Fit();

    SetFocus();
}

void LaneDetectionPanel::OnPageChange() {
    OpticalFlowPanelImage *img_panel_of = dynamic_cast<OpticalFlowPanelImage *>(
        GetParent()->FindWindow(Enum::OF_IMG_PANEL_ID));

    int count = img_panel_of->GetCount();
    img_panel->SetCount(count);

    std::vector<std::vector<PointData>> roiData = img_panel_of->GetRoiData();
    std::vector<std::vector<cv::Point2f>> roiPoints =
        std::vector<std::vector<cv::Point2f>>(roiData.size());
    // set only points variable
    for (int i = 0; i < roiData.size(); i++) {
        roiPoints[i] = std::vector<cv::Point2f>(roiData[i].size());
        for (int j = 0; j < roiData[i].size(); j++) {
            roiPoints[i][j] = roiData[i][j].point;
        }
    }
    img_panel->SetROIPoints(roiPoints);

    // wxMessageBox("Lane Detection Panel: OnPageChange()");
}

// clang-format off
BEGIN_EVENT_TABLE(LaneDetectionPanel, wxPanel)
END_EVENT_TABLE()
