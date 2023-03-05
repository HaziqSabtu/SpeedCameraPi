/**
 * @file Homography.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Helper Class for running Homography based on the result from Feature
 * Detection
 * @version 1.0.0
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Algorithm/image_allign/Homography.hpp>

/**
*@brief Computes the homography matrix between two sets of keypoints and
computes the good matches between them.
*@details https://docs.opencv.org/3.4/d9/d0c/group__calib3d.html for more information
*
*@param keypoints_obj The keypoints in the first image.
*@param keypoints_scene The keypoints in the second image.
*@param matches The output vector of good matches between keypoints_obj and
keypoints_scene.
*@return The homography matrix that transforms the second image to align
with the first image.
*/
cv::Mat Homography::FindHomography(std::vector<cv::KeyPoint> keypoints_obj,
                                   std::vector<cv::KeyPoint> keypoints_scene,
                                   std::vector<cv::DMatch> &matches) {
    std::vector<cv::Point2f> obj;
    std::vector<cv::Point2f> scene;

    for (int i = 0; i < matches.size(); i++) {
        obj.push_back(keypoints_obj[matches[i].queryIdx].pt);
        scene.push_back(keypoints_scene[matches[i].trainIdx].pt);
    }
    return cv::findHomography(scene, obj, cv::RANSAC);
}

/**
*@brief Applies a perspective transformation to the target image using the
* specified homography matrix.
*
*@param target The image to be transformed.
*@param M The homography matrix that defines the transformation.
*
*@return The transformed image.
*/
cv::Mat Homography::PerscpectiveTransform(cv::Mat &target, cv::Mat &M) {
    cv::Mat transform;
    cv::warpPerspective(target, transform, M, target.size(), cv::INTER_LINEAR,
                        cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
    return transform;
}

/**
 * @brief Fill the transformed image on top of the background image
 *
 * @param bg Background image to fill the transformed image on top of
 * @param target Transformed image to be filled
 * @param M Homography matrix used to transform the target image
 * @return result transformed image filled on top of the background image
 */
cv::Mat Homography::FillTransform(cv::Mat &bg, cv::Mat &target, cv::Mat &M) {
    cv::Mat mask = cv::Mat::zeros(target.size(), target.type());
    cv::Mat inverse_mask, combine, result;

    std::vector<cv::Point2f> obj_corners(4);
    std::vector<cv::Point2f> scene_corners(4);
    std::vector<cv::Point2i> scene_corners_int(4);

    obj_corners[0] = cv::Point(0, 0);
    obj_corners[1] = cv::Point(bg.cols, 0);
    obj_corners[2] = cv::Point(bg.cols, bg.rows);
    obj_corners[3] = cv::Point(0, bg.rows);

    cv::perspectiveTransform(obj_corners, scene_corners, M);

    cv::Mat(scene_corners).convertTo(scene_corners_int, CV_32S);

    cv::fillConvexPoly(mask, scene_corners_int, cv::Scalar(255, 255, 255));

    bitwise_not(mask, inverse_mask);
    bitwise_and(bg, inverse_mask, combine);
    bitwise_or(target, combine, result);
    return result;
}