/**
 * @file fileWR.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Utils Class for reading and writing binary file
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Model/SessionData.hpp"
#include <Utils/FileReader/fileWR.hpp>

/**
 * @brief Construct a new FILEWR::FILEWR object
 *
 */
FILEWR::FILEWR(/* args */) {}

/**
 * @brief Destroy the FILEWR::FILEWR object
 *
 */
FILEWR::~FILEWR() {}

/**
 * @brief Read binary file and store it in vector of ImageData
 * @details TODO: check if the file is available and the content is valid
 *
 * @param path path to the file
 * @param imgData vector of ImageData
 */
void FILEWR::ReadFile(std::string path,
                      std::shared_ptr<std::vector<ImageData>> imgData) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return;
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
            imgData->push_back({img, time});
    }
    file.close();
    return;
}

CDVector FILEWR::ReadFile(std::string path) {
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Error opening file");
    }

    CDVector data;

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
            data.push_back({img, time});
    }
    file.close();
    return data;
}

/**
 * @brief Write vector of ImageData to binary file
 * @details only Image and time is written to the file
 *
 * @param imgData vector of ImageData
 */
void FILEWR::WriteFile(std::shared_ptr<std::vector<ImageData>> imgData) {
    // check if file exists
    std::string path = Utils::dateToString() + ".bin";
    WriteFile(path, imgData);
}

void FILEWR::WriteFile(std::string path,
                       std::shared_ptr<std::vector<ImageData>> imgData) {
    std::ofstream file(path, std::ios::binary);

    for (auto img : *imgData) {
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
    return;
}
