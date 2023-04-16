#include <Utils/wxUtils.hpp>

namespace Utils {
std::string wxStringToString(wxString wxstr) {
    std::string str;
    str.assign(wxstr.mb_str());
    return str;
}

bool ConvertMatBitmapTowxBitmap(const cv::Mat& matBitmap,
                                wxBitmap& bitmap) {
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
        const uchar* bgr = matBitmap.data;

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
} // namespace Utils
