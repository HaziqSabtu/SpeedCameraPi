#include <Algorithm/image_allign/FeatureDetector.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

// File path
std::string data_path = "../../../data/";
std::string vid_path = data_path + "align1.MOV";
using namespace std;

int main() {
    // Create FeatureDetector object
    FeatureDetector detector;

    // Open the video file
    cv::VideoCapture cap(vid_path);
    if (!cap.isOpened()) {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    // Read the first frame
    cv::Mat firstFrame;
    cap >> firstFrame;

    while (1) {
        cv::Mat frame;
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
            break;

        // Run the feature detection and matching algorithm
        detector.allign(firstFrame, frame);

        // Get and display the alligned image
        cv::Mat res = detector.GetAllignedImage();
        cv::imshow("Frame", res);

        // Press  ESC on keyboard to exit
        char c = (char)cv::waitKey(25);
        if (c == 27)
            break;
    }

    cap.release();

    return 0;
}