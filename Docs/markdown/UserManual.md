\tableofcontents{HTML:1}

# Hardware Overview

<!-- prettier-ignore-start -->
\image html 111.png ""
\image latex 111.png ""
<!-- prettier-ignore-end -->

| Number | Function      |
| ------ | ------------- |
| 1      | Touch Screen  |
| 2      | Top Cover     |
| 3      | Main Body     |
| 4      | LAN Port      |
| 5      | Camera        |
| 6      | Battery Cover |
| 7      | Handle        |
| 8      | Switch        |


# Quick Start

This chapter describes how to use the device. Figure below shows the overall process of using the device.

<!-- prettier-ignore-start -->
\image html overall.png ""
\image latex overall.png ""
<!-- prettier-ignore-end -->

## Power On

1. Press the power button to turn on the device.
2. The device will boot up and the main interface will be displayed.

## Capture Image

1. Make sure that you are on the Capture Panel.
2. Press the Capture button to capture an image.
3. The captured images will be displayed on the screen.

## Calibrate

1. From the Capture Panel, press the Calibrate button to go to the Calibration Panel.
2. Once you are on the Calibration Panel, press the Start button to start the calibration process.
3. Depends on the calibration mode, the calibration process will be different.
4. Once the calibration process is done, press Accept to accept the calibration result.

## Select ROI

1. From the Capture Panel, press the ROI button to go to the ROI Selection Panel.
2. On the ROI Panel, press the Start button to start the ROI selection process.
3. Within the touchscreen, draw a rectangle to select the region where the object is located.
4. Once the ROI selection process is done, press Accept to accept the ROI selection result.

## Measure

1. From the Capture Panel, press the Measure button to go to the Measurement Panel.
2. On the Measurement Panel, press the Start button to start the measurement process.
3. The measurement result will be displayed on the screen.
This Markdown content mirrors the structure and content of the provided LaTeX 

# Panel Overview

This chapter provides information on the available panels and their functions.

Following are the available panels:

-   Capture Panel
-   Automatic Lane Calibration Panel
-   Manual Lane Calibration Panel
-   Distance Calibration Panel
-   ROI Panel
-   Result Panel
-   Color Calibration Panel
-   Trim Data Panel
-   Settings Panel

<p>&nbsp;</p>
<p>&nbsp;</p>

## Main Layout {#Main-Layout}

<!-- prettier-ignore-start -->
\image html p9.png ""
\image latex p9.png "Main Layout"
<!-- prettier-ignore-end -->

| Number | Name               | Function                                          |
| ------ | ------------------ | ------------------------------------------------- |
| 1      | Title              | Show current panel                                |
| 2      | Image Panel        | Show Image                                        |
| 3      | Status Panel       | Display status of application                     |
| 4      | Button Panel       | Contains all buttons for processes and navigation |
| 5      | Switch Mode Button | Switch between DISTANCE and LANE mode             |
| 6      | Info Button        | Show Info                                         |
| 7      | Settings Button    | Switch to Settings. Panel. Refer to @subpage Settings-Panel                          |
| 8      | Exit Button        | Exit the Application                              |

### Notes
- The Switch Mode Button (**5**) is only available on the @subpage Capture-Panel. It is used to switch between **DISTANCE** and **LANE** mode. The default mode is **LANE** mode.

<p>&nbsp;</p>
<p>&nbsp;</p>

## Capture Panel {#Capture-Panel}

The Capture Panel is the main panel of the program. It is where you can capture the screen, edit the image, and save it to a file.

<!-- prettier-ignore-start -->
\image html p1.png "Buttons of the Capture Panel"
\image latex p1.png "Buttons of the Capture Panel"
<!-- prettier-ignore-end -->

| Number | Function                         |
| ------ | -------------------------------- |
| 1      | Capture Image                    |
| 2      | Load Saved data                  |
| 3      | Toggle Camera On / Off (Preview) |
| 4      | Replay Captured Data             |
| 5      | Clear/Remove Captured Data       |
| 6      | Change to Calibration Panel      |
| 7      | Remove Calibration Data          |
| 8      | Change To Roi Panel              |
| 9      | Remove Roi Data                  |
| 10     | Save Captured  Data              |
| 11     | Trim Captured Data               |
| 12     | Reset Session (Remove All Data)  |
| 13     | Change To Result Panel           |

