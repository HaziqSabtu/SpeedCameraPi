#include "ObjectTracker.hpp"
#include <cstring>
#include <iostream>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>

using namespace std;
using namespace cv;
int main(int argc, char **argv) {

    // declares all required variables
    Rect roi;
    Mat frame, copy;
    vector<Mat> cropList;
    int count = 0;
    // create a tracker object
    // set input video
    string path = "C:/Users/kakik/Desktop/P1/data/highway2.mp4";
    VideoCapture cap(path);
    // get bounding box
    cap >> frame;
    roi = selectROI("tracker", frame);
    // quit if ROI was not selected
    if (roi.width == 0 || roi.height == 0)
        return 0;
    // initialize the tracker
    OBJECTTRACKER tracker = OBJECTTRACKER(frame, roi, "CSRT");

    // perform the tracking process
    printf("Start the tracking process, press ESC to quit.\n");
    for (;;) {
        // get frame from the video
        cap >> frame;
        copy = frame.clone();

        // stop the program if no more images
        if (frame.rows == 0 || frame.cols == 0)
            break;
        // update the tracking result
        roi = tracker.TrackNext(frame);
        if (count % 20 == 0) {
            cout << "Frame: " << count << endl;

            cropList.push_back(copy(roi));
        }
        // draw the tracked object
        rectangle(frame, roi, Scalar(255, 0, 0), 2, 1);
        // show image with the tracked object
        imshow("tracker", frame);
        // imshow("crop", crop);
        count++;
        if (count == 200) {
            break;
        }
        // quit on ESC button
        if (waitKey(1) == 27)
            break;
    }
    for (int i = 0; i < cropList.size(); i++) {
        string name = format("window%d", i);
        imshow(name, cropList[i]);
    }
    // imshow("crop", cropList[1]);
    waitKey(0);
    return 0;
}

// todo look for dominant color
// color quantinazation
// https://docs.opencv.org/3.4/d3/d50/group__imgproc__colormap.html