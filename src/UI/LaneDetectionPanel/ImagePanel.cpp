#include <UI/LaneDetectionPanel/ImagePanel.hpp>

LaneDetectionPanelImage::LaneDetectionPanelImage(
    wxWindow *parent, wxWindowID id, const std::vector<ImgData> &imgData)
    : wxPanel(parent, id) {
    this->imgData = imgData;
    cv::Mat firstImg = imgData[count].image;

    img_bitmap = new BBLaneD(this, wxID_ANY);
    img_bitmap->SetImage(firstImg);

    laneDetection = new LaneDetectionAlgorithm();
}

void LaneDetectionPanelImage::OnSize(wxSizeEvent &e) {
    wxSize this_size = e.GetSize();
    img_bitmap->SetClientSize(this_size);
}

void LaneDetectionPanelImage::SetCount(int count) {
    this->count = count;
    img_bitmap->SetImage(imgData[count].image);
}

void LaneDetectionPanelImage::SetROIPoints(
    std::vector<std::vector<cv::Point2f>> roiPoints) {
    this->roiPoints = roiPoints;
}

void LaneDetectionPanelImage::RunLaneDetection() {
    laneDetection->process(imgData[count].image, roiPoints);
    wxMessageBox("Lane Detection Done");
}

// clang-format off
BEGIN_EVENT_TABLE(LaneDetectionPanelImage, wxPanel)
EVT_SIZE(LaneDetectionPanelImage::OnSize)
END_EVENT_TABLE()
