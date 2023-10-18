#pragma once

#include <opencv2/core/types.hpp>

/**
 * @brief Struct representing nodes for a graph-based algorithm.
 * Used within the BFS class for traversal.
 */
struct Nodes {
    cv::Point p;      /**< The current point. */
    cv::Point parent; /**< The parent point. */

    /**
     * @brief Construct a Nodes object with specified current and parent points.
     *
     * @param p The current point.
     * @param parent The parent point.
     */
    Nodes(cv::Point p, cv::Point parent) {
        this->p = p;
        this->parent = parent;
    }

    /**
     * @brief Construct a Nodes object with a specified current point, setting parent to the same point.
     *
     * @param p The current point.
     */
    Nodes(cv::Point p) {
        this->p = p;
        this->parent = p;
    }
};
