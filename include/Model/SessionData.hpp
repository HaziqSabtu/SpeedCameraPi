#pragma once

#include "Model/ModelEnum.hpp"
#include <Utils/DataStruct.hpp>
#include <Utils/ImageUtils.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

enum PanelID { PANEL_CAPTURE, PANEL_ROI };

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

    SessionData() { Init(); }

    void Init() {
        id = Utils::dateToString();
        currentPanelID = PANEL_CAPTURE;
        imageData = std::make_shared<std::vector<ImageData>>();
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
