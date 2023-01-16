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

void LaneDetectionPanelImage::SetFirstImage(cv::Mat firstImg) {
    this->firstImg = firstImg;
    img_bitmap->SetImage(firstImg);
}

void LaneDetectionPanelImage::SetROIPoints(
    std::vector<std::vector<cv::Point2f>> roiPoints) {
    this->roiPoints = roiPoints;
}

void LaneDetectionPanelImage::RunLaneDetection() {
    laneDetection->process(imgData[count].image, roiPoints);
    GenerateImage();
}

void LaneDetectionPanelImage::GenerateImage() {
    cv::Mat generatedImg =
        laneDetection->generateComplexImage(IMAGE_TO_GENERATE, IMAGE_PER_ROW);
    if (generatedImg.size().width != firstImg.size().width) {
        cv::resize(generatedImg, generatedImg, firstImg.size());
    }
    img_bitmap->SetImage(generatedImg);
    img_bitmap->RefreshBitmap();
}

void LaneDetectionPanelImage::OnIncrement() {
    imgC += IMAGE_TO_GENERATE;
    laneDetection->setImgGenCount(imgC);
    GenerateImage();
}

void LaneDetectionPanelImage::OnDecrement() {
    imgC -= IMAGE_TO_GENERATE;
    laneDetection->setImgGenCount(imgC);
    GenerateImage();
}
// clang-format off
BEGIN_EVENT_TABLE(LaneDetectionPanelImage, wxPanel)
EVT_SIZE(LaneDetectionPanelImage::OnSize)
END_EVENT_TABLE()
