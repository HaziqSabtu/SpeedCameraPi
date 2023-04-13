/**
 * @file fileH264.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Utils Class for reading H264 file and convert it to vector of
 * ImageData
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Utils/FileReader/fileH264.hpp>

/**
 * @brief Construct a new FILEH264::FILEH264 object
 *
 */
FILEH264::FILEH264(/* args */) {}

/**
 * @brief Destroy the FILEH264::FILEH264 object
 *
 */
FILEH264::~FILEH264() {}

/**
 * @brief Read H264 file and convert it to vector of ImageData
 *
 * @param path path to the file in std::string
 * @param imgData result vector of ImageData
 */
void FILEH264::ReadFile(std::string path,
                        std::shared_ptr<std::vector<ImageData>> imgData) {
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
    cap.release();
}