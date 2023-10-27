#pragma once

/**
 * @brief Enum for Defined View Panel
 * @details
 * <table>
 * <tr>
 *  <th>Enum</th>
 *  <th>Panel</th>
 * </tr>
 * <tr>
 *   <td>PANEL_NONE</td>
 *   <td>None</td>
 * </tr>
 * <tr>
 *   <td>PANEL_CAPTURE</td>
 *   <td>CapturePanel</td>
 * </tr>
 * <tr>
 *   <td>PANEL_ROI</td>
 *   <td>RoiPanel</td>
 * </tr>
 * <tr>
 *   <td>PANEL_LANE_CALIBRATION</td>
 *   <td>LaneCalibrationPanel</td>
 * </tr>
 * <tr>
 *   <td>PANEL_LANE_MANUAL_CALIBRATION</td>
 *   <td>LaneManualCalibrationPanel</td>
 * </tr>
 * <tr>
 *   <td>PANEL_DISTANCE_CALIBRATION</td>
 *   <td>DistanceCalibrationPanel</td>
 * </tr>
 * <tr>
 *   <td>PANEL_COLOR_CALIBRATION</td>
 *   <td>ColorCalibrationPanel</td>
 * </tr>
 * <tr>
 *   <td>PANEL_TRIM_DATA</td>
 *   <td>TrimDataPanel</td>
 * </tr>
 * <tr>
 *   <td>PANEL_RESULT</td>
 *   <td>ResultPanel</td>
 * </tr>
 * <tr>
 *   <td>PANEL_SETTINGS</td>
 *   <td>SettingsPanel</td>
 * </tr>
 * <tr>
 *   <td>PANEL_INFO</td>
 *   <td>InfoPanel</td>
 * </tr>
 * </table>
 *
 */

enum PanelID {
    PANEL_NONE,
    PANEL_CAPTURE,
    PANEL_ROI,
    PANEL_LANE_CALIBRATION,
    PANEL_LANE_MANUAL_CALIBRATION,
    PANEL_DISTANCE_CALIBRATION,
    PANEL_COLOR_CALIBRATION,
    PANEL_TRIM_DATA,
    PANEL_RESULT,
    PANEL_SETTINGS,
    PANEL_INFO
};

/**
 * @brief Enum for Measurement / Calibration Mode
 * @details
 * <table>
 * <tr>
 *  <th>Enum</th>
 *  <th>Panel</th>
 * </tr>
 * <tr>
 *   <td>MODE_LANE</td>
 *   <td>Lane Calibration Mode</td>
 * </tr>
 * <tr>
 *   <td>MODE_DISTANCE</td>
 *   <td>Distance Calibration Mode</td>
 * </tr>
 * </table>
 *
 */
enum Mode { MODE_LANE, MODE_DISTANCE };

/**
 * @brief Enum for Button State
 * @details
 * <table>
 * <tr>
 *  <th>Enum</th>
 *  <th>State</th>
 * </tr>
 * <tr>
 *   <td>NORMAL</td>
 *   <td>Normal State</td>
 * </tr>
 * <tr>
 *   <td>ACTIVE</td>
 *   <td>Active State</td>
 * </tr>
 * <tr>
 *   <td>DISABLED</td>
 *   <td>Disabled State</td>
 * </tr>
 * <tr>
 *   <td>ON</td>
 *   <td>On State</td>
 * </tr>
 * <tr>
 *   <td>OFF</td>
 *  <td>Off State</td>
 * </tr>
 * <tr>
 *   <td>HIDDEN</td>
 *   <td>Hidden State</td>
 * </tr>
 * </table>
 *
 */
enum ButtonState { NORMAL, ACTIVE, DISABLED, ON, OFF, HIDDEN };

/**
 * @brief Enum for Panel State. Used within TextOutlinePanel
 * @details
 * <table>
 * <tr>
 *  <th>Enum</th>
 *  <th>State</th>
 * </tr>
 * <tr>
 *   <td>PANEL_NOT_OK</td>
 *   <td>Panel Not OK State</td>
 * </tr>
 * <tr>
 *   <td>PANEL_OK</td>
 *   <td>Panel OK State</td>
 * </tr>
 * <tr>
 *   <td>PANEL_HIDDEN</td>
 *   <td>Panel Hidden State</td>
 * </tr>
 *
 */
enum PanelState { PANEL_NOT_OK, PANEL_OK, PANEL_HIDDEN };