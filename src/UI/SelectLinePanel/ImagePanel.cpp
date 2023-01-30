#include <UI/SelectLinePanel/ImagePanel.hpp>

SelectLinePanelImage::SelectLinePanelImage(wxWindow *parent, wxWindowID id,
                                           std::vector<ImgData> &imgData)
    : wxPanel(parent, id), lineDetection() {
    this->imgData = imgData;
    cv::Mat firstImg = imgData[count].image;

    img_bitmap = new BBLane(this, wxID_ANY);
    img_bitmap->SetImage(firstImg);
}

void SelectLinePanelImage::OnCanny() {
    isCanny = !isCanny;
    if (isCanny) {
        wxLogMessage("Show Canny");
        lineDetection.SetImage(imgData[count].image);
        img_bitmap->SetImage(lineDetection.GetCanny());
        return;
    }
    wxLogMessage("Hide Canny");
    img_bitmap->SetImage(imgData[count].image);
}

void SelectLinePanelImage::OnHough() {
    img_bitmap->ToggleHough();

    if (img_bitmap->GetIsHough()) {
        wxLogMessage("Show Hough");
        lineDetection.SetImage(imgData[count].image);
        img_bitmap->SetLinesP(lineDetection.GetLinesP());
        return;
    }
    wxLogMessage("Hide Hough");
}

void SelectLinePanelImage::OnSize(wxSizeEvent &e) {
    wxSize this_size = e.GetSize();
    img_bitmap->SetClientSize(this_size);
}

// clang-format off
BEGIN_EVENT_TABLE(SelectLinePanelImage, wxPanel)
EVT_SIZE(SelectLinePanelImage::OnSize)
END_EVENT_TABLE()
