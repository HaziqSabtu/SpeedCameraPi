#include <UI/CameraPanel/Panel_Image2.hpp>

ImagePanelBitmap::ImagePanelBitmap(wxPanel* parent) : wxPanel(parent) {
    noImageBitmap = createBitmap("No Image");
    errorBitmap = createBitmap("Error");

    image = noImageBitmap;

    w = -1;
    h = -1;

    Bind(wxEVT_LEFT_DOWN, &ImagePanelBitmap::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &ImagePanelBitmap::OnLeftUp, this);
    Bind(wxEVT_MOTION, &ImagePanelBitmap::OnMotion, this);
    // Bind(EVT_MOUSE_EVENTS, &ImagePanelBitmap::OnMouse, this);
}

void ImagePanelBitmap::setImage(wxBitmap& image) {
    this->image = image;
    Refresh();
}

void ImagePanelBitmap::setNoImage() {
    image = noImageBitmap;
    Refresh();
}

// TODO: Use wxMethods to create the bitmap
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

    wxBrush greenBrush(wxColour(0, 255, 0, 50), wxBRUSHSTYLE_SOLID);
    dc.SetBrush(greenBrush);
    dc.DrawRectangle(0, 0, w, h);

    if (rect.IsEmpty()) {
        return;
    }

    wxBitmap cropped = CropBitmap(resized, rect);
    dc.DrawBitmap(cropped, rect.GetX(), rect.GetY(), false);
}

wxBitmap ImagePanelBitmap::resize(wxBitmap& bitmap, const wxSize& size) {
    wxImage image = bitmap.ConvertToImage();
    image.Rescale(size.GetWidth(), size.GetHeight(), wxIMAGE_QUALITY_HIGH);
    return wxBitmap(image);
}

wxBitmap ImagePanelBitmap::CropBitmap(wxBitmap& originalBitmap,
                                      wxRect region) {
    wxMemoryDC originalDC(originalBitmap);
    wxBitmap croppedBitmap(region.width, region.height);
    wxMemoryDC croppedDC(croppedBitmap);

    croppedDC.Blit(0,
                   0,
                   region.width,
                   region.height,
                   &originalDC,
                   region.x,
                   region.y);

    return croppedBitmap;
}

wxRect ImagePanelBitmap::getRect(wxPoint p1, wxPoint p2) {
    int x = p1.x < p2.x ? p1.x : p2.x;
    int y = p1.y < p2.y ? p1.y : p2.y;
    int width = abs(p1.x - p2.x);
    int height = abs(p1.y - p2.y);

    return wxRect(x, y, width, height);
}

void ImagePanelBitmap::OnPaint(wxPaintEvent& e) {
    wxPaintDC dc(this);
    render(dc);
}

void ImagePanelBitmap::OnSize(wxSizeEvent& event) {
    Refresh();
    event.Skip();
}

void ImagePanelBitmap::OnLeftDown(wxMouseEvent& e) {
    p1 = e.GetPosition();
    isDown = true;
}

void ImagePanelBitmap::OnLeftUp(wxMouseEvent& e) {

    if (!isDown) {
        return;
    }

    isDown = false;

    wxPoint p2 = e.GetPosition();

    rect = getRect(p1, p2);

    Refresh();
}

void ImagePanelBitmap::OnMotion(wxMouseEvent& e) {

    if (!isDown) {
        return;
    }

    wxPoint p2 = e.GetPosition();

    rect = getRect(p1, p2);

    Refresh();
}

BEGIN_EVENT_TABLE(ImagePanelBitmap, wxPanel)
EVT_PAINT(ImagePanelBitmap::OnPaint)
EVT_SIZE(ImagePanelBitmap::OnSize)
END_EVENT_TABLE()