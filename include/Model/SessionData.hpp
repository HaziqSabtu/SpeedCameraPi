#pragma once

#include "Model/CalibrationData.hpp"
#include "Utils/Config/AppConfig.hpp"
#include "Utils/Struct/D_Allign.hpp"
#include <Utils/DataStruct.hpp>
#include <Utils/ImageUtils.hpp>

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
};

struct RoiData {
    cv::Rect initRoi;
    std::vector<cv::Rect> trackedRoi;

    void clear() {
        initRoi = cv::Rect();
        trackedRoi.clear();
    }

    bool isInit() { return initRoi.area() > 0; }
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
};

#define ADVector std::vector<AllignData2>
struct AllignData2 {
    cv::Mat image;
    cv::Mat transformMatrix;

    AllignData2() {}

    AllignData2(cv::Mat image, cv::Mat transformMatrix)
        : transformMatrix(transformMatrix), image(image) {}
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

    void setAllignDataAt(int index, AllignData2 &data) {
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
    CalibData calibData;

  public:
    void setCalibData(CalibData &data) { calibData = data; }

    void removeCalibData() { calibData.clear(); }

    CalibData getCalibData() { return calibData; }

    bool isCalibDataEmpty() { return calibData.isNull(); }

    /////////////////////////////////////////////////////////
    /**
    *
    *
    * ROI Data
    *
    *
    */
    /////////////////////////////////////////////////////////
  private:
    RoiData roiData;

  public:
    void clearRoiData() { roiData.clear(); }
    void setRoiData(RoiData &data) { roiData = data; }
    RoiData getRoiData() { return roiData; }
    bool isRoiDataEmpty() { return !roiData.isInit(); }

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
        // imageData = other.imageData;
        calibData = other.calibData;
        // roiData = other.roiData;
    }

    SessionData clone() const { return SessionData(*this); }

    // Copy assignment operator (deep copy)
    SessionData &operator=(const SessionData &other) {
        if (this == &other) // Handle self-assignment
            return *this;

        id = other.id;
        currentPanelID = other.currentPanelID;
        // imageData = other.imageData;
        calibData = other.calibData;
        // roiData = other.roiData;

        return *this;
    }

    bool isNull() {
        return (
            isCaptureDataEmpty() && isCalibDataEmpty() && isRoiDataEmpty() // &&
                                                                           // &&
            // roiData.isRoiEmpty()
        );
    }

    void Init() {
        id = Utils::dateToString();
        currentPanelID = PANEL_CAPTURE;
        // imageData = std::make_shared<std::vector<ImageData>>();
        calibData = CalibData();
        roiData = RoiData();
    }
};
