#include <UI/ObjectDetectionPanel/ImagePanel.hpp>

ObjectDetectionPanelImage::ObjectDetectionPanelImage(
    wxWindow *parent, wxWindowID id, std::vector<ImgData> &imgData)
    : wxPanel(parent, id) {
    this->imgData = imgData;
    cv::Mat firstImg = imgData[count].image;

    img_bitmap = new BBObjD(this, Enum::OD_BB_ID);
    img_bitmap->SetImage(firstImg);
}

void ObjectDetectionPanelImage::OnButtonIncrement() {
    count = (count >= imgData.size() - 1) ? imgData.size() - 1 : count + 1;
    img_bitmap->SetImage(imgData[count].image);
}

void ObjectDetectionPanelImage::OnButtonDecrement() {
    count = (count <= 0) ? 0 : count - 1;
    img_bitmap->SetImage(imgData[count].image);
}

void ObjectDetectionPanelImage::OnSize(wxSizeEvent &e) {
    wxSize this_size = e.GetSize();
    img_bitmap->SetClientSize(this_size);
}

int ObjectDetectionPanelImage::GetCount() { return count; }

// clang-format off
BEGIN_EVENT_TABLE(ObjectDetectionPanelImage, wxPanel)
EVT_SIZE(ObjectDetectionPanelImage::OnSize)
END_EVENT_TABLE()
