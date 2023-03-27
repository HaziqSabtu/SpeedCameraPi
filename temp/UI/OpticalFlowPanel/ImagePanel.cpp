#include <UI/OpticalFlowPanel/ImagePanel.hpp>

OpticalFlowPanelImage::OpticalFlowPanelImage(
    wxWindow *parent, wxWindowID id, const std::vector<ImgData> &imgData)
    : wxPanel(parent, id) {
    this->imgData = imgData;
    cv::Mat firstImg = imgData[count].image;

    opticalFlow = new SparseOF();

    tracker = new OBJECTTRACKER("CSRT");

    img_bitmap = new BBOpticalFlow(this, wxID_ANY);
    img_bitmap->SetImage(firstImg);
}

void OpticalFlowPanelImage::OnKeyPress(wxKeyEvent &e) {}

void OpticalFlowPanelImage::OnSize(wxSizeEvent &e) {
    wxSize this_size = e.GetSize();
    img_bitmap->SetClientSize(this_size);
}

void OpticalFlowPanelImage::SetCount(int count) {
    this->count = count;
    img_bitmap->SetImage(imgData[count].image);
}

void OpticalFlowPanelImage::SetTrueRect(cv::Rect rect) {
    img_bitmap->SetTrueRect(rect);
}

void OpticalFlowPanelImage::OnButtonIncrement() {
    count = (count >= imgData.size() - 1) ? imgData.size() - 1 : count + 1;
    if (isOpticalFlow) {
        cv::Mat f = imgData[count].image;
        opticalFlow->run(f);
        img_bitmap->SetImage(opticalFlow->getOutput());
        return;
    }
    if (isObjectTracked) {
        cv::Rect r = tracker->UpdateTracker(imgData[count].image);
        img_bitmap->SetTrueRect(r);
    }
    wxMessageBox("Normal");
    img_bitmap->SetImage(imgData[count].image);
}

void OpticalFlowPanelImage::OnButtonDecrement() {
    count = (count <= 0) ? 0 : count - 1;
    if (isObjectTracked) {
        cv::Rect r = tracker->UpdateTracker(imgData[count].image);
        img_bitmap->SetTrueRect(r);
    }
    img_bitmap->SetImage(imgData[count].image);
}

void OpticalFlowPanelImage::StartTracking() {
    if (!isObjectTracked) {
        tracker->InitTracker(imgData[count].image, img_bitmap->GetTrueRect());
        isObjectTracked = true;
    }
}

void OpticalFlowPanelImage::StartOpticalFlow() {
    cv::Mat f = imgData[count].image;
    cv::Rect r = img_bitmap->GetTrueRect();
    opticalFlow->Init(f, r);

    while (!(opticalFlow->isInitPointValid(OF_LIMIT))) {

        /**
         * ! pottential error:
         * ! the loop might run till end of vector
         * ! might not have enough vector left for further run ?
         */

        if (!isObjectTracked) {
            tracker->InitTracker(f, r);
            isObjectTracked = true;
            img_bitmap->ToggleDrawRect();
        }

        count = (count >= imgData.size() - 1) ? imgData.size() - 1 : count + 1;
        f = imgData[count].image;
        r = tracker->UpdateTracker(f);

        opticalFlow->Init(f, r);
        img_bitmap->SetTrueRect(r);
        img_bitmap->SetImage(f);
    }

    while (opticalFlow->getCollection().size() < OF_MAX_COUNT) {
        count = (count >= imgData.size() - 1) ? imgData.size() - 1 : count + 1;
        f = imgData[count].image;
        opticalFlow->run(f);
        img_bitmap->SetImage(opticalFlow->getOutput());
    }
}

void OpticalFlowPanelImage::EvalOFResult() {
    roiData = opticalFlow->evaluateCollection();

    cv::Mat firstFrame = imgData[count - OF_MAX_COUNT + 1].image.clone();

    // Draw Point
    for (int i = 0; i < roiData.size(); i++) {
        for (auto &p : roiData[i]) {
            circle(firstFrame, p.point, 2, cv::Scalar(0, 0, 255), 2);
        }
    }

    // Draw Line for each point
    for (int i = 0; i < roiData[0].size(); i++) {
        cv::Point2f p1 = roiData[0][i].point;
        cv::Point2f p2 = roiData[roiData.size() - 1][i].point;
        line(firstFrame, p1, p2, cv::Scalar(0, 255, 0), 1);
    }

    img_bitmap->SetImage(firstFrame);
}

std::vector<std::vector<PointData>> OpticalFlowPanelImage::GetRoiData() {
    return roiData;
}

// * This function will return FirstImage
int OpticalFlowPanelImage::GetCount() { return count - OF_MAX_COUNT + 1; }

cv::Mat OpticalFlowPanelImage::GetFirstImage() {
    return imgData[count - OF_MAX_COUNT + 1].image;
}

// clang-format off
BEGIN_EVENT_TABLE(OpticalFlowPanelImage, wxPanel)
EVT_KEY_DOWN(OpticalFlowPanelImage::OnKeyPress)
EVT_SIZE(OpticalFlowPanelImage::OnSize)
END_EVENT_TABLE()
