#include <Algorithm/image_allign/FeatureDetector.hpp>
#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>


// File path
std::string data_path = "../../../data/";
std::string vid_path = data_path + "align1.mp4";
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
    int count = 0;
    // Read the first frame
    cv::Mat firstFrame;
    cap >> firstFrame;

    cv::Size resizesize = cv::Size(640, 480);

    cv::resize(firstFrame, firstFrame, resizesize);

    std::chrono::steady_clock::time_point begin =
        std::chrono::steady_clock::now();

    while (count != 6) {
        cv::Mat frame;
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
            break;

        cv::resize(frame, frame, resizesize);

        // Run the feature detection and matching algorithm
        detector.allign(firstFrame, frame);

        // Get and display the alligned image
        cv::Mat res = detector.GetAllignedImage();
        cv::imshow("Frame", res);

        // Press  ESC on keyboard to exit
        char c = (char)cv::waitKey(25);
        if (c == 27)
            break;
        count++;
    }

    std::chrono::steady_clock::time_point end =
        std::chrono::steady_clock::now();

    std::cout << "Time difference = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                       begin)
                     .count()
              << "[ms]" << std::endl;

    cap.release();

    return 0;
}