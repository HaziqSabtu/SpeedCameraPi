#pragma once

#include "UI/Control/ButtonControl/ButtonControl.hpp"
#include "UI/Control/SpinControl/SpinControl.hpp"
#include "UI/Data/Theme.hpp"
#include "UI/StaticText/DefaultStaticText.hpp"
#include <UI/Data/Data.hpp>

#define STD StaticTextData
#define STDV StaticTextDataVector

#define SCD SpinControlData
#define SCDI SpinControlData<int>
#define SCDD SpinControlData<double>

#define wxStringPair std::pair<wxString, wxString>

namespace Data {
namespace Settings {
namespace Panel {
namespace Camera {
const STD Title = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Camera",
    .fontData = T::TitleFontData,
};

const STDV Description = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The camera settings.",
        .fontData = T::descriptionFontData,
    },
};

const STD IDTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Camera ID",
    .fontData = T::TitleChildFontData,
};

const STDV IDDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The ID of the camera to use.",
        .fontData = T::descriptionFontData,
    },
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Disabled for now.",
        .fontData = T::descriptionFontData,
    },
};

const SCDI IDCtrlData = {
    .minValue = 0,
    .maxValue = 0,
    .increment = 1,
    .isDisabled = true,
};

const STD WidthTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Camera Width",
    .fontData = T::TitleChildFontData,
};

const STDV WidthDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The width of the camera resolution.",
        .fontData = T::descriptionFontData,
    },
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Disabled for now.",
        .fontData = T::descriptionFontData,
    },
};

const SCDI WidthCtrlData = {
    .minValue = 0,
    .maxValue = 1920,
    .increment = 1,
    .isDisabled = true,
};

const STD HeightTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Camera Height",
    .fontData = T::TitleChildFontData,
};

const STDV HeightDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The height of the camera resolution.",
        .fontData = T::descriptionFontData,
    },
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Disabled for now.",
        .fontData = T::descriptionFontData,
    },
};

const SCDI HeightCtrlData = {
    .minValue = 0,
    .maxValue = 1080,
    .increment = 1,
    .isDisabled = true,
};

const STD FPSTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Camera FPS",
    .fontData = T::TitleChildFontData,
};

const STDV FPSDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The FPS of the camera.",
        .fontData = T::descriptionFontData,
    },
};

const SCDI FPSCtrlData = {
    .minValue = 0,
    .maxValue = 60,
    .increment = 1,
    .isDisabled = false,
};

} // namespace Camera

namespace Sensor {
const STD Title = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Sensor",
    .fontData = T::TitleFontData,
};

const STDV Description = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The camera sensor settings.",
        .fontData = T::descriptionFontData,
    },
};

const STD WidthTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Sensor Width",
    .fontData = T::TitleChildFontData,
};

const STDV WidthDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The width of the camera sensor. (in mm)",
        .fontData = T::descriptionFontData,
    },
};

const SCDD WidthCtrlData = {
    .minValue = 0,
    .maxValue = 10,
    .increment = 0.01,
};

const STD FocalLengthTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Sensor Focal Length",
    .fontData = T::TitleChildFontData,
};

const STDV FocalLengthDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The focal length of the camera sensor. (in mm)",
        .fontData = T::descriptionFontData,
    },
};

const SCDD FocalLengthCtrlData = {
    .minValue = 0,
    .maxValue = 10,
    .increment = 0.01,
};
} // namespace Sensor

namespace Capture {
const STD Title = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Capture",
    .fontData = T::TitleFontData,
};

const STDV Description = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The capture settings.",
        .fontData = T::descriptionFontData,
    },
};

const STD MaxFrameTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Max Frame",
    .fontData = T::TitleChildFontData,
};

const STDV MaxFrameDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The maximum number of frames to capture.",
        .fontData = T::descriptionFontData,
    },
};

const SCDI MaxFrameCtrlData = {
    .minValue = 0,
    .maxValue = 100,
    .increment = 1,
};

const STD DebugShowImageTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Debug - Show Image",
    .fontData = T::TitleChildFontData,
};

const STDV DebugShowImageDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "if Enable, show the image when capturing.",
        .fontData = T::descriptionFontData,
    },
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "It is recommended to disable this for now.",
        .fontData = T::descriptionFontData,
    },
};

const STD DebugSaveTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Debug - Save Data",
    .fontData = T::TitleChildFontData,
};

const STDV DebugSaveDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "if Enable, data will automatically saved after capturing.",
        .fontData = T::descriptionFontData,
    },
};

}; // namespace Capture

namespace Model {
const STD Title = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Model",
    .fontData = T::TitleFontData,
};

const STDV Description = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The model settings.",
        .fontData = T::descriptionFontData,
    },
};

const STD MaxPoolTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Maximum Thread Pool",
    .fontData = T::TitleChildFontData,
};

const STDV MaxPoolDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The maximum number of threads to use for the thread pool.",
        .fontData = T::descriptionFontData,
    },
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Require restart to take effect.",
        .fontData = T::descriptionFontData,
    },
};

