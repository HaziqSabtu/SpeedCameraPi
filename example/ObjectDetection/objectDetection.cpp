#include <Algorithm/Object_Detection/OpticalFlowTracker.hpp>
#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>

// File path
std::string data_path = "../../../data/";
std::string vid_path = data_path + "straight2.h264";
using namespace std;

std::unique_ptr<std::vector<ImageData>> imgData =
    std::make_unique<std::vector<ImageData>>();

// Parameters
int maxCorners = 1000;
float threshold = 2.0;

int main() {
    // Create ObjectDetector object

    // Open the video file
    cv::VideoCapture cap(vid_path);
    if (!cap.isOpened()) {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    // Read until video is completed
    while (1) {
        cv::Mat frame;
        // Capture frame-by-frame
        cap >> frame;
        // If the frame is empty, break immediately
        if (frame.empty())
            break;

        // Fill the vector with the frames
        imgData->push_back(ImageData(frame));
    }

    // Run image allignment if necessary
    // ...

    // Create ObjectDetector object
    ObjectDetection objectDetection(maxCorners);

    // Compute the flow for the first frame and then update the flow for the
    // rest of the frames
    imgData->at(0).SetFlow(objectDetection.init(imgData->at(0).image));
    for (int i = 1; i < imgData->size(); i++) {
        imgData->at(i).SetFlow(
            objectDetection.updateFlow(imgData->at(i), imgData->at(i - 1)));
    }

    // Threshold the points
    std::vector<int> ids;
    for (int i = 0; i < imgData->at(0).flow.GetPoints().size(); i++) {
        ids.push_back(i);
    }
    for (int i = 1; i < imgData->size(); i++) {
        imgData->at(i).flow.thresholdPointsId(ids, imgData->at(i - 1).flow,
                                              threshold);
    }

    // Set thresholded points
    for (int i = 0; i < imgData->size(); i++) {
        imgData->at(i).SetDetection(imgData->at(i).flow.GetPointsById(ids));
    }

    // Draw the results
    for (int i = 0; i < imgData->size(); i++) {
        cv::Mat img = imgData->at(i).image;
        cv::Rect rect = imgData->at(i).detection.GetRect();
        cv::rectangle(img, rect, cv::Scalar(0, 0, 255), 2);
        cv::imshow("img", img);
        cv::waitKey(20);
    }

    cap.release();

    return 0;
}