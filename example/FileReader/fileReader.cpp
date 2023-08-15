#include <Algorithm/Object_Detection/OpticalFlowTracker.hpp>
#include <Utils/FileReader/fileWR.hpp>
#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>

// File path
std::string data_path = "../../data/";
// std::string bin_path = data_path + "src.bin";
std::string bin_path =
    "c:/Users/kakik/Desktop/wx_cmake_template/example/Data/src.bin";
std::string dst_path =
    "c:/Users/kakik/Desktop/wx_cmake_template/example/Data/output.mp4";
using namespace std;

std::vector<ImageData> *imgData = new std::vector<ImageData>();

int main() {
    FILEWR::ReadFile(bin_path, imgData);

    cv::VideoWriter writer;
    writer.open(dst_path, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 10,
                imgData->at(0).image.size());

    for (auto &img : *imgData) {
        writer.write(img.image);
    }

    for (auto &img : *imgData) {
        cv::imshow("img", img.image);
        cv::waitKey(200);
    }
    writer.release();
    return 0;
}