#include <UI/Panel/Base/Panel_Image.hpp>

BaseImagePanel::BaseImagePanel(wxPanel *parent) : wxPanel(parent) {
    noImageBitmap = createBitmap("No Image");
    errorBitmap = createBitmap("Error");

    image = noImageBitmap;

    w = -1;
    h = -1;
}

void BaseImagePanel::setImage(wxBitmap &image) {
    this->image = image;
    Refresh();
}

void BaseImagePanel::setNoImage() {
    image = noImageBitmap;
    Refresh();
}

wxSize BaseImagePanel::getImageSize() { return image.GetSize(); }

// TODO: Use wxMethods to create the bitmap
const wxBitmap BaseImagePanel::createBitmap(std::string text) {
    cv::Mat image = cv::Mat(480, 640, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::putText(image, text, cv::Point(200, 240), cv::FONT_HERSHEY_SIMPLEX, 1,
                cv::Scalar(255, 255, 255), 2, cv::LINE_AA);

    wxImage returnImage(image.cols, image.rows, image.data, true);

    return wxBitmap(returnImage);
}

void BaseImagePanel::calcRatio(wxDC &dc) {
    int newW, newH;
    dc.GetSize(&newW, &newH);
    if (newW == w && newH == h) {
        return;
    }
    w = newW;
    h = newH;
}

void BaseImagePanel::render(wxDC &dc) {
    calcRatio(dc);

    if (!image.IsOk()) {
        image = errorBitmap;
    }

    widthRatio = (float)image.GetWidth() / (float)w;
    heightRatio = (float)image.GetHeight() / (float)h;

    resized = resize(image, wxSize(w, h));

    dc.DrawBitmap(resized, 0, 0, false);
}

wxBitmap BaseImagePanel::resize(wxBitmap &bitmap, const wxSize &size) {
    wxImage image = bitmap.ConvertToImage();
    image.Rescale(size.GetWidth(), size.GetHeight(), wxIMAGE_QUALITY_HIGH);
    return wxBitmap(image);
}

void BaseImagePanel::OnPaint(wxPaintEvent &e) {
    wxPaintDC dc(this);
    render(dc);
}

void BaseImagePanel::OnSize(wxSizeEvent &event) {
    Refresh();
    event.Skip();
}

BEGIN_EVENT_TABLE(BaseImagePanel, wxPanel)
EVT_PAINT(BaseImagePanel::OnPaint)
EVT_SIZE(BaseImagePanel::OnSize)
END_EVENT_TABLE()