const SCDI MaxPoolCtrlData = {
    .minValue = 0,
    .maxValue = 5,
    .increment = 1,
};
}; // namespace Model

namespace Measurement {
const STD Title = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Measurement",
    .fontData = T::TitleFontData,
};

const STDV Description = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The measurement settings.",
        .fontData = T::descriptionFontData,
    },
};

const STD ObjectWidthTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Object Width",
    .fontData = T::TitleChildFontData,
};

const STDV ObjectWidthDD = {
    {.textColor = T::Text,
     .backgroundColor = T::Background,
     .text =
         "The width of the object to measure. (in mm) (for Lane Measurement)",
     .fontData = T::descriptionFontData},
};

const SCDI ObjectWidthCtrlData = {
    .minValue = 0,
    .maxValue = 10000,
    .increment = 1,

};

const STD ObjectHeightTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Object Height",
    .fontData = T::TitleChildFontData,
};

const STDV ObjectHeightDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The height of the object to measure. (in mm) (for Distance "
                "Measurement)",
        .fontData = T::descriptionFontData,
    },
};

const SCDI ObjectHeightCtrlData = {
    .minValue = 0,
    .maxValue = 10000,
    .increment = 1,
};
} // namespace Measurement

namespace Preview {
const STD Title = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Preview",
    .fontData = T::TitleFontData,
};

const STDV Description = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The preview settings.",
        .fontData = T::descriptionFontData,
    },
};

const STD WidthTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Preview Width",
    .fontData = T::TitleChildFontData,
};

const STDV WidthDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The width of the preview window.",
        .fontData = T::descriptionFontData,
    },
};

const SCDI WidthCtrlData = {
    .minValue = 0,
    .maxValue = 1920,
    .increment = 1,
};

const STD HeightTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Preview Height",
    .fontData = T::TitleChildFontData,
};

const STDV HeightDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The height of the preview window.",
        .fontData = T::descriptionFontData,
    },
};

const SCDI HeightCtrlData = {
    .minValue = 0,
    .maxValue = 1080,
    .increment = 1,

};
} // namespace Preview

namespace OpticalFlow {
const STD Title = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Optical Flow",
    .fontData = T::TitleFontData,
};

const STDV Description = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The optical flow settings.",
        .fontData = T::descriptionFontData,
    },
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "For more information, refer OpenCV documentation.",
        .fontData = T::descriptionFontData,
    },
};

const STD MaxCornersTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Max Corners",
    .fontData = T::TitleChildFontData,
};

const STDV MaxCornersDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The maximum number of corners to detect.",
        .fontData = T::descriptionFontData,
    },
};

const SCDI MaxCornersCtrlData = {
    .minValue = 0,
    .maxValue = 1000,
    .increment = 1,
};

const STD QualityLevelTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Quality Level",
    .fontData = T::TitleChildFontData,
};

const STDV QualityLevelDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The minimum accepted quality of image corners.",
        .fontData = T::descriptionFontData,
    },
};

const SCDD QualityLevelCtrlData = {
    .minValue = 0,
    .maxValue = 1,
    .increment = 0.01,
};

const STD MinDistanceTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Minimum Distance",
    .fontData = T::TitleChildFontData,
};

const STDV MinDistanceDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The minimum possible Euclidean distance between the returned "
                "corners.",
        .fontData = T::descriptionFontData,
    },
};

const SCDD MinDistanceCtrlData = {
    .minValue = 0,
    .maxValue = 1000,
    .increment = 1,
};

const STD BlockSizeTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Block Size",
    .fontData = T::TitleChildFontData,
};

const STDV BlockSizeDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Size of an average block for computing a derivative",
        .fontData = T::descriptionFontData,
    },
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "covariation matrix over each pixel neighborhood.",
        .fontData = T::descriptionFontData,
    },
};

const SCDI BlockSizeCtrlData = {
    .minValue = 0,
    .maxValue = 1000,
    .increment = 1,
};

const STD UseHarrisDetectorTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Use Harris Detector",
    .fontData = T::TitleChildFontData,
};

const STDV UseHarrisDetectorDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Use Harris Detector instead of Shi-Tomasi.",
        .fontData = T::descriptionFontData,
    },
};

const STD KTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "K",
    .fontData = T::TitleChildFontData,
};

const STDV KDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Free parameter of the Harris detector.",
        .fontData = T::descriptionFontData,
    },
};

const SCDD KCtrlData = {
    .minValue = 0,
    .maxValue = 1,
    .increment = 0.01,
};

const STD MinPointDistanceTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Minimum Point Distance",
    .fontData = T::TitleChildFontData,
};

const STDV MinPointDistanceDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The minimum distance between two points.",
        .fontData = T::descriptionFontData,
    },
};

const SCDD MinPointDistanceCtrlData = {
    .minValue = 0,
    .maxValue = 10,
    .increment = 0.1,
};

const STD ThresholdTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Threshold",
    .fontData = T::TitleChildFontData,
};

