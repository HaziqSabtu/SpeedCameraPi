#include <Utils/ImageBitmap/Bit.hpp>

wxImagePanel::wxImagePanel(wxPanel *parent) : wxPanel(parent) {
    noImage = cv::Mat(480, 640, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::putText(noImage, "No Image", cv::Point(200, 240),
                cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2,
                cv::LINE_AA);
    w = -1;
    h = -1;
}

void wxImagePanel::paintEvent(wxPaintEvent &evt) {
    wxPaintDC dc(this);
    render(dc);
}

void wxImagePanel::paintNow() {
    wxClientDC dc(this);
    render(dc);
}

void wxImagePanel::SetImage(cv::Mat &img) {
    image = img.clone();
    paintNow();
}

void wxImagePanel::SetImage() {
    image = noImage;
    paintNow();
}

void wxImagePanel::render(wxDC &dc) {
    int neww, newh;
    dc.GetSize(&neww, &newh);

    if (image.empty()) {
        image = noImage;
    }

    if (neww != w || newh != h) {
        w = neww;
        h = newh;
    }
    cv::resize(image, image, cv::Size(w, h));
    resized = wxBitmap(image.cols, image.rows, 24);
    ConvertMatBitmapTowxBitmap(image, resized);
    dc.DrawBitmap(resized, 0, 0, false);
}

void wxImagePanel::OnSize(wxSizeEvent &event) {
    Refresh();
    event.Skip();
}

bool wxImagePanel::ConvertMatBitmapTowxBitmap(const cv::Mat &matBitmap,
                                              wxBitmap &bitmap) {
    wxCHECK(!matBitmap.empty(), false);
    wxCHECK(matBitmap.type() == CV_8UC3, false);
    wxCHECK(matBitmap.dims == 2, false);
    wxCHECK(bitmap.IsOk(), false);
    wxCHECK(bitmap.GetWidth() == matBitmap.cols &&
                bitmap.GetHeight() == matBitmap.rows,
            false);
    wxCHECK(bitmap.GetDepth() == 24, false);

    wxNativePixelData pixelData(bitmap);
    wxNativePixelData::Iterator pixelDataIt(pixelData);

    if (matBitmap.isContinuous()) {
        const uchar *bgr = matBitmap.data;

        for (int row = 0; row < pixelData.GetHeight(); ++row) {
            pixelDataIt.MoveTo(pixelData, 0, row);

            for (int col = 0; col < pixelData.GetWidth();
                 ++col, ++pixelDataIt) {
                pixelDataIt.Blue() = *bgr++;
                pixelDataIt.Green() = *bgr++;
                pixelDataIt.Red() = *bgr++;
            }
        }
    } else // Is it even possible for Mat with image to be not continous?
    {
        auto matBitmapIt = matBitmap.begin<cv::Vec3b>();

        for (int row = 0; row < pixelData.GetHeight(); ++row) {
            pixelDataIt.MoveTo(pixelData, 0, row);

            for (int col = 0; col < pixelData.GetWidth();
                 ++col, ++pixelDataIt, ++matBitmapIt) {
                pixelDataIt.Blue() = (*matBitmapIt)[0];
                pixelDataIt.Green() = (*matBitmapIt)[1];
                pixelDataIt.Red() = (*matBitmapIt)[2];
            }
        }
    }

    return bitmap.IsOk();
}

BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
EVT_PAINT(wxImagePanel::paintEvent)
EVT_SIZE(wxImagePanel::OnSize)
END_EVENT_TABLE()