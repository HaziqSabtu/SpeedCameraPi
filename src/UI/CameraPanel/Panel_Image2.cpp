#include <UI/CameraPanel/Panel_Image2.hpp>

ImagePanelBitmap::ImagePanelBitmap(wxPanel* parent) : wxPanel(parent) {
    noImageBitmap = createBitmap("No Image");
    errorBitmap = createBitmap("Error");

    image = noImageBitmap;

    w = -1;
    h = -1;
}

void ImagePanelBitmap::setImage(wxBitmap& image) {
    this->image = image;
    Refresh();
}

void ImagePanelBitmap::setNoImage() {
    image = noImageBitmap;
    Refresh();
}

const wxBitmap ImagePanelBitmap::createBitmap(std::string text) {
    cv::Mat image = cv::Mat(480, 640, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::putText(image,
                text,
                cv::Point(200, 240),
                cv::FONT_HERSHEY_SIMPLEX,
                1,
                cv::Scalar(255, 255, 255),
                2,
                cv::LINE_AA);

    wxImage returnImage(image.cols, image.rows, image.data, true);

    return wxBitmap(returnImage);
}

void ImagePanelBitmap::calcRatio(wxDC& dc) {
    int newW, newH;
    dc.GetSize(&newW, &newH);
    if (newW == w && newH == h) {
        return;
    }
    w = newW;
    h = newH;
}

void ImagePanelBitmap::render(wxDC& dc) {
    calcRatio(dc);

    if (!image.IsOk()) {
        image = errorBitmap;
    }

    widthRatio = (float)image.GetWidth() / (float)w;
    heightRatio = (float)image.GetHeight() / (float)h;

    resized = resize(image, wxSize(w, h));
    dc.DrawBitmap(resized, 0, 0, false);
}

wxBitmap ImagePanelBitmap::resize(wxBitmap& bitmap, const wxSize& size) {
    wxImage image = bitmap.ConvertToImage();
    image.Rescale(size.GetWidth(), size.GetHeight(), wxIMAGE_QUALITY_HIGH);
    return wxBitmap(image);
}

void ImagePanelBitmap::onPaint(wxPaintEvent& e) {
    wxPaintDC dc(this);
    render(dc);
}

void ImagePanelBitmap::onSize(wxSizeEvent& event) {
    Refresh();
    event.Skip();
}

BEGIN_EVENT_TABLE(ImagePanelBitmap, wxPanel)
EVT_PAINT(ImagePanelBitmap::onPaint)
EVT_SIZE(ImagePanelBitmap::onSize)
END_EVENT_TABLE()