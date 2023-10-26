#pragma once

#include <Model/AllignData.hpp>
#include <Model/CalibrationData.hpp>
#include <Model/CaptureData.hpp>
#include <Model/Enum.hpp>
#include <Model/ResultData.hpp>
#include <Model/TrackingData.hpp>
#include <Utils/CommonUtils.hpp>
#include <Utils/Config/AppConfig.hpp>

#define DataPtr std::shared_ptr<SessionData>

/**
 * @brief Data containing all the data for a session
 *
 */
class SessionData {

  private:
    // Unique ID of the Session (Not utilized yet)
    std::string id;

    // Mode of the Session (Lane or Distance)
    Mode mode;

    // PanelID that is currently active
    PanelID currentPanelID;

  public:
    void setPanelID(PanelID id);
    PanelID getPanelID();
    void setID(std::string id);
    std::string getID();
    void setMode(Mode mode);
    Mode getMode();
    void toggleMode();

  private:
    CDVector captureData;

  public:
    void setCaptureData(CDVector &data);
    void removeCaptureData();
    CDVector getCaptureData();
    bool isCaptureDataEmpty();

  private:
    CalibrationData calibrationData;

  public:
    void setCalibrationData(CalibrationData &data);
    void removeCalibrationData();
    CalibrationData getCalibrationData();
    bool isCalibrationDataEmpty();

  private:
    TrackingData trackingData;

  public:
    void clearTrackingData();
    void setTrackingData(TrackingData &data);
    TrackingData getTrackingData();
    bool isTrackingDataEmpty();

  private:
    ResultData resultData;

  public:
    void setResultData(ResultData &data);
    ResultData getResultData();
    bool isResultDataEmpty();
    void clearResultData();
    void initAllignData(int size);

  public:
    SessionData();
    SessionData(const SessionData &other);
    SessionData clone() const;
    SessionData &operator=(const SessionData &other);
    bool operator==(const SessionData &other) const;
    bool operator!=(const SessionData &other) const;
    bool isNull();
    void Init();
};
