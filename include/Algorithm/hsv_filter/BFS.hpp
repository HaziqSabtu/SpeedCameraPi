#pragma once

#include <Algorithm/hsv_filter/Nodes.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <queue>

/**
 * @brief A class implementing Breadth-First Search.
 *
 * Breadth-First Search (BFS) is an algorithm used for traversing or searching tree or graph data structures.
 * In this context, the BFS class performs a Breadth-First Search on an image represented as a grid of pixels.
 * It starts from a specified point and explores neighboring pixels in a breadthward motion, making it suitable
 * for tasks like image segmentation, connected component analysis, and more. In this implementation, the BFS
 * class is used to find all pixels in an image that are within a specified distance of a given color.  
 */

class BFS {
  private:
    cv::Point start; /**< The starting point for the search. */
    double distance = 1.0;

  public:
    BFS(cv::Point start);

    BFS();

    cv::Mat run(cv::Mat &src);

    bool isStartDefined();

    void setStart(cv::Point start);

    cv::Point getStart();

  private:
    bool withinDistance(const cv::Vec3b &a, const cv::Vec3b &b,
                        double distance);
};
