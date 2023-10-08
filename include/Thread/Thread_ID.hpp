#pragma once

enum ThreadID {
    THREAD_NONE,
    THREAD_CAMERA_PREVIEW,
    THREAD_CAPTURE_PREVIEW,
    THREAD_LOAD_CAPTURE,
    THREAD_LOAD_FILE,
    THREAD_SAVE_FILE,
    THREAD_CALIBRATION_CAMERA,
    THREAD_CALIBRATION_CAPTURE,
    THREAD_MANUAL_CALIBRATION_CAMERA,
    THREAD_MANUAL_CALIBRATION_CAPTURE,
    THREAD_HORIZONTAL_CALIBRATION_CAMERA,
    THREAD_HORIZONTAL_CALIBRATION_CAPTURE,
    THREAD_CALIBRATION_PREVIEW_CAMERA,
    THREAD_CALIBRATION_PREVIEW_CAPTURE,
    THREAD_COLOR_CALIBRATION,
    THREAD_COLOR_CALIBRATION_PREVIEW,
    THREAD_ROI,
    THREAD_ROI_PREVIEW,
    THREAD_PROCESS,
    THREAD_PROCESS_REDUNDANT,
    THREAD_PROCESS_HORIZONTAL,
    THREAD_RESULT_PREVIEW,
    THREAD_TRIM_DATA,
};