### Instructions

#### Capture Image
To capture image press the Capture button (**1**). The image will be captured and displayed in the panel. The image will also be saved in the program's memory.

#### Load Saved Data
To load saved data press the Load button (**2**). A file dialog will appear. Select the file you want to load. The file will be loaded and displayed in the panel. The file will also be saved in the program's memory.

#### Toggle Camera On / Off (Preview)
To toggle the camera on or off press the Camera button (**3**). The camera will be turned on or off. If the camera is on, the image will be displayed in the panel.

#### Replay Captured Data
To replay the captured data press the Replay button (**4**). Make sure that the data is loaded. The data will be replayed in the panel.

#### Clear/Remove Captured Data
To clear/remove the captured data press the Clear button (**5**). The data will be cleared/removed from the program's memory.

#### Change to Calibration Panel
To change to the Calibration Panel press the Calibration button (**6**). The Calibration Panel will be displayed. Refer @subpage Automatic-Lane-Calibration-Panel or @subpage Distance-Calibration-Panel for more information.

#### Remove Calibration Data
To remove the calibration data press the Remove Calibration button (**7**). The calibration data will be removed from the program's memory. If ROI data is present, it will also be removed.

#### Change To Roi Panel
To change to the Roi Panel press the Roi button (**8**). The Roi Panel will be displayed. Refer @subpage Roi-Panel for more information.

#### Remove Roi Data
To remove the Roi data press the Remove Roi button (**9**). The Roi data will be removed from the program's memory.

#### Save Captured  Data
To save the captured data press the Save button (**10**). A file dialog will appear. If you press accept, the data will be saved to the file you selected.

#### Trim Captured Data
To trim the captured data press the Trim button (**11**). A dialog will appear. The TrimDataPanel will be displayed. Refer @subpage Trim-Data-Panel for more information.

#### Reset Session (Remove All Data)
To reset the session press the Reset button (**12**). All the data will be removed from the program's memory.

#### Change To Result Panel
To change to the Result Panel press the Result button (**13**). The Result Panel will be displayed. Refer @subpage Result-Panel for more information.

<p>&nbsp;</p>
<p>&nbsp;</p>

## Automatic Lane Calibration Panel {#Automatic-Lane-Calibration-Panel}

The Calibration Panel is where you can perform automatic lane calibration. This calibration type is done with the custom mat.

<!-- prettier-ignore-start -->
\image html p2.png "Buttons of the Calibration Panel"
\image latex p2.png "Buttons of the Calibration Panel"
<!-- prettier-ignore-end -->

| Number | Function                                |
| ------ | --------------------------------------- |
| 1      | Start Automatic Lane Calibration        |
| 2      | Change To Manual Lane Calibration Panel |
| 3      | Stop Calibration                        |
| 4      | Select Point                            |
| 5      | Cancel / Remove Calibration             |
| 6      | Start Preview / Show Calibrated Data    |
| 7      | Remove Calibrated Data                  |
| 8      | Change To Color Calibration Panel       |
| 9      | Cancel Calibration                      |
| 10     | Accept Calibration                      |

### Instructions

#### Performing Calibration

To perform automatic lane calibration, press the Start Calibration button (**1**). The program will start the calibration process. The program will display the image in the panel. Begin with selecting point by pressing the Select Point button (**4**). After clicking the point, select on the Image Panel, the position where the mat is located. The program will automatically detect line and display it in the panel. If the line is not detected, try to select another point. If the line is detected, press the Accept Calibration button (**10**). The program will save the calibration data in the program's memory. 


#### Start Preview / Show Calibrated Data

To start preview or show calibrated data press the Preview button (**6**). The program will display the image in the panel. If the calibration data is present, the program will display the calibrated data in the panel.

#### Change To Manual Lane Calibration Panel

To change to the Manual Lane Calibration Panel press the Manual Calibration button (**2**). The Manual Lane Calibration Panel will be displayed. Refer @subpage Manual-Lane-Calibration-Panel for more information.

#### Change To Color Calibration Panel

To change to the Color Calibration Panel press the Color Calibration button (**8**). The Color Calibration Panel will be displayed. Refer @subpage Color-Calibration-Panel for more information.

