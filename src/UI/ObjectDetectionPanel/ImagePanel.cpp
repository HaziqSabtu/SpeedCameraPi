#include <UI/ObjectDetectionPanel/ImagePanel.hpp>

ObjectDetectionPanelImage::ObjectDetectionPanelImage(
    wxWindow *parent, wxWindowID id, ObjectDetection &objd,
    SpeedCalculation &spdC, std::vector<ImgData> &imgData)
    : wxPanel(parent, id), objD(objd), speedCalc(spdC), imgData(imgData) {

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
        handleBBox();
    }

    if (img_bitmap->GetIsBotL()) {
        handleBotL();
    }

    if (img_bitmap->GetIsOptF()) {
        handleOptF();
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
        handleBBox();
        return;
    }
    wxLogMessage("Bounding Box -> Off");
}

void ObjectDetectionPanelImage::OnOptF() {
    wxLogMessage("OnOptF");
    img_bitmap->toggleOptF();
    if (img_bitmap->GetIsOptF()) {
        wxLogMessage("Optical Flow -> On");
        handleOptF();
        return;
    }
    wxLogMessage("Optical Flow -> Off");
}

void ObjectDetectionPanelImage::OnBotL() {
    img_bitmap->toggleBotL();
    if (img_bitmap->GetIsBotL()) {
        wxLogMessage("Bottom Line -> On");
        handleBotL();
        return;
    }
    wxLogMessage("Bottom Line -> Off");
}

void ObjectDetectionPanelImage::OnLine() {
    img_bitmap->toggleLine();
    if (img_bitmap->GetIsLine()) {
        wxLogMessage("Line -> On");
        return;
    }
    wxLogMessage("Line -> Off");
}

void ObjectDetectionPanelImage::OnSpeed() {
    wxLogMessage("Speed Calculation Started");
    speedCalc.SetLine(img_bitmap->GetLine());
    speedCalc.runCalculation(speedCalc.toSpeedData(imgData, opticalFlowPoints));
    wxLogMessage("Speed Calculation Complete");
};

void ObjectDetectionPanelImage::handleBBox() {
    img_bitmap->SetRect(objD.GetRect(opticalFlowPoints[count]));
}

void ObjectDetectionPanelImage::handleOptF() {
    img_bitmap->SetPoints(objD.GetOFPoints(opticalFlowPoints, count));
}

void ObjectDetectionPanelImage::handleBotL() {
    std::vector<cv::Point2f> points =
        objD.GetBottomLine(opticalFlowPoints[count], imgData[count].image.cols);
    wxLogMessage("Bottom Line y: %f", points[0].y);
    img_bitmap->SetBotL(objD.GetBottomLine(opticalFlowPoints[count],
                                           imgData[count].image.cols));
}

int ObjectDetectionPanelImage::GetCount() { return count; }

std::vector<std::vector<cv::Point2f>>
ObjectDetectionPanelImage::GetOpticalFlowPoints() {
    return opticalFlowPoints;
}

void ObjectDetectionPanelImage::SetLine(std::vector<cv::Vec4i> l) {
    img_bitmap->SetLine(l);
}

// clang-format off
BEGIN_EVENT_TABLE(ObjectDetectionPanelImage, wxPanel)
EVT_SIZE(ObjectDetectionPanelImage::OnSize)
END_EVENT_TABLE()
