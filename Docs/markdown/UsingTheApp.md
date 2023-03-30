# Using the App

## Setting up the Config file

During the first run of the app, a config file will be created in the root
directory, e.g. `/home/{user}/`. This file will be called `config.ini`. This
file contains all the settings for the app. You can edit this file to change the
settings.

Currently the variables can only be set in the config file. In the future, there
will be a GUI to change these settings.

### Configuration Variables

#### Camera Panel

| Variable           | Description                                            | Default |
| ------------------ | ------------------------------------------------------ | ------- |
| `Thread_Pool_Size` | Number of Thread pool to be used to process the images | `2`     |

#### Camera Parameter

| Variable        | Description                                                        | Default |
| --------------- | ------------------------------------------------------------------ | ------- |
| `Camera_ID`     | ID of the camera to be used                                        | `0`     |
| `Camera_Width`  | Width of the camera image <br> currently only `1280` are supported | `1280`  |
| `Camera_Height` | Height of the camera image <br> currently only `960` are supported | `960`   |
| `Camera_FPS`    | FPS of the camera image                                            | `10`    |

#### Sensor Parameter

Followings are the variables for the sensor. The default values are for the
Raspberry Pi Camera Module V2.

| Variable              | Description                                                     | Default |
| --------------------- | --------------------------------------------------------------- | ------- |
| `Sensor_Width`        | Width of the sensor image (mm)                                  | `3.68`  |
| `Sensor_Focal_Length` | Focal length of the sensor (mm)                                 | `3.04`  |
| `Object_Width`        | Width of the object in Real World (mm) <br> e.g. Road (3500 mm) | `360`   |

#### Capture Parameter

| Variable          | Description                                                                                                                 | Default |
| ----------------- | --------------------------------------------------------------------------------------------------------------------------- | ------- |
| `Max_Frame_Count` | Maximum number of frames to be captured                                                                                     | `10`    |
| `Debug`           | Debug mode <br> when set to `True` a bin file containing the images captured will be saved in the same directory as the app | `False` |

#### Load Parameter

| Variable            | Description                                                                         | Default   |
| ------------------- | ----------------------------------------------------------------------------------- | --------- |
| `Load_File_Name`    | Name of the file to be loaded <br> currently only .bin and .h264 file are supported | `default` |
| `Load_Dir_Location` | Directory location of the file to be loaded                                         | `default` |
| `Max_Frame`         | Maximum number of frames to be loaded                                               | `10`      |

#### Line Selection Parameter

| Variable | Description                                                                   | Default |
| -------- | ----------------------------------------------------------------------------- | ------- |
| `Radius` | Radius of the circle to be used to select the line <br> for debugging purpose | `10`    |

#### Canny_Parameter