### Notes
- Please make sure that you adjust the object size in the Settings Panel. Go to settings panel by pressing the Settings button. Locate the **Object Width** variable and adjust it to the width of the mat (420 mm).
- To perform this calibration type, make sure the application is in **LANE MEASUREMENT MODE** by pressing the **Toggle Mode** button. Refer to @subpage Main-Layout for more information.

<p>&nbsp;</p>
<p>&nbsp;</p>

## Manual Lane Calibration Panel {#Manual-Lane-Calibration-Panel}

The Manual Lane Calibration Panel is where you can perform manual lane calibration. 

<!-- prettier-ignore-start -->
\image html p3.png "Buttons of the Manual Lane Calibration Panel"
\image latex p3.png "Buttons of the Manual Lane Calibration Panel"
<!-- prettier-ignore-end -->

| Number | Function                             |
| ------ | ------------------------------------ |
| 1      | Start Manual Lane Calibration        |
| 2      | Stop Calibration                     |
| 3      | Select Left Line                     |
| 4      | Remove Selected Left Line            |
| 5      | Select Right Line                    |
| 6      | Remove Selected Right Line           |
| 7      | Start Preview / Show Calibrated Data |
| 8      | Remove Calibrated Data               |
| 9      | Cancel Calibration                   |
| 10     | Accept Calibration                   |

### Instructions

#### Performing Calibration

To perform manual lane calibration, press the Start Calibration button (**1**). The program will start the calibration process. The program will display the image in the panel. Begin with selecting the left line by pressing the Select Left Line button (**3**). Line selection is done via point and drag method. Place the finger on the Image Panel where the lane is located and drag the finger to the end of the lane. The program will display the line in the panel. If the line seems inaccurate, try to select another point. Repeat the process for the right line by pressing the Select Right Line button (**5**). After selecting both lines, press the Accept Calibration button (**10**). The program will save the calibration data in the program's memory.

#### Start Preview / Show Calibrated Data

To start preview or show calibrated data press the Preview button (**7**). The program will display the image in the panel. If the calibration data is present, the program will display the calibrated data in the panel.

### Notes

- Please make sure that you adjust the object size in the Settings Panel. Go to settings panel by pressing the Settings button. Locate the **Object Width** variable and adjust it to the width of the mat (420 mm) or width of road (3500 mm).

- To perform this calibration type, make sure the application is in **LANE MEASUREMENT MODE** by pressing the **Toggle Mode** button. Refer to @subpage Main-Layout for more information.

<p>&nbsp;</p>
<p>&nbsp;</p>

## Distance Calibration Panel {#Distance-Calibration-Panel}

The Distance Calibration Panel is where you can perform distance calibration. This calibration is done with an object of known height.

<!-- prettier-ignore-start -->
\image html p4.png "Buttons of the Distance Calibration Panel"
\image latex p4.png "Buttons of the Distance Calibration Panel"
<!-- prettier-ignore-end -->

| Number | Function                             |
| ------ | ------------------------------------ |
| 1      | Start Distance Calibration           |
| 2      | Stop Calibration                     |
| 3      | Select Top Line                      |
| 4      | Remove Selected Top Line             |
| 5      | Select Bottom Line                   |
| 6      | Remove Selected Bottom Line          |
| 7      | Start Preview / Show Calibrated Data |
| 8      | Remove Calibrated Data               |
| 9      | Cancel Calibration                   |
| 10     | Accept Calibration                   |

### Instructions

#### Performing Calibration

To perform distance calibration, press the Start Calibration button (**1**). The program will start the calibration process. The program will display the image in the panel. Begin with selecting the top line by pressing the Select Top Line button (**3**). Line selection is done via point and drag method. Place the finger on the Image Panel where the starting point of the object is located. Adjust the position by dragging the finger. Repeat the process for the bottom line by pressing the Select Bottom Line button (**5**). After selecting both lines, press the Accept Calibration button (**10**). The program will save the calibration data in the program's memory.

#### Start Preview / Show Calibrated Data

To start preview or show calibrated data press the Preview button (**7**). The program will display the image in the panel. If the calibration data is present, the program will display the calibrated data in the panel.

### Notes

- Please make sure that you adjust the object size in the Settings Panel. Go to settings panel by pressing the Settings button. Locate the **Object Height** variable and adjust it to the height of the object.
- To perform this calibration type, make sure the application is in **DISTANCE MEASUREMENT MODE** by pressing the **Toggle Mode** button. Refer to @subpage Main-Layout for more information.

