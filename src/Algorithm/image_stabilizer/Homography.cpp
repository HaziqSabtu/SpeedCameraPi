#include <Algorithm/image_stabilizer/Homography.hpp>

void HOMOGRAPHY::FindHomography(std::vector<cv::KeyPoint> keypoints_obj,
                                std::vector<cv::KeyPoint> keypoints_scene,
                                std::vector<cv::DMatch> &matches,
                                std::vector<cv::Point2f> &obj,
                                std::vector<cv::Point2f> &scene, cv::Mat &H,
                                std::string type) {
    std::cout << "Running FindHomography on:" << type << std::endl;
    for (int i = 0; i < matches.size(); i++) {
        //-- Get the keypoints from the good matches
        obj.push_back(keypoints_obj[matches[i].queryIdx].pt);
        scene.push_back(keypoints_scene[matches[i].trainIdx].pt);
    }

    H = cv::findHomography(scene, obj, cv::RANSAC);
};

void HOMOGRAPHY::PerscpectiveTransform(cv::Mat &target, cv::Mat &transform,
                                       cv::Mat &M) {
    cv::warpPerspective(target, transform, M, target.size(), cv::INTER_LINEAR,
                        cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
}

void HOMOGRAPHY::FillTransform(cv::Mat &bg, cv::Mat &target, cv::Mat &M,
                               cv::Mat &result) {
    cv::Mat mask = cv::Mat::zeros(target.size(), target.type());
    cv::Mat inverse_mask, combine;

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
}