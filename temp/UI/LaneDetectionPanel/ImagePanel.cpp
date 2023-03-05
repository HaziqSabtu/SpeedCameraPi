#include <UI/LaneDetectionPanel/ImagePanel.hpp>

LaneDetectionPanelImage::LaneDetectionPanelImage(
    wxWindow *parent, wxWindowID id, const std::vector<ImgData> &imgData)
    : wxPanel(parent, id) {
    this->imgData = imgData;
    cv::Mat firstImg = imgData[count].image;
    wxSize size = wxSize(firstImg.size().width, firstImg.size().height);
    img_bitmap = new BBLaneD(this, wxID_ANY, size);
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

    // * Janky fix for resizing the image due to buffering ?
    if (generatedImg.size().width != firstImg.size().width) {
        cv::resize(generatedImg, generatedImg, firstImg.size());
    }
    img_bitmap->SetImage(generatedImg);
    img_bitmap->RefreshBitmap();
}

void LaneDetectionPanelImage::SetLeftData() {
    if (imgIndex == -1) {
        wxMessageBox("Please select an image");
        return;
    }
    laneDetection->generateEvalDataLeft(imgIndex);
    GenerateImageLeft();
}

void LaneDetectionPanelImage::GenerateImageLeft() {
    cv::Mat generatedImg = laneDetection->generateComplexImageLeft(
        IMAGE_TO_GENERATE, IMAGE_PER_ROW);
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

void LaneDetectionPanelImage::OnLeftDown(wxMouseEvent &e) {
    wxPoint mousePos = e.GetPosition();
    wxMessageBox(wxString::Format("x: %d, y: %d", mousePos.x, mousePos.y));
    wxSize imgSize = img_bitmap->GetSize();
    int rowImg = mousePos.x / (imgSize.GetWidth() / IMAGE_PER_ROW);
    if (rowImg >= IMAGE_PER_ROW - 1) {
        return;
    }
    int colImg = mousePos.y /
                 (imgSize.GetHeight() / (IMAGE_TO_GENERATE / IMAGE_PER_ROW));
    if (colImg >= IMAGE_TO_GENERATE / IMAGE_PER_ROW - 1) {
        return;
    }
    imgIndex = rowImg + colImg * IMAGE_PER_ROW;
    wxMessageBox(wxString::Format("Index: %d", imgIndex));
}
// clang-format off
BEGIN_EVENT_TABLE(LaneDetectionPanelImage, wxPanel)
EVT_SIZE(LaneDetectionPanelImage::OnSize)
EVT_LEFT_DOWN(LaneDetectionPanelImage::OnLeftDown)
END_EVENT_TABLE()
