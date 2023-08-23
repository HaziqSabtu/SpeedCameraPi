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
    PANEL_COLOR_CALIBRATION,
    PANEL_RESULT,
    PANEL_SETTINGS,
    PANEL_INFO
};

struct TrackingData {
    cv::Rect roi;
    std::vector<cv::Rect> trackedRoi;

    TrackingData() {}

    TrackingData(cv::Rect roi, std::vector<cv::Rect> trackedRoi)
        : roi(roi), trackedRoi(trackedRoi) {}

    void clear() {
        roi = cv::Rect();
        trackedRoi.clear();
    }

    bool isInit() { return roi.area() > 0; }

    bool operator==(const TrackingData &other) const {
        return roi == other.roi && trackedRoi == other.trackedRoi;
    }

    bool operator!=(const TrackingData &other) const {
        return !(*this == other);
    }

    TrackingData clone() const { return TrackingData(*this); }

    TrackingData &operator=(const TrackingData &other) {
        roi = other.roi;
        trackedRoi = other.trackedRoi;
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
    double speed;
    std::vector<double> speedList;
    std::vector<double> distanceFromCamera;
    std::vector<Line> intersectingLines;

    ResultData() {}

    ResultData(double speed, std::vector<double> speedList,
               std::vector<double> distanceFromCamera,
               std::vector<Line> intersectingLines)
        : speed(speed), speedList(speedList),
          distanceFromCamera(distanceFromCamera),
          intersectingLines(intersectingLines) {}

    bool isDefined() {
        if (speed == -1) {
            return false;
        }

        if (speedList.empty() || distanceFromCamera.empty() ||
            intersectingLines.empty()) {
            return false;
        }

        if (speedList.size() + 1 != distanceFromCamera.size() ||
            speedList.size() + 1 != intersectingLines.size()) {
            return false;
        }

        return true;
    }

    void clear() {
        speed = -1;
        speedList.clear();
        distanceFromCamera.clear();
        intersectingLines.clear();
    }

    bool operator==(const ResultData &other) const {
        return speed == other.speed && speedList == other.speedList &&
               distanceFromCamera == other.distanceFromCamera &&
               intersectingLines == other.intersectingLines;
    }

    bool operator!=(const ResultData &other) const { return !(*this == other); }

    ResultData clone() const { return ResultData(*this); }

    ResultData &operator=(const ResultData &other) {
        speed = other.speed;
        speedList = other.speedList;
        distanceFromCamera = other.distanceFromCamera;
        intersectingLines = other.intersectingLines;
        return *this;
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

  private:
    PanelID currentPanelID;

  public:
    void setPanelID(PanelID id) { currentPanelID = id; }
    PanelID getPanelID() { return currentPanelID; }

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
    * Allign Data Vector
    *
    *
    */
    /////////////////////////////////////////////////////////
  private:
    ADVector allignData;

  public:
    void setAllignData(ADVector &data) { allignData = data; }

    void setAllignDataAt(int index, AllignData &data) {
        if (isAllignDataEmpty()) {
            throw std::runtime_error("Allign Data is empty");
        }

        if (index < 0 || index >= captureData.size()) {
            throw std::runtime_error("Index out of range");
        }

        allignData[index] = data;
    }

    void removeAllignData() { allignData.clear(); }

    ADVector getAllignData() { return allignData; }

    bool isAllignDataEmpty() { return allignData.empty(); }

    void initAllignData() {
        if (isCaptureDataEmpty()) {
            throw std::runtime_error("Capture Data is empty");
        }

        if (isAllignDataEmpty()) {
            allignData.resize(captureData.size());
        }
    }

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
        captureData = other.captureData;
        allignData = other.allignData;
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
        captureData = other.captureData;
        allignData = other.allignData;
        calibrationData = other.calibrationData;
        trackingData = other.trackingData;
        resultData = other.resultData;
        return *this;
    }

    bool operator==(const SessionData &other) const {
        return (id == other.id && currentPanelID == other.currentPanelID &&
                captureData == other.captureData &&
                allignData == other.allignData &&
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
        captureData = CDVector();
        allignData = ADVector();
        calibrationData = CalibrationData();
        trackingData = TrackingData();
        resultData = ResultData();
    }
};
