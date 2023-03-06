#include <Utils/FileReader/fileH264.hpp>

FILEH264::FILEH264(/* args */) {}

FILEH264::~FILEH264() {}

void FILEH264::ReadFile(std::string path, std::vector<ImageData> &imgData) {
    cv::VideoCapture cap(path);

    if (!cap.isOpened()) {
        std::cout << "Could not open video file" << std::endl;
        exit(1);
    }

    int capFPS = cap.get(cv::CAP_PROP_FPS);

    cv::Mat frame;

    std::chrono ::high_resolution_clock::time_point startTime =
        std::chrono::high_resolution_clock::now();
    int frameCount = 0;

    while (cap.read(frame)) {
        cv::Mat frameCopy = frame.clone();
        std::chrono ::high_resolution_clock::time_point time =
            startTime +
            std::chrono::milliseconds((int)(frameCount * 1000.0 / capFPS));
        imgData.push_back({frameCopy, time});
        frameCount++;
    }

    std::cout << "Read file " << path << std::endl;
    cap.release();
    std::cout << "Release file " << path << std::endl;
}

void FILEH264::ReadFile(wxString path, std::vector<ImageData> &imgData) {
    std::string s = std::string(path.mb_str(wxConvUTF8));
    ReadFile(s, imgData);
}

void FILEH264::ReadFile(std::string path, std::vector<ImageData> *imgData) {
    cv::VideoCapture cap(path);

    if (!cap.isOpened()) {
        std::cout << "Could not open video file" << std::endl;
        exit(1);
    }

    int capFPS = cap.get(cv::CAP_PROP_FPS);

    cv::Mat frame;

    std::chrono ::high_resolution_clock::time_point startTime =
        std::chrono::high_resolution_clock::now();
    int frameCount = 0;

    while (cap.read(frame)) {
        cv::Mat frameCopy = frame.clone();
        std::chrono ::high_resolution_clock::time_point time =
            startTime +
            std::chrono::milliseconds((int)(frameCount * 1000.0 / capFPS));
        imgData->push_back({frameCopy, time});
        frameCount++;
    }

    std::cout << "Read file " << path << std::endl;
    cap.release();
    std::cout << "Release file " << path << std::endl;
}

double FILEH264::getTimeDifference(
    std::chrono::high_resolution_clock::time_point time1,
    std::chrono::high_resolution_clock::time_point time2) {
    return std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1)
               .count() /
           1000.0;
}