Followings are the variables for the Canny Edge Detection. See
[OpenCV Canny](https://docs.opencv.org/4.x/dd/d1a/group__imgproc__feature.html#ga04723e007ed888ddf11d9ba04e2232de)
or [Example](https://docs.opencv.org/4.x/da/d22/tutorial_py_canny.html) for more
information.

| Variable       | Description                                                                                                         | Default |
| -------------- | ------------------------------------------------------------------------------------------------------------------- | ------- |
| `Threshold1`   | Lower threshold for the hysteresis procedure                                                                        | `50.0`  |
| `Threshold2`   | Upper threshold for the hysteresis procedure                                                                        | `150.0` |
| `ApertureSize` | Aperture size for the Sobel() operator                                                                              | `3`     |
| `L2Gradient`   | A flag, indicating whether a more accurate `L_2` norm <br> should be used to calculate the image gradient magnitude | `0`     |

#### Hough Parameter

Followings are the variables for the Hough Line Transform. See
[OpenCV Hough](https://docs.opencv.org/3.4/dd/d1a/group__imgproc__feature.html#ga8618180a5948286384e3b7ca02f6feeb)
or [Example](https://docs.opencv.org/3.4/d9/db0/tutorial_hough_lines.html) for
more information.

| Variable        | Description                                                                              | Default    |
| --------------- | ---------------------------------------------------------------------------------------- | ---------- |
| `Rho`           | Distance resolution of the accumulator in pixels                                         | `1`        |
| `Theta`         | Angle resolution of the accumulator in radians                                           | `pi / 180` |
| `Threshold`     | Accumulator threshold parameter <br> Lines with less than `Threshold` votes are rejected | `50`       |
| `MinLineLength` | Minimum line length. Line segments shorter than that are rejected                        | `25`       |
| `MaxLineGap`    | Maximum allowed gap between points on the same line to link them                         | `10`       |

#### Optical Flow Parameter

| Variable              | Description                                                                                                      | Default |
| --------------------- | ---------------------------------------------------------------------------------------------------------------- | ------- |
| `Max_Corners`         | Maximum number of corners to be detected                                                                         | `1000`  |
| `Quality_Level`       | Minimum quality level for corner detection                                                                       | `0.05`  |
| `Min_Distance`        | Minimum Euclidean distance between corners                                                                       | `7`     |
| `Block_Size`          | Size of the averaging block for corner detection                                                                 | `7`     |
| `Use_Harris_Detector` | Flag to use Harris detector                                                                                      | `False` |
| `K`                   | Free parameter of the Harris detector                                                                            | `0.04`  |
| `Min_Point_Distance`  | ?                                                                                                                | `0.2`   |
| `Threshold`           | Value to be used to filter out the points <br> adjust this values if the object detection results are inaccurate | `2.0`   |

## Using the App

    The application is currently in development. Proper error handling and
    documentation will be added in the future. The application is also expected to
    crash at random times. Will be fixed in the future.

The app is divided into 3 main parts.

| Part             | Description                                                                                         |
| ---------------- | --------------------------------------------------------------------------------------------------- |
| Capture Panel    | This part is used to capture the images from the camera                                             |
| Processing Panel | This part is used to process the images captured from the camera. Line Selection is also done here. |
| Result Panel     | This part is used to display the processed images.                                                  |

### Capture Panel

<!-- prettier-ignore-start -->
\image html button1.jpg "Camera Panel"
\image latex button1.jpg "Camera Panel"
<!-- prettier-ignore-end -->

| Button | Description                                                                                |
| ------ | ------------------------------------------------------------------------------------------ |
| 1      | Start capturing the images from the camera.                                                |
| 2      | Load the images from the file. <br> the filepath needs to be specified in the config file. |
| 3      | Toggle camera preview. <br> Note: will be removed in the future                            |

### Processing Panel

<!-- prettier-ignore-start -->
\image html button2.jpg "Processing Panel"
\image latex button2.jpg "Processing Panel"
<!-- prettier-ignore-end -->

| Button | Description                                                     |
| ------ | --------------------------------------------------------------- |
| 1      | Next image                                                      |
| 2      | Previous image                                                  |
| 3      | Toggle Canny Image to be displayed <br> for debugging purpose   |
| 4      | Toggle detected line to be displayed <br> for debugging purpose |
| 5      | Clear selected line                                             |
| 6      | Reset                                                           |

Detected Lines will be displayed in the Result Panel in red.

    Note: In some cases, the app will crash when the line is selected. This is due
    to some of the variables not being initialized properly. Will be fixed in the
    future. For now, just relaunch the app.

    Note: In some cases, the detected lines will not be displayed properly. Relaunch the app to fix this. Will be fixed in the future.

### Result Panel

<!-- prettier-ignore-start -->
\image html button3.jpg "Result Panel"
\image latex button3.jpg "Result Panel"
<!-- prettier-ignore-end -->

| Button | Description                                                                 |
| ------ | --------------------------------------------------------------------------- |
| 1      | Replay the result                                                           |
| 2      | Toggle Bounding Box to be displayed                                         |
| 3      | Toggle Line used for calculation to be displayed <br> for debugging purpose |
| 4      | Toggle Optical Flow to be displayed <br> for debugging purpose              |
| 5      | Toggle selected lines to be displayed <br> for debugging purpose            |
| 6      | Return to Process Panel to reselect line                                    |
| 7      | Reset                                                                       |
