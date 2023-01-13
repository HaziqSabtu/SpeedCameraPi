#ifndef DESCRIPTOR_MATCHER_H
#define DESCRIPTOR_MATCHER_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/flann.hpp>
#include <opencv2/xfeatures2d.hpp>

class DESCRIPTORMATCHER {
  public:
    static void BruteForceMatcher(cv::Mat &query, cv::Mat &target,
                                  std::vector<cv::DMatch> &matches,
                                  std::string type, int normType = 0);

    static void getNormType(int normType, cv::NormTypes &normTypes,
                            std::string &typeName);

    static void BruteForceMatcher(cv::Mat &query, cv::Mat &target,
                                  std::vector<std::vector<cv::DMatch>> &matches,
                                  std::string type, int normType = 0);

    static void FlannBasedMatcher(cv::Mat &query, cv::Mat &target,
                                  std::vector<std::vector<cv::DMatch>> &matches,
                                  std::string type);

    // Run Lowe's Ratio Test to remove bad matches on KNN.
    static void
    FilterKeyPoints(std::vector<std::vector<cv::DMatch>> &knnMatches,
                    std::vector<cv::DMatch> &goodMatch, double RATIO = 0.3);
};

// if (descriptors1.type() != CV_32F) {
//     cout << "Converting to CV_32F" << endl;
//     descriptors1.convertTo(descriptors1, CV_32F);
// }
// if (descriptors2.type() != CV_32F) {
//     cout << "Converting to CV_32F" << endl;
//     descriptors2.convertTo(descriptors2, CV_32F);
// }

//   double max_dist = 0; double min_dist = 100;

//   //-- Quick calculation of max and min distances between keypoints
//   for( int i = 0; i < descriptors_object.rows; i++ )
//   { double dist = matches[i].distance;
//     if( dist < min_dist ) min_dist = dist;
//     if( dist > max_dist ) max_dist = dist;
//   }

//   printf("-- Max dist : %f \n", max_dist );
//   printf("-- Min dist : %f \n", min_dist );

//   //-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist
//   ) std::vector< DMatch > good_matches;

//   for( int i = 0; i < descriptors_object.rows; i++ )
//   { if( matches[i].distance < 3*min_dist )
//      { good_matches.push_back( matches[i]); }
//   }
#endif

// todo
// add template for repeated methods
// figure out inline methods
