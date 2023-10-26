#include <Model/SessionData.hpp>

/**
 * @brief Sets the PanelID of the session data.
 * @param id The PanelID to set.
 */
void SessionData::setPanelID(PanelID id) { currentPanelID = id; }

/**
 * @brief Gets the current PanelID of the session data.
 * @return The current PanelID.
 */
PanelID SessionData::getPanelID() { return currentPanelID; }

/**
 * @brief Sets the ID of the session data.
 * @param id The ID to set.
 */
void SessionData::setID(std::string id) { this->id = id; }

/**
 * @brief Gets the ID of the session data.
 * @return The ID.
 */
std::string SessionData::getID() { return id; }

/**
 * @brief Sets the mode of the session data.
 * @param mode The Mode to set.
 */
void SessionData::setMode(Mode mode) { this->mode = mode; }

/**
 * @brief Gets the current mode of the session data.
 * @return The current Mode.
 */
Mode SessionData::getMode() { return mode; }

/**
 * @brief Toggles the mode between MODE_LANE and MODE_DISTANCE.
 */
void SessionData::toggleMode() {
    mode = mode == MODE_LANE ? MODE_DISTANCE : MODE_LANE;
}

/**
 * @brief Sets the capture data.
 * @param data The capture data to set.
 */
void SessionData::setCaptureData(CDVector &data) { captureData = data; }

/**
 * @brief Removes the capture data.
 */
void SessionData::removeCaptureData() { captureData.clear(); }

/**
 * @brief Gets the capture data.
 * @return The capture data.
 */
CDVector SessionData::getCaptureData() { return captureData; }

/**
 * @brief Checks if the capture data is empty.
 * @return True if capture data is empty, otherwise false.
 */
bool SessionData::isCaptureDataEmpty() { return captureData.empty(); }

/**
 * @brief Sets the calibration data.
 * @param data The calibration data to set.
 */
void SessionData::setCalibrationData(CalibrationData &data) {
    calibrationData = data;
}

/**
 * @brief Removes the calibration data.
 */
void SessionData::removeCalibrationData() { calibrationData.clear(); }

/**
 * @brief Gets the calibration data.
 * @return The calibration data.
 */
CalibrationData SessionData::getCalibrationData() { return calibrationData; }

/**
 * @brief Checks if the calibration data is empty.
 * @return True if calibration data is empty, otherwise false.
 */
bool SessionData::isCalibrationDataEmpty() { return calibrationData.isNull(); }

/**
 * @brief Clears the tracking data.
 */
void SessionData::clearTrackingData() { trackingData.clear(); }

/**
 * @brief Sets the tracking data.
 * @param data The tracking data to set.
 */
void SessionData::setTrackingData(TrackingData &data) { trackingData = data; }

/**
 * @brief Gets the tracking data.
 * @return The tracking data.
 */
TrackingData SessionData::getTrackingData() { return trackingData; }

/**
 * @brief Checks if the tracking data is empty.
 * @return True if tracking data is empty, otherwise false.
 */
bool SessionData::isTrackingDataEmpty() { return !trackingData.isInit(); }

/**
 * @brief Sets the result data.
 * @param data The result data to set.
 */
void SessionData::setResultData(ResultData &data) { resultData = data; }

/**
 * @brief Gets the result data.
 * @return The result data.
 */
ResultData SessionData::getResultData() { return resultData; }

/**
 * @brief Checks if the result data is empty.
 * @return True if result data is empty, otherwise false.
 */
bool SessionData::isResultDataEmpty() { return !resultData.isDefined(); }

/**
 * @brief Clears the result data.
 */
void SessionData::clearResultData() { resultData.clear(); }

/**
 * @brief Initializes alignment data with a specified size.
 * @param size The size to initialize.
 */
void SessionData::initAllignData(int size) { resultData.initAllignData(size); }

/**
 * @brief Initializes a new session data.
 */
SessionData::SessionData() { Init(); }

/**
 * @brief Copy constructor for SessionData.
 * @param other The other SessionData to copy.
 */
SessionData::SessionData(const SessionData &other) {
    id = other.id;
    currentPanelID = other.currentPanelID;
    mode = other.mode;
    captureData = other.captureData;
    calibrationData = other.calibrationData;
    trackingData = other.trackingData;
    resultData = other.resultData;
}

/**
 * @brief Clones the current SessionData.
 * @return A copy of the current SessionData.
 */
SessionData SessionData::clone() const { return SessionData(*this); }

/**
 * @brief Assignment operator for SessionData.
 * @param other The other SessionData to assign.
 * @return A reference to the modified SessionData.
 */
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

/**
 * @brief Checks if the current SessionData is equal to another SessionData.
 * @param other The other SessionData to compare.
 * @return True if the SessionData are equal, otherwise false.
 */
bool SessionData::operator==(const SessionData &other) const {
    return (id == other.id && currentPanelID == other.currentPanelID &&
            mode == other.mode && captureData == other.captureData &&
            calibrationData == other.calibrationData &&
            trackingData == other.trackingData &&
            resultData == other.resultData);
}

/**
 * @brief Checks if the current SessionData is not equal to another SessionData.
 * @param other The other SessionData to compare.
 * @return True if the SessionData are not equal, otherwise false.
 */
bool SessionData::operator!=(const SessionData &other) const {
    return !(*this == other);
}

/**
 * @brief Checks if the SessionData is null (empty).
 * @return True if all data is empty, otherwise false.
 */
bool SessionData::isNull() {
    return (isCaptureDataEmpty() && isCalibrationDataEmpty() &&
            isTrackingDataEmpty());
}

/**
 * @brief Initializes the SessionData with default values.
 */
void SessionData::Init() {
    id = Utils::dateToString();
    currentPanelID = PANEL_CAPTURE;
    mode = MODE_LANE;
    captureData = CDVector();
    calibrationData = CalibrationData();
    trackingData = TrackingData();
    resultData = ResultData();
}
