#pragma once

#include "Model/CalibrationData.hpp"
#include "Utils/Config/AppConfig.hpp"
#include <Utils/CommonUtils.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#define DataPtr std::shared_ptr<SessionData>

enum PanelID {
    PANEL_NONE,
    PANEL_CAPTURE,
    PANEL_ROI,
    PANEL_CALIBRATION,
    PANEL_MANUAL_CALIBRATION,
    PANEL_HORIZONTAL_CALIBRATION,
    PANEL_COLOR_CALIBRATION,
    PANEL_TRIM_DATA,
    PANEL_RESULT,
    PANEL_SETTINGS,
    PANEL_INFO
};

enum Mode { MODE_LANE, MODE_DISTANCE };

struct TrackingData {
    cv::Rect roi;

    TrackingData() {}

    TrackingData(cv::Rect roi) : roi(roi) {}

    void clear() { roi = cv::Rect(); }

    bool isInit() { return roi.area() > 0; }

    bool operator==(const TrackingData &other) const {
        return roi == other.roi;
    }

    bool operator!=(const TrackingData &other) const {
        return !(*this == other);
    }

    TrackingData clone() const { return TrackingData(*this); }

    TrackingData &operator=(const TrackingData &other) {
        roi = other.roi;
        return *this;
    }
};

#define HPTime std::chrono::high_resolution_clock::time_point
#define CDVector std::vector<CaptureData>
struct CaptureData {
    cv::Mat image;
    HPTime time;

    CaptureData() {}

    CaptureData(cv::Mat image)
        : image(image), time(std::chrono::high_resolution_clock::now()) {}

    CaptureData(cv::Mat image, HPTime time) : image(image), time(time) {}

    bool operator==(const CaptureData &other) const {
        return Utils::isCvMatSameRandom(image, other.image, 50) &&
               time == other.time;
    }

    CaptureData clone() const { return CaptureData(*this); }

    // Copy assignment operator (deep copy)
    CaptureData &operator=(const CaptureData &other) {
        if (this == &other) // Handle self-assignment
            return *this;

        image = other.image.clone();
        time = other.time;
        return *this;
    }
};

#define ADVector std::vector<AllignData>
struct AllignData {
    cv::Mat image;
    cv::Mat transformMatrix;

    AllignData() {}

    AllignData(cv::Mat image, cv::Mat transformMatrix)
        : transformMatrix(transformMatrix), image(image) {}

    bool operator==(const AllignData &other) const {
        return Utils::isCvMatSame(image, other.image) &&
               Utils::isCvMatSame(transformMatrix, other.transformMatrix);
    }

    AllignData clone() const { return AllignData(*this); }

    // Copy assignment operator (deep copy)
    AllignData &operator=(const AllignData &other) {
        if (this == &other) // Handle self-assignment
            return *this;

        image = other.image.clone();
        transformMatrix = other.transformMatrix.clone();
        return *this;
    }
};

struct ResultData {
    ADVector allignData;
    std::vector<cv::Rect> trackedRoi;

    std::vector<double> speedList;
    std::vector<double> distanceFromCamera;
    std::vector<Line> intersectingLines;
    double speed = -1;

    ResultData() {}

    ResultData(std::vector<double> speedList,
               std::vector<double> distanceFromCamera,
               std::vector<Line> intersectingLines, double speed)
        : speedList(speedList), distanceFromCamera(distanceFromCamera),
          intersectingLines(intersectingLines), speed(speed) {}

    bool isDefined() {
        if (speed == -1) {
            return false;
        }

        if (allignData.empty() || trackedRoi.empty()) {
            return false;
        }

        if (allignData.size() != trackedRoi.size()) {
            return false;
        }

        return true;
    }

    void clear() {
        speed = -1;
        speedList.clear();
        distanceFromCamera.clear();
        intersectingLines.clear();
        allignData.clear();
        trackedRoi.clear();
    }

    bool operator==(const ResultData &other) const {
        return speed == other.speed && speedList == other.speedList &&
               allignData == other.allignData &&
               trackedRoi == other.trackedRoi &&
               distanceFromCamera == other.distanceFromCamera &&
               intersectingLines == other.intersectingLines;
    }

    bool operator!=(const ResultData &other) const { return !(*this == other); }

    ResultData clone() const { return ResultData(*this); }

    ResultData &operator=(const ResultData &other) {
        speed = other.speed;
        allignData = other.allignData;
        trackedRoi = other.trackedRoi;
        speedList = other.speedList;
        distanceFromCamera = other.distanceFromCamera;
        intersectingLines = other.intersectingLines;
        return *this;
    }

