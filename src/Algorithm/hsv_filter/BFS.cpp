#include <Algorithm/hsv_filter/BFS.hpp>
#include <iostream>
#include <opencv2/core/hal/interface.h>

/**
 * @brief Construct a new BFS::BFS object
 * 
 * @param start The starting point for the search.
 */
BFS::BFS(cv::Point start) { this->start = start; }

/**
 * @brief Default constructor.
 * 
 */
BFS::BFS() : BFS(cv::Point(-1, -1)) {}

/**
 * @brief Run the BFS on a source image.
 *
 * @param src The source image.
 * @return The result of the BFS operation.
 */
cv::Mat BFS::run(cv::Mat &src) {
    // Create an output matrix initialized with zeros of the same size as src.
    cv::Mat returnMat = cv::Mat::zeros(src.size(), CV_8UC1);

    // If the starting point is not defined, return an empty matrix.
    if (!isStartDefined()) {
        return returnMat;
    }

    // Create a destination matrix and a matrix to keep track of visited pixels.
    cv::Mat dst = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
    cv::Mat visited = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);

    // Initialize a queue with the starting point.
    std::queue<Nodes> q(std::deque<Nodes> {Nodes(start)});

    // Perform Breadth-First Search.
    while (!q.empty()) {
        // Get the node at the front of the queue.
        Nodes n = q.front();
        cv::Point p = n.p;
        q.pop();

        // If the pixel has already been visited, skip it.
        if (visited.at<uchar>(p.y, p.x) == 1) {
            continue;
        }

        // Mark the pixel as visited.
        visited.at<uchar>(p.y, p.x) = 1;

        // Get the color of the current pixel and its parent pixel.
        cv::Vec3b current = src.at<cv::Vec3b>(p.y, p.x);
        cv::Vec3b parent = src.at<cv::Vec3b>(n.parent.y, n.parent.x);

        // Check if the colors are within the specified distance.
        if (withinDistance(current, parent, distance)) {
            // If they are, set the pixel in the destination matrix to 255 (white).
            dst.at<uchar>(p.y, p.x) = 255;

            // Add neighboring pixels to the queue.
            p.x + 1 < src.cols ? q.push(Nodes(cv::Point(p.x + 1, p.y), p))
                               : void();
            p.x - 1 >= 0 ? q.push(Nodes(cv::Point(p.x - 1, p.y), p)) : void();
            p.y + 1 < src.rows ? q.push(Nodes(cv::Point(p.x, p.y + 1), p))
                               : void();
            p.y - 1 >= 0 ? q.push(Nodes(cv::Point(p.x, p.y - 1), p)) : void();
        }
    }

    // Return the resulting image after BFS.
    return dst;
}

/**
 * @brief Checks if the starting point is defined.
 * @return True if the starting point is defined, false otherwise.
 */
bool BFS::isStartDefined() { return (start.x != -1 && start.y != -1); }

/**
 * @brief Set the starting point.
 * @param start The new starting point.
 */
void BFS::setStart(cv::Point start) { this->start = start; }

/**
 * @brief Get the current starting point.
 * @return The starting point.
 */
cv::Point BFS::getStart() { return start; }

/**
 * @brief Check if two colors are within a specified distance.
 *
 * @param a The first color.
 * @param b The second color.
 * @param distance The distance threshold.
 * @return True if the colors are within the distance threshold, false otherwise.
 */
bool BFS::withinDistance(const cv::Vec3b &a, const cv::Vec3b &b,
                         double distance) {
    double hue_a = static_cast<double>(a[0]);
    double hue_b = static_cast<double>(b[0]);

    // Calculate the shortest angular distance between hue_a and hue_b
    double hue_distance =
        std::min(std::abs(hue_a - hue_b), 180.0 - std::abs(hue_a - hue_b));

    double dist = hue_distance;

    return (dist <= distance);
}
