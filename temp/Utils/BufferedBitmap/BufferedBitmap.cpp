#include <Utils/BufferedBitmap/BufferedBitmap.hpp>

BufferedBitmap::BufferedBitmap(wxWindow *parent, wxWindowID id)
    : wxStaticBitmap(parent, id, wxNullBitmap) {
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void BufferedBitmap::SetImage(const cv::Mat &image) {
    img = image.clone();
    wxLogMessage("Setting Image");
    BufferedBitmap::processRatio();
    wxImage wximg = matToWxImage(img);
    wxStaticBitmap::SetBitmap(wxBitmap(wximg));
    Refresh();
}

wxImage BufferedBitmap::matToWxImage(const cv::Mat &mat) {
    wxLogMessage("mattoxwimage");
    if (mat.empty())
        return wxImage();
    if (mat.type() == CV_8UC3) {
        cv::cvtColor(mat, RGBImg, cv::COLOR_BGR2RGB);
        // cv::imshow("temp", mat);
        wxImage img(RGBImg.cols, RGBImg.rows, RGBImg.data, true);
        return img;

    } else if (mat.type() == CV_8UC1) {
        wxImage image(mat.cols, mat.rows, mat.data);
        return image.ConvertToGreyscale();
    } else
        throw std::runtime_error("Unsupported image format");
}

double BufferedBitmap::GetWidthRatio() { return widthRatio; }

double BufferedBitmap::GetHeightRatio() { return heightRatio; }

void BufferedBitmap::OnPaint(wxPaintEvent &e){
    std::cout << "from BB" << std::endl;
}


// clang-format off
wxBEGIN_EVENT_TABLE(BufferedBitmap, wxStaticBitmap)
EVT_PAINT(BufferedBitmap::OnPaint)
wxEND_EVENT_TABLE()