    void initAllignData(int size) {
        if (size <= 0) {
            throw std::runtime_error("Size must be greater than 0");
        }

        allignData.resize(size);
    }
};

class SessionData {

    /////////////////////////////////////////////////////////
    /**
    *
    *
    * Common Data
    *
    *
    */
    /////////////////////////////////////////////////////////
  private:
    std::string id;
    Mode mode;
    PanelID currentPanelID;

  public:
    void setPanelID(PanelID id) { currentPanelID = id; }
    PanelID getPanelID() { return currentPanelID; }

    void setID(std::string id) { this->id = id; }
    std::string getID() { return id; }

    void setMode(Mode mode) { this->mode = mode; }
    Mode getMode() { return mode; }
    void toggleMode() { mode = mode == MODE_LANE ? MODE_DISTANCE : MODE_LANE; }

    /////////////////////////////////////////////////////////
    /**
    *
    *
    * Capture Data Vector
    *
    *
    */
    /////////////////////////////////////////////////////////
  private:
    CDVector captureData;

  public:
    void setCaptureData(CDVector &data) { captureData = data; }

    void removeCaptureData() { captureData.clear(); }

    CDVector getCaptureData() { return captureData; }

    bool isCaptureDataEmpty() { return captureData.empty(); }

    /////////////////////////////////////////////////////////
    /**
    *
    *
    * Calibration Data
    *
    *
    */
    /////////////////////////////////////////////////////////
  private:
    CalibrationData calibrationData;

  public:
    void setCalibrationData(CalibrationData &data) { calibrationData = data; }

    void removeCalibrationData() { calibrationData.clear(); }

    CalibrationData getCalibrationData() { return calibrationData; }

    bool isCalibrationDataEmpty() { return calibrationData.isNull(); }

    /////////////////////////////////////////////////////////
    /**
    *
    *
    * Tracking Data
    *
    *
    */
    /////////////////////////////////////////////////////////
  private:
    TrackingData trackingData;

  public:
    void clearTrackingData() { trackingData.clear(); }
    void setTrackingData(TrackingData &data) { trackingData = data; }
    TrackingData getTrackingData() { return trackingData; }
    bool isTrackingDataEmpty() { return !trackingData.isInit(); }

    /////////////////////////////////////////////////////////
    /**
    *
    *
    * Result Data
    *
    *
    */
    /////////////////////////////////////////////////////////
  private:
    ResultData resultData;

  public:
    void setResultData(ResultData &data) { resultData = data; }
    ResultData getResultData() { return resultData; }
    bool isResultDataEmpty() { return !resultData.isDefined(); }
    void clearResultData() { resultData.clear(); }

    void initAllignData(int size) { resultData.initAllignData(size); }

    /////////////////////////////////////////////////////////
    /**
    *
    *
    * Session Data
    *
    *
    */
    /////////////////////////////////////////////////////////

  public:
    SessionData() { Init(); }

    SessionData(const SessionData &other) {
        id = other.id;
        currentPanelID = other.currentPanelID;
        mode = other.mode;
        captureData = other.captureData;
        calibrationData = other.calibrationData;
        trackingData = other.trackingData;
        resultData = other.resultData;
    }

    SessionData clone() const { return SessionData(*this); }

    // Copy assignment operator (deep copy)
    SessionData &operator=(const SessionData &other) {
        if (this == &other) // Handle self-assignment
            return *this;

        id = other.id;
        currentPanelID = other.currentPanelID;
        mode = other.mode;
        captureData = other.captureData;
        calibrationData = other.calibrationData;
        trackingData = other.trackingData;
        resultData = other.resultData;
        return *this;
    }

    bool operator==(const SessionData &other) const {
        return (id == other.id && currentPanelID == other.currentPanelID &&
                mode == other.mode && captureData == other.captureData &&
                calibrationData == other.calibrationData &&
                trackingData == other.trackingData &&
                resultData == other.resultData);
    }

    bool operator!=(const SessionData &other) const {
        return !(*this == other);
    }

    bool isNull() {
        return (isCaptureDataEmpty() && isCalibrationDataEmpty() &&
                isTrackingDataEmpty());
    }

    void Init() {
        id = Utils::dateToString();
        currentPanelID = PANEL_CAPTURE;
        mode = MODE_LANE;
        captureData = CDVector();
        // allignData = ADVector();
        calibrationData = CalibrationData();
        trackingData = TrackingData();
        resultData = ResultData();
    }
};