const STDV ThresholdDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text =
            "The threshold for the minimal point distance to be considered as "
            "moving.",
        .fontData = T::descriptionFontData,
    },
};

const SCDD ThresholdCtrlData = {
    .minValue = 0,
    .maxValue = 100,
    .increment = 0.1,
};

} // namespace OpticalFlow

namespace Ransac {
const STD Title = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "RANSAC",
    .fontData = T::TitleFontData,
};

const STDV Description = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The RANSAC settings.",
        .fontData = T::descriptionFontData,
    },
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Used in Line Search.",
        .fontData = T::descriptionFontData,
    },
};

const STD ThresholdTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Threshold",
    .fontData = T::TitleChildFontData,
};

const STDV ThresholdDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Minimum distance to be considered as inlier.",
        .fontData = T::descriptionFontData,
    },
};

const SCDD ThresholdCtrlData = {
    .minValue = 0,
    .maxValue = 100,
    .increment = 1,
};

const STD MinPointsTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Minimum Points",
    .fontData = T::TitleChildFontData,
};

const STDV MinPointsDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Minimum number of data points to allow line search.",
        .fontData = T::descriptionFontData,
    },
};

const SCDI MinPointsCtrlData = {
    .minValue = 0,
    .maxValue = 100,
    .increment = 1,
};

const STD MaxIterationsTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Maximum Iterations",
    .fontData = T::TitleChildFontData,
};

const STDV MaxIterationsDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Maximum number of iterations in model fitting.",
        .fontData = T::descriptionFontData,
    },
};

const SCDI MaxIterationsCtrlData = {
    .minValue = 0,
    .maxValue = 1000,
    .increment = 1,
};

} // namespace Ransac

namespace HSV {
const STD BlueTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Blue HSV",
    .fontData = T::TitleFontData,
};

const STDV BlueDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The blue HSV settings.",
        .fontData = T::descriptionFontData,
    },
};

const STD YellowTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Yellow HSV",
    .fontData = T::TitleFontData,
};

const STDV YellowDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "The yellow HSV settings.",
        .fontData = T::descriptionFontData,
    },
};

const STD HueTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Hue",
    .fontData = T::TitleChildFontData,
};

const STDV HueDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Hue Range. (0-180)",
        .fontData = T::descriptionFontData,
    },
};

const SCDI HueCtrlData = {
    .minValue = 0,
    .maxValue = 180,
    .increment = 1,
};

const wxStringPair HueLabels = {
    "Upper Hue",
    "Lower Hue",
};

const STD SaturationTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Saturation",
    .fontData = T::TitleChildFontData,
};

const STDV SaturationDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Saturation Range. (0-255)",
        .fontData = T::descriptionFontData,
    },
};

const SCDI SaturationCtrlData = {
    .minValue = 0,
    .maxValue = 255,
    .increment = 1,
};

const wxStringPair SaturationLabels = {
    "Upper Saturation",
    "Lower Saturation",
};

const STD ValueTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Value",
    .fontData = T::TitleChildFontData,
};

const STDV ValueDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Value Range. (0-255)",
        .fontData = T::descriptionFontData,
    },
};

const SCDI ValueCtrlData = {
    .minValue = 0,
    .maxValue = 255,
    .increment = 1,
};

const wxStringPair ValueLabels = {
    "Upper Value",
    "Lower Value",
};

} // namespace HSV

namespace Threads {
const STD Title = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Threads",
    .fontData = T::TitleFontData,
};

const STDV Description = {
    {.textColor = T::Text,
     .backgroundColor = T::Background,
     .text = "The thread settings.",
     .fontData = T::descriptionFontData},
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Enable / Disable automatic thread initialization",
        .fontData = T::descriptionFontData,
    },
};

const STD AutoManualCalibrationTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Auto Manual Calibration",
    .fontData = T::TitleChildFontData,
};

const STDV AutoManualCalibrationDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Enable / Disable automatic manual calibration.",
        .fontData = T::descriptionFontData,
    },
};

const STD AutoCalibrationTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Auto Calibration",
    .fontData = T::TitleChildFontData,
};

const STDV AutoCalibrationDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Enable / Disable automatic calibration.",
        .fontData = T::descriptionFontData,
    },
};

const STD AutoRoiTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Auto ROI",
    .fontData = T::TitleChildFontData,
};

const STDV AutoRoiDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Enable / Disable automatic ROI.",
        .fontData = T::descriptionFontData,
    },
};

const STD AutoResultTD = {
    .textColor = T::Text,
    .backgroundColor = T::Background,
    .text = "Auto Result",
    .fontData = T::TitleChildFontData,
};

const STDV AutoResultDD = {
    {
        .textColor = T::Text,
        .backgroundColor = T::Background,
        .text = "Enable / Disable automatic result processing.",
        .fontData = T::descriptionFontData,
    },
};

} // namespace Threads
} // namespace Panel
} // namespace Settings
}; // namespace Data