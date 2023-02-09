#include <Algorithm/speed_calculation/speedCalculation.hpp>

SpeedCalculation::SpeedCalculation() {}

// SpeedCalculation::SpeedCalculation(int imageWidth) : imageWidth(imageWidth) {
//     std::cout << "imageWidth: " << imageWidth << std::endl;
// }

void SpeedCalculation::runCalculation(std::vector<SpeedData> speedData) {
    if (line.size() != 2) {
        wxLogMessage("Line Size Error");
        return;
    }

    if (speedData.size() == 0) {
        wxLogMessage("No data");
        return;
    }

    speeds.clear();
    int i = 0;
    for (SpeedData data : speedData) {

        cv::Point2f bottom = data.BottomLine();
        cv::Point2f intersection1 = intersection(bottom.y, line[0]);
        cv::Point2f intersection2 = intersection(bottom.y, line[1]);

        double pixelDist = fabs(intersection1.x - intersection2.x);
        double dist1 = distanceFromCamera(pixelDist);
        wxLogMessage("####################");
        wxLogMessage("%d: Distance: %f", i, dist1);

        if (prevDistFromCamera != -1) {
            double speed =
                calcSpeed(prevDistFromCamera, dist1, prevTime, data.time);
            wxLogMessage("Speed: %f", speed);
            speeds.push_back(speed);
        }

        prevDistFromCamera = dist1;
        prevTime = data.time;
        i++;
    }

    double avgSpeed = ImageUtils::TrimmedMean(speeds, 10);

    double measuredSpeed = 0.3 / 1.2;
    // double measuredSpeed = 1200 / 4665.2;
    wxLogMessage("Measured Speed: %f", measuredSpeed);

    double error = fabs(avgSpeed - measuredSpeed) * 100 / measuredSpeed;
    wxLogMessage("Error: %f", error);
}

double SpeedCalculation::distanceFromCamera(float pixelWidth) {
    return (LANE_WIDTH * imageWidth * FocalLength) / (pixelWidth * SensorWidth);
}

void SpeedCalculation::SetLine(std::vector<cv::Vec4i> l) { line = l; }

void SpeedCalculation::SetImageWidth(int w) { this->imageWidth = w; }

std::vector<SpeedData>
SpeedCalculation::toSpeedData(std::vector<ImgData> &imgData,
                              std::vector<std::vector<cv::Point2f>> &points) {
    std::vector<SpeedData> speedData;
    for (int i = 0; i < imgData.size(); i++) {
        SpeedData data;
        data.image = imgData[i].image;
        data.time = imgData[i].time;
        data.points = points[i];
        speedData.push_back(data);
    }
    return speedData;
}

cv::Point2f SpeedCalculation::intersection(float y, cv::Vec4i b) {
    cv::Vec4f b2(b[0], b[1], b[2], b[3]);
    cv::Vec4f a(0, y, 1, y);
    return intersection(a, b2);
}

cv::Point2f SpeedCalculation::intersection(cv::Vec4f a, cv::Vec4f b) {
    cv::Point2f p;
    float x1 = a[0], y1 = a[1], x2 = a[2], y2 = a[3];
    float x3 = b[0], y3 = b[1], x4 = b[2], y4 = b[3];
    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (d == 0) {
        return cv::Point2f(-1, -1);
    }
    p.x =
        ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / d;
    p.y =
        ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / d;
    return p;
}

double SpeedCalculation::calcSpeed(
    double prevDist, double curDist,
    std::chrono::high_resolution_clock::time_point prevTime,
    std::chrono::high_resolution_clock::time_point curTime) {
    double distDiff = fabs(curDist - prevDist);
    double timeDiff = FILEAVI::getTimeDifference(prevTime, curTime);
    wxLogMessage("DistDiff: %f", distDiff);
    wxLogMessage("TimeDiff: %f", timeDiff);
    return distDiff / timeDiff;
}
