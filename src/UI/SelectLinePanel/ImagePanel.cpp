#include <UI/SelectLinePanel/ImagePanel.hpp>

SelectLinePanelImage::SelectLinePanelImage(wxWindow *parent, wxWindowID id,
                                           std::vector<ImgData> &imgData)
    : wxPanel(parent, id) {
    this->imgData = imgData;
    cv::Mat firstImg = imgData[count].image;

    img_bitmap = new BBLane(this, wxID_ANY);
    img_bitmap->SetImage(firstImg);
}

void SelectLinePanelImage::OnButtonIncrement() {
    count = (count >= imgData.size() - 1) ? imgData.size() - 1 : count + 1;
    img_bitmap->SetImage(imgData[count].image);
}

void SelectLinePanelImage::OnButtonDecrement() {
    count = (count <= 0) ? 0 : count - 1;
    img_bitmap->SetImage(imgData[count].image);
}

void SelectLinePanelImage::OnKeyPress(wxKeyEvent &e) {
    if (e.GetKeyCode() == 'n' || e.GetKeyCode() == WXK_RIGHT) {
        OnButtonIncrement();
    } else if (e.GetKeyCode() == 'p' || e.GetKeyCode() == WXK_LEFT) {
        OnButtonDecrement();
    } else if (e.GetKeyCode() == 's' || e.GetKeyCode() == WXK_RETURN) {
        // todo set selected IMG
    }
}

void SelectLinePanelImage::OnSize(wxSizeEvent &e) {
    wxSize this_size = e.GetSize();
    img_bitmap->SetClientSize(this_size);
}

// clang-format off
BEGIN_EVENT_TABLE(SelectLinePanelImage, wxPanel)
EVT_KEY_DOWN(SelectLinePanelImage::OnKeyPress)
EVT_SIZE(SelectLinePanelImage::OnSize)
END_EVENT_TABLE()
