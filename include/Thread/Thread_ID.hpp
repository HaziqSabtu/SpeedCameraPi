#pragma once

enum ThreadID {
    THREAD_NONE,
    THREAD_CAPTURE,
    THREAD_REPLAY,
    THREAD_LOAD_CAPTURE,
    THREAD_LOAD_FILE,
    THREAD_CALIBRATION,
    THREAD_MANUAL_CALIBRATION,
    THREAD_CALIBRATION_PREVIEW,
    THREAD_COLOR_CALIBRATION,
    THREAD_COLOR_CALIBRATION_PREVIEW,
    THREAD_ROI,
    THREAD_PROCESS,
    THREAD_RESULT_PREVIEW,
};