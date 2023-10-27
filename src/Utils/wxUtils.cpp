#include <Utils/wxUtils.hpp>

namespace Utils {
std::string wxStringToString(wxString wxstr) {
    std::string str;
    str.assign(wxstr.mb_str());
    return str;
}

bool cvMatToWxBitmap(const cv::Mat &matBitmap, wxBitmap &bitmap) {
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

cv::Point wxPointToCvPoint(const wxPoint &point) {
    return cv::Point(point.x, point.y);
}

wxBitmap recolor(wxBitmap &b, const wxColour &c) {
    wxImage img = b.ConvertToImage();
    img.Replace(255, 255, 255, c.Red(), c.Green(), c.Blue());
    return wxBitmap(img);
}

wxBitmap resize(const wxBitmap &b, const wxSize &s) {
    wxImage img = b.ConvertToImage();

    if (s.GetWidth() == 0 && s.GetHeight() != 0) {
        double aspectRatio =
            static_cast<double>(img.GetWidth()) / img.GetHeight();
        int newWidth = static_cast<int>(s.GetHeight() * aspectRatio);
        img.Rescale(newWidth, s.GetHeight());
    } else if (s.GetWidth() != 0 && s.GetHeight() == 0) {
        double aspectRatio =
            static_cast<double>(img.GetHeight()) / img.GetWidth();
        int newHeight = static_cast<int>(s.GetWidth() * aspectRatio);
        img.Rescale(s.GetWidth(), newHeight);
    } else {
        img.Rescale(s.GetWidth(), s.GetHeight());
    }

    return wxBitmap(img);
}

std::pair<cv::Scalar, cv::Scalar>
HSVRangeConfigToScalar(const HSVRangeConfig &range) {
    return std::make_pair(
        cv::Scalar(range.hueLower, range.saturationLower, range.valueLower),
        cv::Scalar(range.hueUpper, range.saturationUpper, range.valueUpper));
}

HSVRangeConfig
ScalarToHSVRangeConfig(const std::pair<cv::Scalar, cv::Scalar> &range) {
    return HSVRangeConfig {
        static_cast<int>(range.first[0]), static_cast<int>(range.second[0]),
        static_cast<int>(range.first[1]), static_cast<int>(range.second[1]),
        static_cast<int>(range.first[2]), static_cast<int>(range.second[2])};
}

wxString idToFileName(std::string id) {
    const std::string extension = ".scpdata";
    return wxString::Format(wxT("%s%s"), id, extension);
}

} // namespace Utils
