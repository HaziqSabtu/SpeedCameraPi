#include <Algorithm/hsv_filter/BFS.hpp>

BFS::BFS(cv::Point start) { this->start = start; }

BFS::BFS() { BFS(cv::Point(-1, -1)); }

cv::Mat BFS::run(cv::Mat &src) {
    cv::Mat returnMat = cv::Mat::zeros(src.size(), CV_8UC1);

    if (!isStartDefined()) {
        return returnMat;
    }

    cv::Mat dst = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
    cv::Mat visited = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
    std::queue<Nodes> q(std::deque<Nodes> {Nodes(start)});

    while (!q.empty()) {
        Nodes n = q.front();
        cv::Point p = n.p;
        q.pop();

        if (visited.at<uchar>(p.y, p.x) == 1) {
            continue;
        }

        visited.at<uchar>(p.y, p.x) = 1;

        cv::Vec3b current = src.at<cv::Vec3b>(p.y, p.x);
        cv::Vec3b parent = src.at<cv::Vec3b>(n.parent.y, n.parent.x);

        if (withinDistance(current, parent, 10.0)) {
            dst.at<uchar>(p.y, p.x) = 255;
            p.x + 1 < src.cols ? q.push(Nodes(cv::Point(p.x + 1, p.y), p))
                               : void();
            p.x - 1 >= 0 ? q.push(Nodes(cv::Point(p.x - 1, p.y), p)) : void();
            p.y + 1 < src.rows ? q.push(Nodes(cv::Point(p.x, p.y + 1), p))
                               : void();
            p.y - 1 >= 0 ? q.push(Nodes(cv::Point(p.x, p.y - 1), p)) : void();
        }
    }

    return dst;
}

bool BFS::isStartDefined() { return (start.x != -1 && start.y != -1); }

void BFS::setStart(cv::Point start) { this->start = start; }

cv::Point BFS::getStart() { return start; }

bool BFS::withinDistance(const cv::Vec3b &a, const cv::Vec3b &b,
                         double distance) {
    double hue_a = static_cast<double>(a[0]);
    double hue_b = static_cast<double>(b[0]);

    // Calculate the shortest angular distance between hue_a and hue_b
    double hue_distance =
        std::min(std::abs(hue_a - hue_b), 180.0 - std::abs(hue_a - hue_b));

    double dist =
        std::sqrt(std::pow(hue_distance, 2) + std::pow(a[1] - b[1], 2) +
                  std::pow(a[2] - b[2], 2));

    return (dist <= distance);
}
