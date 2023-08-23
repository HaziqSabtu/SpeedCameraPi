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
#include <iostream>

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

CDVector FILEWR::ReadFileOld(std::string path) {
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

FileReadWrite::FileReadWrite() {}

FileReadWrite::~FileReadWrite() {}

void FileReadWrite::WriteFile(DataPtr data, std::string filename) {

    filename = filename.empty() ? data->getID() : filename;

    auto path = filename + FILE_EXTENSION;

    FileMetaData m;
    m.vectorSize = data->getCaptureData().size();
    m.imgWidth = data->getCaptureData().front().image.cols;
    m.imgHeight = data->getCaptureData().front().image.rows;
    m.isCalibrated = !data->isCalibrationDataEmpty();
    m.isROI = !data->isTrackingDataEmpty();

    std::ofstream file(path, std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Error opening file");
    }

    file.write(FILE_IDENTIFIER.c_str(), FILE_IDENTIFIER.size());

    file.write(reinterpret_cast<char *>(&m), sizeof(m));

    // Write the number of cv::Mat objects in the vector
    auto captureData = data->getCaptureData();

    if (captureData.size() == 0) {
        throw std::runtime_error("Error: No data");
    }

    if (captureData.size() != m.vectorSize) {
        throw std::runtime_error("Error: Vector size mismatch");
    }

    for (auto &i : captureData) {
        if (i.image.cols != m.imgWidth || i.image.rows != m.imgHeight) {
            throw std::runtime_error("Error: Mat size mismatch");
        }
    }

    // Write each cv::Mat's data
    for (const CaptureData &data : captureData) {
        int rows = data.image.rows;
        int cols = data.image.cols;
        int type = data.image.type();

        file.write(reinterpret_cast<const char *>(&rows), sizeof(rows));
        file.write(reinterpret_cast<const char *>(&cols), sizeof(cols));
        file.write(reinterpret_cast<const char *>(&type), sizeof(type));

        // Write timestamp
        auto timestamp = data.time.time_since_epoch().count();
        file.write(reinterpret_cast<const char *>(&timestamp),
                   sizeof(timestamp));

        file.write(reinterpret_cast<const char *>(data.image.data),
                   data.image.total() * data.image.elemSize());
    }

    if (m.isCalibrated) {

        // add divider
        file.write(DATA_DIVIDER.c_str(), DATA_DIVIDER.size());

        CalibrationData calibData = data->getCalibrationData();
        Line left = calibData.lineLeft;
        Line right = calibData.lineRight;

        // verify line
        if (left.isNull() || right.isNull()) {
            throw std::runtime_error("Error: Line is null");
        }

        file.write(reinterpret_cast<const char *>(&left), sizeof(left));
        file.write(reinterpret_cast<const char *>(&right), sizeof(right));
    }

    if (m.isROI) {

        file.write(DATA_DIVIDER.c_str(), DATA_DIVIDER.size());

        TrackingData trackingData = data->getTrackingData();
        cv::Rect roi = trackingData.roi;

        if (roi.area() <= 0) {
            throw std::runtime_error("Error: ROI is not set");
        }

        file.write(reinterpret_cast<const char *>(&roi), sizeof(roi));
    }

    file.close();
}

void FileReadWrite::ReadFile(DataPtr data, std::string filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Error opening file");
    }

    // read identifier
    std::string identifier;
    identifier.resize(FILE_IDENTIFIER.size());
    file.read(&identifier[0], FILE_IDENTIFIER.size());

    if (identifier != FILE_IDENTIFIER) {
        throw std::runtime_error("Error: Invalid file");
    }

    FileMetaData metadata;

    // Read metadata from the file
    file.read(reinterpret_cast<char *>(&metadata), sizeof(metadata));

    // print all
    std::cerr << "Vector size: " << metadata.vectorSize << std::endl;
    std::cerr << "Image width: " << metadata.imgWidth << std::endl;
    std::cerr << "Image height: " << metadata.imgHeight << std::endl;
    std::cerr << "Is calibrated: " << metadata.isCalibrated << std::endl;
    std::cerr << "Is ROI: " << metadata.isROI << std::endl;

    // Read each cv::Mat object
    std::vector<CaptureData> captureData;
    for (size_t i = 0; i < metadata.vectorSize; i++) {
        int rows = 0;
        int cols = 0;
        int type = 0;

        file.read(reinterpret_cast<char *>(&rows), sizeof(rows));
        file.read(reinterpret_cast<char *>(&cols), sizeof(cols));
        file.read(reinterpret_cast<char *>(&type), sizeof(type));

        // Read timestamp
        std::chrono::high_resolution_clock::time_point timestamp;
        file.read(reinterpret_cast<char *>(&timestamp), sizeof(timestamp));

        cv::Mat mat(rows, cols, type);

        file.read(reinterpret_cast<char *>(mat.data),
                  mat.total() * mat.elemSize());

        captureData.push_back({mat, timestamp});
    }

    data->setCaptureData(captureData);

    if (metadata.isCalibrated) {
        // read divider
        std::string divider;
        divider.resize(DATA_DIVIDER.size());
        file.read(&divider[0], DATA_DIVIDER.size());

        if (divider != DATA_DIVIDER) {
            throw std::runtime_error("Error: Invalid file");
        }

        CalibrationData calibData;

        // Read calibration data from the file
        file.read(reinterpret_cast<char *>(&calibData.lineLeft),
                  sizeof(calibData.lineLeft));
        file.read(reinterpret_cast<char *>(&calibData.lineRight),
                  sizeof(calibData.lineRight));

        data->setCalibrationData(calibData);
    }

    if (metadata.isROI) {

        std::string divider;
        divider.resize(DATA_DIVIDER.size());
        file.read(&divider[0], DATA_DIVIDER.size());

        if (divider != DATA_DIVIDER) {
            throw std::runtime_error("Error: Invalid file");
        }

        cv::Rect roi;

        file.read(reinterpret_cast<char *>(&roi), sizeof(roi));

        std::cerr << "ROI: " << roi.x << " " << roi.y << " " << roi.width << " "
                  << roi.height << std::endl;

        TrackingData trackingData;
        trackingData.roi = roi;
        data->setTrackingData(trackingData);
    }

    file.close();
}
