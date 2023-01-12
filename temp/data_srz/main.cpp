#include "fileWR.hpp"
#include <fstream>
#include <iostream>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>

int mode = 1;

int main(int argc, char **argv) {
    if (mode == 1) {
        std::cout << "WRITING" << std::endl;
        std::cout << "OpenCV Version: " << CV_VERSION << std::endl;

        std::string videoPath =
            "C:/Users/kakik/Desktop/P1/data/vid/sudkreuzWOFill.wmv";

        cv::VideoCapture cap(videoPath);

        if (!cap.isOpened()) {
            std::cout << "Could not open video file" << std::endl;
            return -1;
        }

        int fps = cap.get(cv::CAP_PROP_FPS);
        std::vector<ImgData> imgData;

        std::chrono::high_resolution_clock::time_point t1 =
            std::chrono::high_resolution_clock::now();

        cv::Mat frame;
        int count = 0;
        while (cap.read(frame)) {

            if (frame.empty()) {
                break;
            }

            cv::Mat save = frame.clone();
            // if (count % 10 == 0) {
            //     imgData.push_back(
            //         {save, std::chrono::high_resolution_clock::now()});
            // }

            std::chrono::high_resolution_clock::time_point t2 =
                t1 + std::chrono::microseconds(
                         static_cast<int>(count * 1000000.0 / fps));

            imgData.push_back({save, t2});

            cv::imshow("Frame", frame);

            char c = (char)cv::waitKey(25);
            if (c == 27) {
                break;
            }

            count++;
        }

        // show images from imgData
        for (auto &img : imgData) {
            // cv::imshow("Frame", img.image);
            std::cout
                << "Time: "
                << static_cast<double>(
                       std::chrono::duration_cast<std::chrono::microseconds>(
                           img.time - imgData[0].time)
                           .count()) /
                       1000.0
                << std::endl;
            // cv::waitKey(0);
        }

        // save imgData to binary file
        std::string binPath = "C:/Users/kakik/Desktop/P1/data/bin/SWOF.bin";
        if (FILEWR::WriteFile(binPath, imgData) == -1) {
            return -1;
        }
        cap.release();

        std::cout << "Done" << std::endl;
    }

    else {
        std::cout << "READING" << std::endl;
        std::string binPath = "C:/Users/kakik/Desktop/P1/data/bin/car2_720.bin";

        std::vector<ImgData> imgData;

        if (FILEWR::ReadFile(binPath, imgData) == -1) {
            return -1;
        }
        // show images from imgData
        for (auto &img : imgData) {
            cv::imshow("Frame", img.image);
            std::cout
                << "Time: "
                << static_cast<double>(
                       std::chrono::duration_cast<std::chrono::microseconds>(
                           img.time - imgData[0].time)
                           .count()) /
                       1000.0
                << std::endl;
            if (cv::waitKey(0) == 27)
                break;
        }
    }
    return 0;
}