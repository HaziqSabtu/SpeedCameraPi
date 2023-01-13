#include <UI/SelectROIPanel/ImagePanel.hpp>

SelectRoiPanelImage::SelectRoiPanelImage(wxWindow *parent, wxWindowID id,
                                         std::vector<ImgData> &imgData)
    : wxPanel(parent, id) {
    this->imgData = imgData;
    cv::Mat firstImg = imgData[count].image;

    img_bitmap = new BBImage(this, wxID_ANY);
    img_bitmap->SetImage(firstImg);
}

void SelectRoiPanelImage::OnButtonIncrement() {
    count = (count >= imgData.size() - 1) ? imgData.size() - 1 : count + 1;
    img_bitmap->SetImage(imgData[count].image);
}

void SelectRoiPanelImage::OnButtonDecrement() {
    count = (count <= 0) ? 0 : count - 1;
    img_bitmap->SetImage(imgData[count].image);
}

void SelectRoiPanelImage::OnKeyPress(wxKeyEvent &e) {
    if (e.GetKeyCode() == 'n' || e.GetKeyCode() == WXK_RIGHT) {
        OnButtonIncrement();
    } else if (e.GetKeyCode() == 'p' || e.GetKeyCode() == WXK_LEFT) {
        OnButtonDecrement();
    } else if (e.GetKeyCode() == 's' || e.GetKeyCode() == WXK_RETURN) {
        // todo set selected IMG
    }
}

void SelectRoiPanelImage::OnToggleROI(wxCommandEvent &e) {
    img_bitmap->SetImage(imgData[count].image);
    img_bitmap->RemoveRectangle();
}

void SelectRoiPanelImage::OnSize(wxSizeEvent &e) {
    wxSize this_size = e.GetSize();
    img_bitmap->SetClientSize(this_size);
}

int SelectRoiPanelImage::GetCount() { return count; }

cv::Rect SelectRoiPanelImage::GetTrueRect() {
    return img_bitmap->GetTrueRect();
}

// clang-format off
BEGIN_EVENT_TABLE(SelectRoiPanelImage, wxPanel)
EVT_KEY_DOWN(SelectRoiPanelImage::OnKeyPress)
EVT_SIZE(SelectRoiPanelImage::OnSize)
END_EVENT_TABLE()