<p>&nbsp;</p>
<p>&nbsp;</p>

## Roi Panel {#Roi-Panel}

The Roi Panel is where you can perform region of interest (ROI) selection. 

<!-- prettier-ignore-start -->
\image html p8.png "Buttons of the Roi Panel"
\image latex p8.png "Buttons of the Roi Panel"
<!-- prettier-ignore-end -->

| Number | Function      |
| ------ | ------------- |
| 1      | Start Roi     |
| 2      | Stop Roi      |
| 3      | Start Preview |
| 4      | Remove Roi    |
| 5      | Cancel        |
| 6      | Accept        |

### Instructions

#### Performing ROI Selection

To perform ROI selection, press the Start Roi button (**1**). The program will start the ROI selection process. The program will display the image in the panel. Begin with selecting the top left point by pressing the Select Top Left Point button (**3**). Point selection is done via point and drag method. Place the finger on the Image Panel where the starting point of the ROI is located. Drag the finger to the end of the ROI. Press the Accept button (**6**) to accept the ROI. The program will save the ROI data in the program's memory.

#### Start Preview

To start preview the ROI press the Preview button (**3**). The program will display the image in the panel. If the ROI data is present, the program will display the ROI in the panel.

## Result Panel {#Result-Panel}

The Result Panel is where you can perform data processing and view the result of the measurement.

<!-- prettier-ignore-start -->
\image html p5.png "Buttons of the Result Panel"
\image latex p5.png "Buttons of the Result Panel"
<!-- prettier-ignore-end -->

| Number | Function                                     |
| ------ | -------------------------------------------- |
| 1      | Start Process Data with Optical Flow Tracker |
| 2      | Rerun Process With CSRT Tracker              |
| 3      | Preview Processed Data                       |
| 4      | Change To Capture Panel                      |

### Instructions

#### Start Process Data with Optical Flow Tracker

The program is set to use the Optical Flow Tracker by default. To start processing the data, press the Process Data button (**1**). The program will start processing the data. The program will display the processed data in the panel.

#### Rerun Process With CSRT Tracker

In some cases, where the Optical Flow Tracker is not accurate, you can use the CSRT Tracker. To rerun the process with CSRT Tracker, press the Rerun Process button (**2**). The program will start processing the data with CSRT Tracker. The program will display the processed data in the panel.

#### Preview Processed Data

To preview the processed data press the Preview button (**3**). The program will display the processed data in the panel.

#### Change To Capture Panel

After processing the data, you can change to the Capture Panel by pressing the Back button (**4**). The Capture Panel will be displayed.

<p>&nbsp;</p>
<p>&nbsp;</p>

## Color Calibration Panel {#Color-Calibration-Panel}

The Color Calibration Panel is where you can perform color calibration. The purpose of this calibration is to detect the color of the mat, which is used within the @subpage Automatic-Lane-Calibration-Panel.

<!-- prettier-ignore-start -->
\image html p6.png "Buttons of the Color Calibration Panel"
\image latex p6.png "Buttons of the Color Calibration Panel"
<!-- prettier-ignore-end -->


| Number | Function                         |
| ------ | -------------------------------- |
| 1      | Start Color Calibration          |
| 2      | Preview Current Calibrated Color |
| 3      | Stop Calibration                 |
| 4      | Select Blue Color                |
| 5      | Remove Selected Blue Range       |
| 6      | Select Yellow Color              |
| 7      | Remove Selected Yellow Range     |
| 8      | Restore Default Range            |
| 9      | Cancel Calibration               |
| 10     | Accept Calibration               |

### Instructions

#### Performing Calibration

To perform color calibration, press the Start Calibration button (**1**). The program will start the calibration process. The program will display the image in the panel. Begin with selecting the blue color by pressing the Select Blue Color button (**4**). Color selection is done via point and drag method. Place the finger on the Image Panel where the blue color is located The program will display the blue color range in the panel. If the range seems inaccurate, try to select another point. Repeat the process for the yellow color by pressing the Select Yellow Color button (**6**). After selecting both colors, press the Accept Calibration button (**10**). The program will save the calibration data in the program's memory.

#### Preview Current Calibrated Color

