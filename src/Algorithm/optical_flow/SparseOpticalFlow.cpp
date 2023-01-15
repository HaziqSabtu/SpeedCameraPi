#include <Algorithm/optical_flow/SparseOpticalFlow.hpp>

SparseOF::SparseOF() : criteria(criteriaType, maxCount, epsilon), rng() {
    for (int i = 0; i < 100; i++) {
        int r = rng.uniform(0, 256);
        int g = rng.uniform(0, 256);
        int b = rng.uniform(0, 256);
        colors.push_back(cv::Scalar(r, g, b));
    }
}

SparseOF::~SparseOF() {}

void SparseOF::setInitialPoints() {
    cv::goodFeaturesToTrack(prevGray, initialPoints, maxCorners, qualityLevel,
                            minDistance, cv::Mat(), blockSize,
                            useHarrisDetector, k);

    // todo: fix cornerSubPix to increase accuracy
    cv::cornerSubPix(prevGray, initialPoints, cv::Size(5, 5), cv::Size(-1, -1),
                     criteria);
}

void SparseOF::setRoiPoints(const cv::Rect &roi) {
    this->roi = roi;
    for (int i = 0; i < initialPoints.size(); i++) {
        if (roi.contains(initialPoints[i])) {
            roiPoints.push_back(initialPoints[i]);
        }
    }
    pushCollection(roiPoints);
}

void SparseOF::Init(const cv::Mat &frame, cv::Rect &roi) {
    if (!prevGray.empty()) {
        prevGray.release();
    }

    cv::cvtColor(frame, prevGray, cv::COLOR_BGR2GRAY);
    setInitialPoints();
    setRoiPoints(roi);

    if (mask.empty()) {
        mask = cv::Mat::zeros(frame.size(), frame.type());
    }
}

void SparseOF::run(const cv::Mat &frame) {
    clearVector();

    cv::Mat frameGray;
    cv::cvtColor(frame, frameGray, cv::COLOR_BGR2GRAY);

    cv::calcOpticalFlowPyrLK(prevGray, frameGray, roiPoints, trackingPoints,
                             status, err);
    pushCollection(trackingPoints, status, err);
    drawPoints(frame);

    updatePrevVariables(frameGray, trackingPoints);
}

void SparseOF::drawPoints(const cv::Mat &frame) {
    cv::Mat t = frame.clone();
    for (int i = 0; i < trackingPoints.size(); i++) {
        cv::line(mask, trackingPoints[i], roiPoints[i], colors[i], 2);
        cv::circle(t, trackingPoints[i], 5, colors[i], -1);
    }
    cv::add(t, mask, output);
}

void SparseOF::updatePrevVariables(const cv::Mat &g,
                                   const std::vector<cv::Point2f> &p) {
    prevGray.release();
    g.copyTo(prevGray);

    roiPoints.assign(p.begin(), p.end());
}

void SparseOF::pushCollection(std::vector<cv::Point2f> &points) {
    std::vector<PointData> pointData;
    for (int i = 0; i < points.size(); i++) {
        pointData.push_back(PointData{points[i], 1});
    }
    collection.push_back(pointData);
}

void SparseOF::pushCollection(std::vector<cv::Point2f> &points,
                              std::vector<uchar> &status,
                              std::vector<float> &err) {
    std::vector<PointData> pointData;
    for (int i = 0; i < points.size(); i++) {
        pointData.push_back(PointData{points[i], status[i], err[i]});
    }
    collection.push_back(pointData);
}

void SparseOF::clearVector() {
    status.clear();
    err.clear();
    trackingPoints.clear();
    // good_new.clear();
}

void SparseOF::frameSkip(std::vector<std::vector<PointData>> &pointData,
                         int skip) {
    std::vector<std::vector<PointData>> temp;
    for (int i = 0; i < pointData.size(); i++) {
        if (i % skip == 0) {
            temp.push_back(pointData[i]);
        }
    }
    pointData = temp;
}

bool SparseOF::isInitPointValid(const int LIMIT) {
    if (roiPoints.size() == 0) {
        std::cout << "No Points Available for Tracking" << std::endl;
        return false;
    }

    if (roiPoints.size() < LIMIT) {
        std::cout << "Not Enough Points Available for Tracking" << std::endl;
        return false;
    }
    return true;
}

std::vector<std::vector<PointData>> SparseOF::evaluateCollection() {
    std::vector<std::vector<PointData>> pass =
        std::vector<std::vector<PointData>>(collection.size());
    std::vector<int> passPos;
    for (int i = 0; i < collection[0].size(); i++) {
        for (int j = 0; j < collection.size(); j++) {
            if (collection[j][i].status == 1) {
                if (collection[j][i].err > MAXERROR) {
                    break;
                }
            }
            if (j == collection.size() - 1) {
                passPos.push_back(i);
            }
        }
    }

    for (auto &pos : passPos) {
        // std::cout << "Pass: " << pos << std::endl;
        for (int i = 0; i < collection.size(); i++) {
            pass[i].push_back(collection[i][pos]);
        }
    }
    // std::cout << "Pass Size: " << pass.size() << std::endl;
    // std::cout << "Pass[0] Size: " << pass[0].size() << std::endl;

    // std::cout << "Collection Size: " << collection.size() << std::endl;
    // std::cout << "Collection[0] Size: " << collection[0].size() << std::endl;
    return pass;
}

std::vector<std::vector<PointData>> SparseOF::getCollection() {
    return collection;
};

cv::Rect SparseOF::getRoi() { return roi; }

cv::Mat SparseOF::getOutput() { return output; }

cv::Mat SparseOF::getMask() { return mask; }
