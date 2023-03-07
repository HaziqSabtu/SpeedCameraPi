#include <Utils/FileReader/fileAVI.hpp>

FILEAVI::FILEAVI(/* args */) {}

FILEAVI::~FILEAVI() {}

void FILEAVI::ReadFile(std::string path, std::vector<ImgData> &imgData) {
    cv::VideoCapture cap(path);

    if (!cap.isOpened()) {
        std::cout << "Could not open video file" << std::endl;
        exit(1);
    }

    cv::Mat frame;

    std::chrono ::high_resolution_clock::time_point startTime =
        std::chrono::high_resolution_clock::now();

    while (cap.read(frame)) {
        cv::Mat frameCopy = frame.clone();
        double timestamp = cap.get(cv::CAP_PROP_POS_MSEC);
        std::cout << "Timestamp: " << timestamp << std::endl;
        std::chrono ::high_resolution_clock::time_point time =
            startTime + std::chrono::milliseconds((int)timestamp);
        imgData.push_back({frameCopy, time});
    }

    std::cout << "Read file " << path << std::endl;
    cap.release();
    std::cout << "Release file " << path << std::endl;
}

// int FILEAVI::WriteFile(std::string path, std::vector<ImgData> &imgData) {
//     // check if file exists

//     std::ofstream file(path, std::ios::binary);

//     for (auto &img : imgData) {
//         std::chrono::high_resolution_clock::time_point time = img.time;
//         int cols = img.image.cols;
//         int rows = img.image.rows;
//         int type = img.image.type();
//         bool continuous = img.image.isContinuous();
//         file.write(reinterpret_cast<char const *>(&time), sizeof(time));
//         file.write(reinterpret_cast<char const *>(&cols), sizeof(cols));
//         file.write(reinterpret_cast<char const *>(&rows), sizeof(rows));
//         file.write(reinterpret_cast<char const *>(&type), sizeof(type));
//         file.write(reinterpret_cast<char const *>(&continuous),
//                    sizeof(continuous));

//         if (continuous) {
//             size_t size = rows * cols * img.image.elemSize();
//             file.write(reinterpret_cast<char const *>(img.image.ptr()),
//             size);
//         } else {
//             size_t size = cols * img.image.elemSize();
//             for (int i = 0; i < rows; ++i) {
//                 file.write(reinterpret_cast<char const *>(img.image.ptr(i)),
//                            size);
//             }
//         }
//     }
//     file.close();
//     return 0;
// }

double FILEAVI::getTimeDifference(
    std::chrono::high_resolution_clock::time_point time1,
    std::chrono::high_resolution_clock::time_point time2) {
    return std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1)
               .count() /
           1000.0;
}