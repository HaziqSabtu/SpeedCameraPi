#include <Algorithm/image_allign/FeatureDetector.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

// File path
std::string data_path = "./";
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

    std::chrono::steady_clock::time_point begin =
        std::chrono::steady_clock::now();
    
    std::vector<cv::Mat> res;

    while (count != 6) {
        cv::Mat frame;
        cap >> frame;

        // If the frame is empty, break immediately
        if (frame.empty())
            break;

        // Run the feature detection and matching algorithm
        detector.allign(firstFrame, frame);

        // Get and display the alligned image
        res.push_back(detector.GetAllignedImage()); 

        // Press  ESC on keyboard to exit

        count++;
    }


    for(cv::Mat img: res){
        cv::imshow("res", img);
        char c = (char)cv::waitKey(0);
        if (c == 27)
            break;
    }

    cap.release();

    return 0;
}