#pragma once

#include <opencv2/core/types.hpp>

struct Nodes {
    cv::Point p;
    cv::Point parent;

    Nodes(cv::Point p, cv::Point parent) {
        this->p = p;
        this->parent = parent;
    }

    Nodes(cv::Point p) {
        this->p = p;
        this->parent = p;
    }
};