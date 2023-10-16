/**
 * @file DataStruct.hpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom Data Structures
 * @version 1.0.0
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <Algorithm/object_tracker/OpticalFlowData.hpp>
#include <chrono>
#include <opencv2/opencv.hpp>

#define ImageDataPtr std::shared_ptr<std::vector<ImageData>>

/**
 * @brief Struct for ImageData
 *
 */
// struct ImageData {
//     cv::Mat image;
//     std::chrono::high_resolution_clock::time_point time;

//     AllignData allign;

//     Detection::HoughData hough;

//     OpticalFlowData flow;

//     DetectionData detection;

//     ImageData() {}

//     ImageData(cv::Mat image,
//               std::chrono::high_resolution_clock::time_point time)
//         : image(image), time(time), allign(), hough(), flow(), detection() {}

//     ImageData(cv::Mat image)
//         : image(image), time(std::chrono::high_resolution_clock::now()),
//           allign(), hough(), flow(), detection() {}

//     void SetAllign(AllignData allign) { this->allign = allign; }

//     void SetHough(Detection::HoughData hough) { this->hough = hough; }

//     void SetFlow(OpticalFlowData flow) { this->flow = flow; }

//     void SetDetection(DetectionData detection) { this->detection = detection; }

//     OpticalFlowData GetFlow() { return flow; }
// };

// //TODO: Remove this struct
// /**
//  * @brief Struct for SpeedData
//  * @deprecated
//  *
//  */
// struct SpeedData {
//     cv::Mat image;
//     std::chrono::high_resolution_clock::time_point time;
//     std::vector<cv::Point2f> points;

//     cv::Point2f BottomLine() {
//         // same Implementation as in ObjectDetection
//         std::vector<cv::Point2f> tmp;
//         tmp.assign(points.begin(), points.end());
//         std::sort(tmp.begin(), tmp.end(),
//                   [](cv::Point2f a, cv::Point2f b) { return a.y > b.y; });
//         return tmp.front();
//     }
// };

#endif