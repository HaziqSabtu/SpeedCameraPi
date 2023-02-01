#include <UI/ObjectDetectionPanel/ImagePanel.hpp>

ObjectDetectionPanelImage::ObjectDetectionPanelImage(
    wxWindow *parent, wxWindowID id, ObjectDetection &objd,
    std::vector<ImgData> &imgData)
    : wxPanel(parent, id), objD(objd), imgData(imgData) {

    cv::Mat firstImg = imgData[count].image;

    img_bitmap = new BBObjD(this, Enum::OD_BB_ID);
    img_bitmap->SetImage(firstImg);
}

void ObjectDetectionPanelImage::runDetection() {
    wxLogMessage("Running Object Detection");
    objD.runDetection(imgData);
    opticalFlowPoints = objD.GetOpticalFlowPoints(true);
    wxLogMessage("Object Detection Complete");
}

void ObjectDetectionPanelImage::OnButtonIncrement() {
    count = (count >= imgData.size() - 1) ? imgData.size() - 1 : count + 1;
    img_bitmap->SetImage(imgData[count].image);

    if (img_bitmap->GetIsBBox()) {
        img_bitmap->SetRect(objD.GetRect(opticalFlowPoints[count]));
    }

    if (img_bitmap->GetIsBotL()) {
        img_bitmap->setBotL(objD.GetBottomLine(opticalFlowPoints[count],
                                               imgData[count].image.cols));
    }

    if (img_bitmap->GetIsOptF()) {
        img_bitmap->setPoints(objD.GetOFPoints(opticalFlowPoints, count));
    }
}

void ObjectDetectionPanelImage::OnButtonDecrement() {
    count = (count <= 0) ? 0 : count - 1;
    img_bitmap->SetImage(imgData[count].image);
}

void ObjectDetectionPanelImage::OnSize(wxSizeEvent &e) {
    wxSize this_size = e.GetSize();
    img_bitmap->SetClientSize(this_size);
}

void ObjectDetectionPanelImage::OnBBox() {
    img_bitmap->toggleBBox();
    if (img_bitmap->GetIsBBox()) {
        wxLogMessage("Bounding Box -> On");
        img_bitmap->SetRect(objD.GetRect(opticalFlowPoints[count]));
        return;
    }
    wxLogMessage("Bounding Box -> Off");
}

void ObjectDetectionPanelImage::OnOptF() {
    img_bitmap->toggleOptF();
    if (img_bitmap->GetIsOptF()) {
        wxLogMessage("Optical Flow -> On");
        img_bitmap->setPoints(objD.GetOFPoints(opticalFlowPoints, count));
        return;
    }
    wxLogMessage("Optical Flow -> Off");
}

void ObjectDetectionPanelImage::OnBotL() {
    img_bitmap->toggleBotL();
    if (img_bitmap->GetIsBotL()) {
        wxLogMessage("Bottom Line -> On");
        img_bitmap->setBotL(objD.GetBottomLine(opticalFlowPoints[count],
                                               imgData[count].image.cols));
        return;
    }
    wxLogMessage("Bottom Line -> Off");
}

int ObjectDetectionPanelImage::GetCount() { return count; }

std::vector<std::vector<cv::Point2f>>
ObjectDetectionPanelImage::GetOpticalFlowPoints() {
    return opticalFlowPoints;
}

// clang-format off
BEGIN_EVENT_TABLE(ObjectDetectionPanelImage, wxPanel)
EVT_SIZE(ObjectDetectionPanelImage::OnSize)
END_EVENT_TABLE()
