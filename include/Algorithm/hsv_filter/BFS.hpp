#pragma once

#include <Algorithm/hsv_filter/Nodes.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <queue>

class BFS {
  private:
    cv::Point start;

  public:
    BFS(cv::Point start);
    BFS();

    cv::Mat run(cv::Mat &src);

    bool isStartDefined();
    void setStart(cv::Point start);
    cv::Point getStart();

    bool withinDistance(const cv::Vec3b &a, const cv::Vec3b &b,
                        double distance);
};
