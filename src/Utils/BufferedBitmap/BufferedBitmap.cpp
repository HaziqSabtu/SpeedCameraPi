#include <Utils/BufferedBitmap/BufferedBitmap.hpp>

BufferedBitmap::BufferedBitmap(wxWindow *parent, wxWindowID id)
    : wxStaticBitmap(parent, id, wxNullBitmap) {
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void BufferedBitmap::SetImage(const cv::Mat &image) {
    // wxMessageBox("CrashHere");
    img = image.clone();
    wxImage wximg = matToWxImage(img);
    wxStaticBitmap::SetBitmap(wxBitmap(wximg));
}

wxImage BufferedBitmap::matToWxImage(const cv::Mat &mat) {
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

// clang-format off
wxBEGIN_EVENT_TABLE(BufferedBitmap, wxStaticBitmap)
wxEND_EVENT_TABLE()
