#include <Algorithm/object_detection/ObjectDetection.hpp>

ObjectDetection::ObjectDetection(cv::RNG rng, int maxCorners) : rng(rng) {
    this->maxCorners = maxCorners;
    for (int i = 0; i < maxCorners; i++) {
        colors.push_back(cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255),
                                    rng.uniform(0, 255)));
    }
}

ObjectDetection::ObjectDetection(cv::RNG rng) : ObjectDetection(rng, 1000) {}

void ObjectDetection::runDetection(const std::vector<ImgData> &imgData) {
    cv::Mat firstImage = imgData[0].image;
    initOpticalFlow(firstImage);
    for (int i = 1; i < imgData.size(); i++) {
        refreshVectors();
        frame = imgData[i].image;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::calcOpticalFlowPyrLK(oldGray, gray, oldPoints, points, status, err);

        std::vector<cv::Point2f> goodPoints;
        std::vector<int> deletedIDs;

        for (uint i = 0; i < oldPoints.size(); i++) {
            if (isPointValid(i)) {
                goodPoints.push_back(points[i]);
                opticalFlowPoints[i].push_back(points[i]);
                continue;
            }
            deletedIDs.push_back(i);
        }

        if (deletedIDs.size() > 0) {
            removeUntrackedPoints(deletedIDs);
        }

        copyOldData(goodPoints);
    }
}

cv::Rect ObjectDetection::GetRect(const std::vector<cv::Point2f> &points) {
    return cv::boundingRect(points);
}

void ObjectDetection::SetMinPointDistance(double minPointDistance) {
    this->minPointDistance = minPointDistance;
}

// std::vector<cv::Point2f>
// ObjectDetection::GetBottomLine(const std::vector<cv::Point2f> &points,
//                                int width) {
//     std::vector<cv::Point2f> bottomLine;
//     cv::Rect rect = GetRect(points);
//     bottomLine.push_back(
//         cv::Point2f(0, static_cast<float>(rect.y + rect.height)));
//     bottomLine.push_back(cv::Point2f(static_cast<float>(width),
//                                      static_cast<float>(rect.y +
//                                      rect.height)));
//     return bottomLine;
// }

std::vector<cv::Point2f>
ObjectDetection::GetBottomLine(const std::vector<cv::Point2f> &points,
                               int width) {
    std::vector<cv::Point2f> bottomLine;
    std::vector<cv::Point2f> tmp;
    tmp.assign(points.begin(), points.end());
    std::sort(tmp.begin(), tmp.end(),
              [](cv::Point2f a, cv::Point2f b) { return a.y > b.y; });
    cv::Point2f mostBottomLine = tmp.front();
    bottomLine.push_back(cv::Point2f(0, mostBottomLine.y));
    bottomLine.push_back(
        cv::Point2f(static_cast<float>(width), mostBottomLine.y));
    return bottomLine;
}

std::vector<std::vector<cv::Point2f>> ObjectDetection::GetOFPoints(
    const std::vector<std::vector<cv::Point2f>> &opticalFlowPoints, int count) {
    std::vector<std::vector<cv::Point2f>> result;
    result.assign(opticalFlowPoints.begin(),
                  opticalFlowPoints.begin() + count + 1);
    return result;
}

std::vector<std::vector<cv::Point2f>>
ObjectDetection::GetOpticalFlowPoints(bool reshape) {
    return reshape ? reshapeVectors(opticalFlowPoints) : opticalFlowPoints;
}

void ObjectDetection::initOpticalFlow(cv::Mat &frame) {
    oldFrame = frame.clone();
    cv::cvtColor(oldFrame, oldGray, cv::COLOR_BGR2GRAY);
    cv::Mat mask = cv::Mat::zeros(oldFrame.size(), oldFrame.type());

    cv::goodFeaturesToTrack(oldGray, oldPoints, maxCorners, qualityLevel,
                            minDistance, cv::Mat(), blockSize,
                            useHarrisDetector, k);

    for (cv::Point2f p : oldPoints) {
        std::vector<cv::Point2f> tmp;
        tmp.push_back(p);
        opticalFlowPoints.push_back(tmp);
    }
}

void ObjectDetection::copyOldData(std::vector<cv::Point2f> goodPoints) {
    oldGray = gray.clone();
    oldPoints.clear();
    oldPoints.assign(goodPoints.begin(), goodPoints.end());
}

bool ObjectDetection::isPointValid(int i) {
    return status[i] == 1 &&
           distance(oldPoints[i], points[i]) >= minPointDistance;
}

void ObjectDetection::removeUntrackedPoints(std::vector<int> &deletedIDs) {
    opticalFlowPoints.erase(
        std::remove_if(opticalFlowPoints.begin(), opticalFlowPoints.end(),
                       [&](std::vector<cv::Point2f> &v) {
                           return std::find(deletedIDs.begin(),
                                            deletedIDs.end(),
                                            &v - &opticalFlowPoints[0]) !=
                                  deletedIDs.end();
                       }),
        opticalFlowPoints.end());
}

double ObjectDetection::distance(cv::Point2f p1, cv::Point2f p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void ObjectDetection::refreshVectors() {
    points.clear();
    status.clear();
    err.clear();
}

std::vector<std::vector<cv::Point2f>> ObjectDetection::reshapeVectors(
    std::vector<std::vector<cv::Point2f>> &vectors) {
    std::vector<std::vector<cv::Point2f>> reshapedVectors;
    std::cout << "vectors.size() = " << vectors.size() << std::endl;
    std::cout << "vectors[0].size() = " << vectors[0].size() << std::endl;
    for (int i = 0; i < vectors[i].size(); i++) {
        std::vector<cv::Point2f> tmp;
        for (int j = 0; j < vectors.size(); j++) {
            tmp.push_back(vectors[j][i]);
        }
        reshapedVectors.push_back(tmp);
    }
    std::cout << "reshapedVectors.size() = " << reshapedVectors.size()
              << std::endl;
    std::cout << "reshapedVectors[0].size() = " << reshapedVectors[0].size()
              << std::endl;
    return reshapedVectors;
}
