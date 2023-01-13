#include "ORBDetection.hpp"
#include "SIFTdetection.hpp"

#include <chrono>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

// int main(int argc, char **argv) {

//     char *file = "high";
//     char *ext = ".jpg";
//     double resizeRatio = 0.45;

//     string path = "C:/Users/kakik/Desktop/P1/data/";
//     string path1 = format("%s%s1%s", path.c_str(), file, ext);
//     string path2 = format("%s%s2%s", path.c_str(), file, ext);

//     Mat image1, image2;
//     cout << "OpenCV version: " << CV_VERSION << endl;
//     Mat src1 = imread(path1); // Read the file
//     Mat src2 = imread(path2); // Read the file

//     if (!src1.data || !src2.data) // Check for invalid input
//     {
//         cout << "Could not open or find the image" << std::endl;
//         return -1;
//     }

//     resize(src1, image1, Size(), resizeRatio, resizeRatio, INTER_LINEAR);
//     resize(src2, image2, Size(), resizeRatio, resizeRatio, INTER_LINEAR);

//     ORBDetection d;
//     d.run(image1, image2);

//     SIFTDetection s;
//     s.run(image1, image2);

//     waitKey(0); // Wait for a keystroke in the window
//     return 0;
// }

int main() {
    cout << "Hello World" << endl;
    string path = "C:/Users/kakik/Desktop/P1/data/vid/sudkreuz1.mp4";
    double resizeRatio = 1;
    VideoCapture video(path);

    int frame_width = video.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = video.get(cv::CAP_PROP_FRAME_HEIGHT);
    int fps = video.get(cv::CAP_PROP_FPS);
    cv::VideoWriter writer(
        "C:/Users/kakik/Desktop/P1/data/vid/sudkreuzWOFill.wmv",
        cv::VideoWriter::fourcc('M', 'P', '4', '2'), fps,
        cv::Size(frame_width * resizeRatio, frame_height * resizeRatio));

    if (!video.isOpened())
        return -1;

    Mat frame1, frame2, image1, image2, fillOutput;

    while (video.read(frame1)) {
        // std::chrono::steady_clock::time_point begin =
        //     std::chrono::steady_clock::now();

        if (!frame2.data) {
            cout << "No data" << endl;
            frame2 = frame1;
            resize(frame2, image2, Size(), resizeRatio, resizeRatio,
                   INTER_LINEAR);

            continue;
        }

        resize(frame1, image1, Size(), resizeRatio, resizeRatio, INTER_LINEAR);

        ORBDetection d;
        // d.run(image2, image1);

        SIFTDetection s;
        s.run(image2, image1);

        fillOutput = s.getTransform();

        // std::chrono::steady_clock::time_point end =
        //     std::chrono::steady_clock::now();

        // std::cout << "Time difference = "
        //           << std::chrono::duration_cast<std::chrono::microseconds>(
        //                  end - begin)
        //                  .count()
        //           << "[µs]" << std::endl;
        writer.write(fillOutput);

        if (cv::waitKey(25) >= 0)
            break;
    }

    video.release();
    writer.release();

    cv::destroyAllWindows();

    return 0;
}
