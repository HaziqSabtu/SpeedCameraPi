#include <Utils/ImageBitmap/ImageBitmap.hpp>

ImageBitmap::ImageBitmap(wxWindow *parent, wxWindowID id,
                         const wxBitmap &bitmap, const wxPoint &pos,
                         const wxSize &size, long style, const wxString &name)
    : wxStaticBitmap(parent, id, bitmap, pos, size, style, name) {}

void ImageBitmap::SetImage(const cv::Mat &img) {
    this->image = img.clone();
    drawBitMap();
}

void ImageBitmap::drawBitMap() {
    wxLogMessage("ImageBitmap::drawBitMap()");
    if (image.empty()) {
        return;
    }
    processRatio();

    cv::Mat img_cp = image.clone();
    cv::Mat img_rs;
    cv::resize(img_cp, img_rs, cv::Size(resizeWidth, resizeHeight));

    wxImage wximg = matToWxImage(img_rs);
    SetBitmap(wxBitmap(wximg));
}

void ImageBitmap::processRatio() {
    clientSize = GetClientSize();

    width = clientSize.GetWidth();
    height = clientSize.GetHeight();

    if (width == 0 || height == 0) {
        return;
    }

    imgRatio = (double)image.cols / (double)image.rows;
    clientRatio = (double)width / (double)height;

    if (imgRatio > clientRatio) {
        resizeWidth = width;
        resizeHeight = (int)((double)width / imgRatio);
    } else {
        resizeHeight = height;
        resizeWidth = (int)((double)height * imgRatio);
    }

    widthRatio = (double)image.cols / (double)resizeWidth;
    heightRatio = (double)image.rows / (double)resizeHeight;

    // std::cout << "width: " << width << std::endl;
    // std::cout << "height: " << height << std::endl;
    // std::cout << "imgRatio: " << imgRatio << std::endl;
    // std::cout << "img.cols: " << image.cols << std::endl;
    // std::cout << "img.rows: " << image.rows << std::endl;
    // std::cout << "clientRatio: " << clientRatio << std::endl;
    // std::cout << "resizeWidth: " << resizeWidth << std::endl;
    // std::cout << "resizeHeight: " << resizeHeight << std::endl;
    // std::cout << "widthRatio: " << widthRatio << std::endl;
    // std::cout << "heightRatio: " << heightRatio << std::endl;
}

wxPoint ImageBitmap::GetRealMousePos(wxPoint mousePos) {
    wxPoint realMousePos;
    realMousePos.x = mousePos.x * widthRatio;
    realMousePos.y = mousePos.y * heightRatio;
    return realMousePos;
}

void ImageBitmap::OnSize() { drawBitMap(); }

wxImage ImageBitmap::matToWxImage(cv::Mat &image) {
    if (image.empty()) {
        return wxImage();
    }
    if (image.type() == CV_8UC3) {
        cv::cvtColor(image, rgbImage, cv::COLOR_BGR2RGB);
        wxImage wximg(rgbImage.cols, rgbImage.rows, rgbImage.data, true);
        return wximg;

    } else if (image.type() == CV_8UC1) {
        wxImage wximg(image.cols, image.rows, image.data);
        return wximg.ConvertToGreyscale();
    } else {
        throw std::runtime_error("Unsupported image format");
    }
}
// clang-format off
wxBEGIN_EVENT_TABLE(ImageBitmap, wxStaticBitmap) 
wxEND_EVENT_TABLE()