To preview the current calibrated color press the Preview button (**2**). The program will display the image in the panel. If the calibration data is present, the program will display the calibrated data in the panel.

#### Restore Default Range

To restore the default range press the Restore Default Range button (**8**). The program will restore the default range.

<p>&nbsp;</p>
<p>&nbsp;</p>

## Trim Data Panel {#Trim-Data-Panel}

The Trim Data Panel is where you can trim the captured data. In cases where the captured data is too long, you can trim the data to a certain length.

<!-- prettier-ignore-start -->
\image html p7.png "Buttons of the Trim Data Panel"
\image latex p7.png "Buttons of the Trim Data Panel"
<!-- prettier-ignore-end -->

| Number | Function                 |
| ------ | ------------------------ |
| 1      | Start Trim Data          |
| 2      | Replay Current Data      |
| 3      | Stop Trim Data           |
| 4      | Replay Current Data      |
| 5      | Decrement Start Position |
| 6      | Increment Start Position |
| 7      | Decrement End Position   |
| 8      | Increment End Position   |
| 9      | Cancel                   |
| 10     | Accept                   |

### Instructions

#### Performing Trim

To perform trim, press the Start Trim button (**1**). The program will start the trim process. The program will display the image in the panel. Begin with selecting the start position by pressing the Decrement Start Position button (**5**) or Increment Start Position button (**6**). The program will display the current start position in the panel. Repeat the process for the end position by pressing the Decrement End Position button (**7**) or Increment End Position button (**8**). After selecting both positions, press the Accept button (**10**). The program will save the trimmed data in the program's memory.

#### Replay Current Data / Preview

To replay the current data or preview the trimmed data press the Replay button (**2**). The program will replay the data in the panel.

### Notes

- There is a limit to the minimum length of data (5 frames). Buttons will be disabled if the minimum length is reached.

- By performing the trim, the program will automatically remove the calibration data and ROI data. This is done to avoid any errors.

<p>&nbsp;</p>
<p>&nbsp;</p>

## Settings Panel {#Settings-Panel}

The Settings Panel is where you can adjust the settings of the application.

### Camera

#### Camera ID

The Camera ID is the ID of the camera that will be used by the application. The default value is 0. If you have multiple cameras, you can change the value to the ID of the camera you want to use.

(Changing the value of this variable is disabled. However, the value can be manipulated directly by accessing the config file or through source code.)

#### Camera Width

The Camera Width is the width of the camera. The default value is 1280. If you have a camera with a different width, you can change the value to the width of the camera.

(Changing the value of this variable is disabled. However, the value can be manipulated directly by accessing the config file or through source code.)

#### Camera Height

The Camera Height is the height of the camera. The default value is 960. If you have a camera with a different height, you can change the value to the height of the camera.

(Changing the value of this variable is disabled. However, the value can be manipulated directly by accessing the config file or through source code.)

#### Camera FPS

The Camera FPS is the FPS of the camera. The default value is 10. If you want to increase or decrease the FPS of the camera, you can change the value to the FPS of the camera.

### Sensor

#### Sensor Width

The Sensor Width is the width of the sensor. The default value is 3.68 mm. If you have a sensor with a different width, you can change the value to the width of the sensor.

(Variable is in mm).

#### Sensor Focal Length

The Sensor Focal Length is the focal length of the sensor. The default value is 3.04 mm. If you have a sensor with a different focal length, you can change the value to the focal length of the sensor.

(Variable is in mm).

### Capture

#### Max Frame

The number of frames that will be captured. The default value is 10. If you want to increase or decrease the number of frames, you can change the value to the number of frames.

#### Debug - Show Image

This variable is used to show image during capturing process. There seems to be a bug where when showing images during capturing will cause inaccuracy in timing of the capturing process. The default value is false. If you want to show the image during capturing process, you can change the value to true.

#### Debug - Save Data

This variable is used to save data during capturing process. The default value is false. If the variable is enabled, the data will always be automatically saved for each capturing process.

### Model

#### Maximum Thread Pool

The maximum number of threads that will be used by the application. The default value is 2. If you want to increase or decrease the number of threads, you can change the value to the number of threads.

#### Optical Flow

Refer to OpenCV documentation for more information.

##### Max Corners

The maximum number of corners that will be detected by the Optical Flow Tracker. The default value is 1000. If you want to increase or decrease the number of corners, you can change the value to the number of corners.

