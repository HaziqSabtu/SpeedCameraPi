#include <Model/SessionData.hpp>

void SessionData::setPanelID(PanelID id) { currentPanelID = id; }

PanelID SessionData::getPanelID() { return currentPanelID; }

void SessionData::setID(std::string id) { this->id = id; }

std::string SessionData::getID() { return id; }

void SessionData::setMode(Mode mode) { this->mode = mode; }

Mode SessionData::getMode() { return mode; }

void SessionData::toggleMode() {
    mode = mode == MODE_LANE ? MODE_DISTANCE : MODE_LANE;
}

void SessionData::setCaptureData(CDVector &data) { captureData = data; }

void SessionData::removeCaptureData() { captureData.clear(); }

CDVector SessionData::getCaptureData() { return captureData; }

bool SessionData::isCaptureDataEmpty() { return captureData.empty(); }

void SessionData::setCalibrationData(CalibrationData &data) {
    calibrationData = data;
}

void SessionData::removeCalibrationData() { calibrationData.clear(); }

CalibrationData SessionData::getCalibrationData() { return calibrationData; }

bool SessionData::isCalibrationDataEmpty() { return calibrationData.isNull(); }

void SessionData::clearTrackingData() { trackingData.clear(); }

void SessionData::setTrackingData(TrackingData &data) { trackingData = data; }

TrackingData SessionData::getTrackingData() { return trackingData; }

bool SessionData::isTrackingDataEmpty() { return !trackingData.isInit(); }

void SessionData::setResultData(ResultData &data) { resultData = data; }

ResultData SessionData::getResultData() { return resultData; }

bool SessionData::isResultDataEmpty() { return !resultData.isDefined(); }

void SessionData::clearResultData() { resultData.clear(); }

void SessionData::initAllignData(int size) { resultData.initAllignData(size); }

SessionData::SessionData() { Init(); }

SessionData::SessionData(const SessionData &other) {
    id = other.id;
    currentPanelID = other.currentPanelID;
    mode = other.mode;
    captureData = other.captureData;
    calibrationData = other.calibrationData;
    trackingData = other.trackingData;
    resultData = other.resultData;
}

SessionData SessionData::clone() const { return SessionData(*this); }

SessionData &SessionData::operator=(const SessionData &other) {
    if (this == &other)
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

bool SessionData::operator==(const SessionData &other) const {
    return (id == other.id && currentPanelID == other.currentPanelID &&
            mode == other.mode && captureData == other.captureData &&
            calibrationData == other.calibrationData &&
            trackingData == other.trackingData &&
            resultData == other.resultData);
}

bool SessionData::operator!=(const SessionData &other) const {
    return !(*this == other);
}

bool SessionData::isNull() {
    return (isCaptureDataEmpty() && isCalibrationDataEmpty() &&
            isTrackingDataEmpty());
}

void SessionData::Init() {
    id = Utils::dateToString();
    currentPanelID = PANEL_CAPTURE;
    mode = MODE_LANE;
    captureData = CDVector();
    calibrationData = CalibrationData();
    trackingData = TrackingData();
    resultData = ResultData();
}
