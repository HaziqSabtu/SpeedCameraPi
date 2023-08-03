#pragma once

#include "Model/CalibrationData.hpp"
#include "Utils/Config/AppConfig.hpp"
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
    PANEL_COLOR_CALIBRATION
};

struct RoiData {
    int x;
    int y;
    int width;
    int height;

    RoiData() {
        x = 0;
        y = 0;
        width = 0;
        height = 0;
    }

    bool isRoiEmpty() {
        return (x == 0 && y == 0 && width == 0 && height == 0);
    }

    void clearRoi() {
        x = 0;
        y = 0;
        width = 0;
        height = 0;
    }

    void Info() {
        std::cout << "RoiData Info:" << std::endl;
        std::cout << "x: " << x << std::endl;
        std::cout << "y: " << y << std::endl;
        std::cout << "width: " << width << std::endl;
        std::cout << "height: " << height << std::endl;
    }
};

struct SessionData {

    std::string id;

    PanelID currentPanelID;

    std::shared_ptr<std::vector<ImageData>> imageData;

    /////////////////////////////////////////////////////////
    /**
    *
    *
    * Calibration Data
    *
    *
    */
    /////////////////////////////////////////////////////////

    CalibData calibData;

    void setCalibData(CalibData &data) { calibData = data; }

    void removeCalibData() { calibData.clear(); }

    CalibData getCalibData() { return calibData; }

    /////////////////////////////////////////////////////////
    /**
    *
    *
    * Session Data
    *
    *
    */
    /////////////////////////////////////////////////////////

    SessionData() { Init(); }

    SessionData(const SessionData &other) {
        id = other.id;
        currentPanelID = other.currentPanelID;
        imageData = other.imageData;
        calibData = other.calibData;
        roiData = other.roiData;
    }

    SessionData clone() const { return SessionData(*this); }

    // Copy assignment operator (deep copy)
    SessionData &operator=(const SessionData &other) {
        if (this == &other) // Handle self-assignment
            return *this;

        id = other.id;
        currentPanelID = other.currentPanelID;
        imageData = other.imageData;
        calibData = other.calibData;
        roiData = other.roiData;

        return *this;
    }

    bool isNull() {
        return (imageData->empty() && calibData.isNull() &&
                roiData.isRoiEmpty());
    }

    void Init() {
        id = Utils::dateToString();
        currentPanelID = PANEL_CAPTURE;
        imageData = std::make_shared<std::vector<ImageData>>();
        calibData = CalibData();
        roiData = RoiData();
    }

    void clearImageData() {
        if (imageData == nullptr) {
            imageData = std::make_shared<std::vector<ImageData>>();
            return;
        }

        imageData->clear();
    }

    bool isImageDataEmpty() {
        if (imageData == nullptr) {
            return true;
        }

        return imageData->empty();
    }

    RoiData roiData;

    void clearRoiData() { roiData.clearRoi(); }

    void updateRoiData(int x, int y, int width, int height) {

        if (currentPanelID != PANEL_ROI) {
            throw std::runtime_error("currentPanelID is not PANEL_ROI");
        }

        roiData.x = x;
        roiData.y = y;
        roiData.width = width;
        roiData.height = height;
    }

    void setPanelID(PanelID id) { currentPanelID = id; }
};
