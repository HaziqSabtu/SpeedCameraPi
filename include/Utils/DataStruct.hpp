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

#include <chrono>
#include <opencv2/opencv.hpp>

struct ImageData {
    cv::Mat image;
    std::chrono::high_resolution_clock::time_point time;

    ImageData() {}

    ImageData(cv::Mat image,
              std::chrono::high_resolution_clock::time_point time)
        : image(image), time(time) {}

    ImageData(cv::Mat image)
        : image(image), time(std::chrono::high_resolution_clock::now()) {}

    double TimeDiff(ImageData &data) {
        return std::chrono::duration_cast<std::chrono::microseconds>(time -
                                                                     data.time)
            .count();
    }
};

struct SpeedData {
    cv::Mat image;
    std::chrono::high_resolution_clock::time_point time;
    std::vector<cv::Point2f> points;

    cv::Point2f BottomLine() {
        // same Implementation as in ObjectDetection
        std::vector<cv::Point2f> tmp;
        tmp.assign(points.begin(), points.end());
        std::sort(tmp.begin(), tmp.end(),
                  [](cv::Point2f a, cv::Point2f b) { return a.y > b.y; });
        return tmp.front();
    }
};

namespace Detection {
struct Line {
    cv::Point2f p1;
    cv::Point2f p2;

    Line(cv::Point2f p1, cv::Point2f p2) : p1(p1), p2(p2) {}

    Line(cv::Vec4i line)
        : p1(cv::Point2f(line[0], line[1])), p2(cv::Point2f(line[2], line[3])) {
    }

    double Length() { return cv::norm(p1 - p2); }

    double Slope() { return (p2.y - p1.y) / (p2.x - p1.x); }

    double Angle() { return atan2(p2.y - p1.y, p2.x - p1.x); }

    double Distance(cv::Point2f p) {
        double a = p1.y - p2.y;
        double b = p2.x - p1.x;
        double c = p1.x * p2.y - p2.x * p1.y;
        return abs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
    }

    cv::Point2f Intersection(Line line) {
        double x1 = p1.x;
        double y1 = p1.y;
        double x2 = p2.x;
        double y2 = p2.y;
        double x3 = line.p1.x;
        double y3 = line.p1.y;
        double x4 = line.p2.x;
        double y4 = line.p2.y;

        double x = ((x1 * y2 - y1 * x2) * (x3 - x4) -
                    (x1 - x2) * (x3 * y4 - y3 * x4)) /
                   ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));
        double y = ((x1 * y2 - y1 * x2) * (y3 - y4) -
                    (y1 - y2) * (x3 * y4 - y3 * x4)) /
                   ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));

        return cv::Point2f(x, y);
    }

    Line Extrapolate(int height, int width) {
        cv::Point2f p1;
        cv::Point2f p2;

        p1 = Intersection(Line(cv::Point2f(0, 0), cv::Point2f(width, 0)));
        p2 = Intersection(
            Line(cv::Point2f(0, height), cv::Point2f(width, height)));

        return Line(p1, p2);
    }

    Line Extrapolate(cv::Mat image) {
        return Extrapolate(image.rows, image.cols);
    }

    bool isIntersect(cv::Point2f p, int radius) {
        double dx = p2.x - p1.x;
        double dy = p2.y - p1.y;

        double a = dx * dx + dy * dy;
        double b = 2 * (dx * (p1.x - p.x) + dy * (p1.y - p.y));
        double c = p.x * p.x + p.y * p.y + p1.x * p1.x + p1.y * p1.y -
                   2 * (p.x * p1.x + p.y * p1.y) - radius * radius;

        double delta = b * b - 4 * a * c;

        if (delta < 0) {
            return false;
        }

        double t1 = (-b + sqrt(delta)) / (2 * a);
        double t2 = (-b - sqrt(delta)) / (2 * a);

        // Check if either t1 or t2 is within the range [0, 1]
        if ((t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1)) {
            return true;
        }
        return false;
    }

    static Line Average(std::vector<Detection::Line> lines) {
        cv::Point2f p1;
        cv::Point2f p2;

        for (auto line : lines) {
            p1 += line.p1;
            p2 += line.p2;
        }

        p1 /= static_cast<float>(lines.size());
        p2 /= static_cast<float>(lines.size());

        return Line(p1, p2);
    }
};

struct HoughData {
    cv::Mat canny;
    std::vector<Detection::Line> lines;

    HoughData(cv::Mat canny, std::vector<Detection::Line> lines)
        : canny(canny), lines(lines) {}

    HoughData() {}
};
} // namespace Detection

#endif