##### Quality Level

The quality level of the corners that will be detected by the Optical Flow Tracker. The default value is 0.05. If you want to increase or decrease the quality level, you can change the value to the quality level.

#### Minimum Distance

The minimum distance between corners that will be detected by the Optical Flow Tracker. The default value is 7. If you want to increase or decrease the minimum distance, you can change the value to the minimum distance.

#### Block Size

The block size of the corners that will be detected by the Optical Flow Tracker. The default value is 3. If you want to increase or decrease the block size, you can change the value to the block size.

#### Use Harris Detector

This variable is used to enable or disable the Harris Detector. The default value is false. If you want to enable the Harris Detector, you can change the value to true.

#### K

The K value of the Harris Detector. The default value is 0.04. If you want to increase or decrease the K value, you can change the value to the K value.

#### Minimum Point Distance

The minimum distance between points that will be detected by the Optical Flow Tracker. Any value below this value will be ignored. The default value is 0.2. If you want to increase or decrease the minimum distance, you can change the value to the minimum distance.

#### Threshold

The minimum distance between points that will be detected by the Optical Flow Tracker. Any value below this value will be ignored. The default value is 0.2. If you want to increase or decrease the minimum distance, you can change the value to the minimum distance.

### Measurement

#### Object Width

The width of the object that will be used for measurement. The default value is 3500 mm. If you have an object with a different width, you can change the value to the width of the object.

(This variable is used together with the **LANE MEASUREMENT MODE**. Refer to @subpage Main-Layout , @subpage Automatic-Lane-Calibration-Panel , and @subpage Manual-Lane-Calibration-Panel for more information.)

#### Object Height

The height of the object that will be used for measurement. The default value is 2000 mm. If you have an object with a different height, you can change the value to the height of the object.

(This variable is used together with the **DISTANCE MEASUREMENT MODE**. Refer to @subpage Main-Layout and @subpage Distance-Calibration-Panel for more information.)

### Preview

#### Preview Width

The width of the preview image. The default value is 640. If you want to increase or decrease the width of the preview image, you can change the value to the width of the preview image.

(This variable is used to display image within Image Panel. Lowering the value will increase the performance of the application.)

#### Preview Height

The height of the preview image. The default value is 480. If you want to increase or decrease the height of the preview image, you can change the value to the height of the preview image.

(This variable is used to display image within Image Panel. Lowering the value will increase the performance of the application.)

### RANSAC

#### Threshold

The minimum distance to consider a point as an inlier. The default value is 6.0. If you want to increase or decrease the threshold, you can change the value to the threshold.

#### Minimum Point

The minimum number of data within the datasets to enable line searching. Default value is 50. If you want to increase or decrease the minimum point, you can change the value to the minimum point.

#### Maximum Iteration

The maximum number of iteration to find the best line. Default value is 500. If you want to increase or decrease the maximum iteration, you can change the value to the maximum iteration.

### Blue HSV

#### Hue

The hue value of the blue color. The default value is 130 for Upper and 100 for Lower.

#### Saturation

The saturation value of the blue color. The default value is 255 for Upper and 100 for Lower.

#### Value

The value of the blue color. The default value is 255 for Upper and 100 for Lower.

### Yellow HSV

#### Hue

The hue value of the yellow color. The default value is 35 for Upper and 20 for Lower.

#### Saturation

The saturation value of the yellow color. The default value is 255 for Upper and 100 for Lower.

#### Value

The value of the yellow color. The default value is 255 for Upper and 100 for Lower.

### Threads
Variable to enable automatic process starting when switching panel.

#### Auto Calibration

This variable is used to enable or disable automatic calibration when switching to the Calibration Panel. The default value is false. If you want to enable automatic calibration, you can change the value to true.

(This variable is unused).

#### Auto Manual Calibration

When enabled, the program will automatically start manual calibration when switching to the Manual Lane Calibration Panel. The default value is false. If you want to enable automatic manual calibration, you can change the value to true.

#### Auto ROI

When enabled, the program will automatically start ROI selection when switching to the ROI Panel. The default value is false. If you want to enable automatic ROI selection, you can change the value to true.

#### Auto Result

When enabled, the program will automatically start processing data when switching to the Result Panel. The default value is false. If you want to enable automatic processing data, you can change the value to true.