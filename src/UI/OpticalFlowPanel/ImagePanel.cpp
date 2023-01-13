#include <UI/OpticalFlowPanel/ImagePanel.hpp>

OpticalFlowPanelImage::OpticalFlowPanelImage(wxWindow *parent, wxWindowID id,
                                             std::vector<ImgData> &imgData)
    : wxPanel(parent, id) {
    this->imgData = imgData;
    cv::Mat firstImg = imgData[count].image;

    img_bitmap = new BBOpticalFlow(this, wxID_ANY);
    img_bitmap->SetImage(firstImg);
}

void OpticalFlowPanelImage::OnKeyPress(wxKeyEvent &e) {
    // if (e.GetKeyCode() == 'n' || e.GetKeyCode() == WXK_RIGHT) {
    //     OnButtonIncrement();
    // } else if (e.GetKeyCode() == 'p' || e.GetKeyCode() == WXK_LEFT) {
    //     OnButtonDecrement();
    // } else if (e.GetKeyCode() == 's' || e.GetKeyCode() == WXK_RETURN) {
    //     // todo set selected IMG
    // }
}

void OpticalFlowPanelImage::OnSize(wxSizeEvent &e) {
    wxSize this_size = e.GetSize();
    img_bitmap->SetClientSize(this_size);
}

void OpticalFlowPanelImage::SetCount(int count) {
    this->count = count;
    img_bitmap->SetImage(imgData[count].image);
}

void OpticalFlowPanelImage::OnButtonIncrement() {
    count = (count >= imgData.size() - 1) ? imgData.size() - 1 : count + 1;
    img_bitmap->SetImage(imgData[count].image);
}

void OpticalFlowPanelImage::OnButtonDecrement() {
    count = (count <= 0) ? 0 : count - 1;
    img_bitmap->SetImage(imgData[count].image);
}

// clang-format off
BEGIN_EVENT_TABLE(OpticalFlowPanelImage, wxPanel)
EVT_KEY_DOWN(OpticalFlowPanelImage::OnKeyPress)
EVT_SIZE(OpticalFlowPanelImage::OnSize)
END_EVENT_TABLE()
