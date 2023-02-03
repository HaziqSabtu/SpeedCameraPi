#include <Algorithm/speed_calculation/speedCalculation.hpp>

SpeedCalculation::SpeedCalculation() {}

void SpeedCalculation::runCalculation(std::vector<SpeedData> speedData) {
    if (line.size() != 2) {
        wxLogMessage("Line Size Error");
        return;
    }

    if (speedData.size() == 0) {
        wxLogMessage("No data");
        return;
    }

    wxLogMessage("Calculating speed");
    for (auto l : line) {
        wxLogMessage("Line: %d, %d, %d, %d", l[0], l[1], l[2], l[3]);
    }
    for (int i = 0; i < speedData.size(); i++) {
        wxLogMessage("Image: %d", i);
        wxLogMessage("Time: %lld",
                     std::chrono::duration_cast<std::chrono::milliseconds>(
                         speedData[i].time.time_since_epoch())
                         .count());
        wxLogMessage("Points: %zd", speedData[i].points.size());
    }
}

void SpeedCalculation::SetLine(std::vector<cv::Vec4i> l) { line = l; }

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