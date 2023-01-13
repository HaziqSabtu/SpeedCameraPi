#include <Utils/fileWR.hpp>

FILEWR::FILEWR(/* args */) {}

FILEWR::~FILEWR() {}

int FILEWR::ReadFile(std::string path, std::vector<ImgData> &imgData) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return -1;
    }
    while (file) {
        std::chrono::high_resolution_clock::time_point time;
        file.read(reinterpret_cast<char *>(&time), sizeof(time));

        int cols;
        int rows;
        int type;
        bool continuous;

        file.read(reinterpret_cast<char *>(&cols), sizeof(cols));
        file.read(reinterpret_cast<char *>(&rows), sizeof(rows));
        file.read(reinterpret_cast<char *>(&type), sizeof(type));
        file.read(reinterpret_cast<char *>(&continuous), sizeof(continuous));

        cv::Mat img(rows, cols, type);
        if (continuous) {
            size_t size = rows * cols * img.elemSize();
            file.read(reinterpret_cast<char *>(img.ptr()), size);
        } else {
            size_t size = cols * img.elemSize();
            for (int i = 0; i < rows; ++i) {
                file.read(reinterpret_cast<char *>(img.ptr(i)), size);
            }
        }
        if (!img.empty() && time.time_since_epoch().count() != 0)
            imgData.push_back({img, time});
    }
    file.close();
    return 0;
}

int FILEWR::WriteFile(std::string path, std::vector<ImgData> &imgData) {
    // check if file exists

    std::ofstream file(path, std::ios::binary);

    for (auto &img : imgData) {
        std::chrono::high_resolution_clock::time_point time = img.time;
        int cols = img.image.cols;
        int rows = img.image.rows;
        int type = img.image.type();
        bool continuous = img.image.isContinuous();
        file.write(reinterpret_cast<char const *>(&time), sizeof(time));
        file.write(reinterpret_cast<char const *>(&cols), sizeof(cols));
        file.write(reinterpret_cast<char const *>(&rows), sizeof(rows));
        file.write(reinterpret_cast<char const *>(&type), sizeof(type));
        file.write(reinterpret_cast<char const *>(&continuous),
                   sizeof(continuous));

        if (continuous) {
            size_t size = rows * cols * img.image.elemSize();
            file.write(reinterpret_cast<char const *>(img.image.ptr()), size);
        } else {
            size_t size = cols * img.image.elemSize();
            for (int i = 0; i < rows; ++i) {
                file.write(reinterpret_cast<char const *>(img.image.ptr(i)),
                           size);
            }
        }
    }
    file.close();
    return 0;
}

double FILEWR::getTimeDifference(
    std::chrono::high_resolution_clock::time_point time1,
    std::chrono::high_resolution_clock::time_point time2) {
    return std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1)
               .count() /
           1000.0;
}