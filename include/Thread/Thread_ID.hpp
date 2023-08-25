#pragma once

enum ThreadID {
    THREAD_NONE,
    THREAD_CAPTURE,
    THREAD_REPLAY,
    THREAD_LOAD_CAPTURE,
    THREAD_LOAD_FILE,
    THREAD_SAVE_FILE,
    THREAD_CALIBRATION,
    THREAD_CALIBRATION_CAPTURE,
    THREAD_MANUAL_CALIBRATION,
    THREAD_MANUAL_CALIBRATION_CAPTURE,
    THREAD_CALIBRATION_PREVIEW,
    THREAD_CALIBRATION_PREVIEW_CAPTURE,
    THREAD_COLOR_CALIBRATION,
    THREAD_COLOR_CALIBRATION_PREVIEW,
    THREAD_ROI,
    THREAD_ROI_PREVIEW,
    THREAD_PROCESS,
    THREAD_RESULT_PREVIEW,
    THREAD_TRIM_DATA,
};