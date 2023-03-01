#include <Algorithm/lane_detection/LaneDetectionAlgorithm.hpp>

LaneDetectionAlgorithm::LaneDetectionAlgorithm() {}

LaneDetectionAlgorithm::~LaneDetectionAlgorithm() {}

void LaneDetectionAlgorithm::process(
    cv::Mat &input, std::vector<std::vector<cv::Point2f>> &roiList) {
    preProcessImage(input);
    getAllLine();
    processDetectedLines(HoughLineOutput, false);
    processRawData(roiList, false, false);
    processROIData(roiList, false, false);
    filterDetLine(detectedLines, false);
    generateLineCombo(filteredLines, -1, false);
    evaluateLineCombo(lineCombinations, {});
    // generateBestImage(10);
}

// preProcessing Image for Feature Recognition
// 1. Convert to HLS
// 2. Apply Threshold
// 3. Convert to Gray
// 4. Apply Gaussian Blur
// 5. Apply Canny Edge Detection
void LaneDetectionAlgorithm::preProcessImage(cv::Mat &_frame) {
    frame = _frame.clone();
    cv::cvtColor(frame, hlsFrame, cv::COLOR_BGR2HLS);
    cv::inRange(hlsFrame, cv::Scalar(hLow, lLow, sLow),
                cv::Scalar(hHigh, lHigh, sHigh), hlsMask);
    cv::bitwise_and(frame, frame, hlsOutput, hlsMask);

    cv::cvtColor(hlsOutput, grayFrame, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(grayFrame, blurFrame,
                     cv::Size(blurKernelSize, blurKernelSize), blurSigmaX,
                     blurSigmaY);
    cv::Canny(blurFrame, cannyFrame, cannyThreshold1, cannyThreshold2,
              cannyApertureSize);
}

void LaneDetectionAlgorithm::getAllLine() {
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(cannyFrame, HoughLineOutput, 1, CV_PI / 180, houghThreshold,
                    houghMinLineLength, houghMaxLineGap);
}

void LaneDetectionAlgorithm::processDetectedLines(std::vector<cv::Vec4i> lines,
                                                  bool draw) {
    // process every line
    // get intersection from (0 -> frameHeight)
    // sort by x
    for (auto &l : lines) {
        DetLine d;

        cv::Point2f point1 =
            cv::Point2f(static_cast<float>(l[0]), static_cast<float>(l[1]));
        cv::Point2f point2 =
            cv::Point2f(static_cast<float>(l[2]), static_cast<float>(l[3]));

        if (isLineParallel(
                point1, point2, cv::Point2f(0, 0),
                cv::Point2f(static_cast<float>(frame.size().width), 0), 1)) {
            continue;
        }

        // end of line is intersection of line with top frame border
        d.end = getIntersectionPoint(
            point1, point2, cv::Point2f(0, 0),
            cv::Point2f(static_cast<float>(frame.size().width), 0));

        // start of line is intersection of line with bottom frame border
        d.start = getIntersectionPoint(
            point1, point2,
            cv::Point2f(0, static_cast<float>(frame.size().height)),
            cv::Point2f(static_cast<float>(frame.size().width),
                        static_cast<float>(frame.size().height)));

        d.angle = getAngle(d.end, d.start);
        // std::cout << "d.angle: " << d.angle << std::endl;
        detectedLines.push_back(d);
    }

    stable_sort(
        detectedLines.begin(), detectedLines.end(),
        [](const DetLine a, const DetLine b) { return a.start.x < b.start.x; });

    std::cout << "detectedLines.size(): " << detectedLines.size() << std::endl;

    if (draw) {
        for (auto &d : detectedLines) {
            line(hlsOutput, d.start, d.end, cv::Scalar(0, 255, 255), 1,
                 cv::LINE_AA);
            circle(hlsOutput, d.start, 5, cv::Scalar(0, 0, 255), 2);
        }
    }
}

void LaneDetectionAlgorithm::processRawData(
    std::vector<std::vector<cv::Point2f>> &rois, bool debug = false,
    bool draw = false) {
    // process RAW roi Data
    // get all angle for every ROI Point from Start to End
    // start is higher than end
    // sort by angle INC

    // todo SWAP END W START
    for (int i = 0; i < rois.front().size(); i++) {
        ROI r;
        r.pos = i;

        if (rois.front()[i].y > rois.back()[i].y) {
            r.start = rois.back()[i];
            r.end = rois.front()[i];
        } else {
            r.start = rois.front()[i];
            r.end = rois.back()[i];
        }
        r.angle = getAngle(r.start, r.end);
        roiDataList.push_back(r);
    }

    stable_sort(roiDataList.begin(), roiDataList.end(),
                [](ROI a, ROI b) { return a.angle < b.angle; });

    if (debug) {
        for (auto &r : roiDataList) {
            std::cout << "r.angle: " << r.angle << std::endl;
        }
    }

    if (draw) {
        for (auto &roi : rois) {
            std::cout << "roi.size(): " << roi.size() << std::endl;
            for (auto &r : roi) {
                std::cout << "r: " << r << std::endl;
                cv::circle(hlsOutput, r, 2, cv::Scalar(0, 255, 255), 2);
            }
        }
        for (auto &r : roiDataList) {
            cv::circle(hlsOutput, r.start, 5, cv::Scalar(0, 0, 255), 2);
            cv::circle(hlsOutput, r.end, 5, cv::Scalar(0, 255, 0), 2);
        }
    }
}

// process ROI Data
// choose 2 ROI with the largest angle difference
// get intersection point from 2 ROI
// get angle between 2 ROI
// get ALL POINTS of LEFT, RIGHT, MID from bottom to intersection point
void LaneDetectionAlgorithm::processROIData(
    std::vector<std::vector<cv::Point2f>> &rois, bool debug = false,
    bool draw = false) {

    int a = roiDataList.front().pos, b = roiDataList.back().pos;

    roiData.left = rois.front()[a];
    roiData.right = rois.front()[b];

    roiData.intersection = getIntersectionPoint(
        rois.front()[a], rois.back()[a], rois.front()[b], rois.back()[b]);

    roiData.angleBetween = getAngleBetweenVector(
        rois.front()[a], rois.back()[a], rois.front()[b], rois.back()[b]);

    // get intersection of left point with bottom frame border
    cv::Point2f intersectionLeft = getIntersectionPoint(
        rois.front()[a], rois.back()[a], cv::Point2i(0, frame.rows),
        cv::Point2i(frame.cols, frame.rows));

    // get intersection of right point with bottom frame border
    cv::Point2f intersectionRight = getIntersectionPoint(
        rois.front()[b], rois.back()[b], cv::Point2i(0, frame.rows),
        cv::Point2i(frame.cols, frame.rows));

    // get intersection of mid point with bottom frame border
    cv::Point2f intersectionMid = getIntersectionPoint(
        roiData.intersection,
        cv::Point2f(((roiData.left.x + roiData.right.x) / 2),
                    (roiData.left.y + roiData.right.y) / 2),
        cv::Point2f(0, (float)frame.rows),
        cv::Point2f((float)frame.cols, (float)frame.rows));

    // get All Points from BOTTOM -> INTERSECTION (w/ Y)
    roiData.pointsData.leftPoints =
        getAllPointY(intersectionLeft, roiData.intersection);
    roiData.pointsData.rightPoints =
        getAllPointY(intersectionRight, roiData.intersection);
    roiData.pointsData.midPoints =
        getAllPointY(intersectionMid, roiData.intersection);
    // sussy
    roiData.midAngle =
        getAngle(roiData.intersection,
                 cv::Point2i(roiData.pointsData.midPoints.front().x,
                             roiData.pointsData.midPoints.front().y));
    std::cout << "roiData.midAngle: " << roiData.midAngle << std::endl;

    if (debug) {
        std::cout << "roiData.left: " << roiData.left << std::endl;
        std::cout << "roiData.right: " << roiData.right << std::endl;
        std::cout << "roiData.intersection: " << roiData.intersection
                  << std::endl;
        std::cout << "roiData.angleBetween: " << roiData.angleBetween
                  << std::endl;
        std::cout << "intersectionLeft: " << intersectionLeft
                  << "  Size: " << roiData.pointsData.leftPoints.size()
                  << std::endl;
        std::cout << "intersectionRight: " << intersectionRight
                  << "  Size: " << roiData.pointsData.rightPoints.size()
                  << std::endl;
        std::cout << "intersectionMid: " << intersectionMid
                  << "  Size: " << roiData.pointsData.midPoints.size()
                  << std::endl;
        std::cout << "roiData.midAngle: " << roiData.midAngle << std::endl;
    }

    if (draw) {
        circle(hlsOutput, roiData.intersection, 3, cv::Scalar(255, 0, 0), 3);
        for (auto &p : roiData.pointsData.leftPoints) {
            circle(hlsOutput, p, 1, cv::Scalar(255, 0, 0), 1);
        }

        for (auto &p : roiData.pointsData.rightPoints) {
            circle(hlsOutput, p, 1, cv::Scalar(255, 0, 0), 1);
        }

        for (auto &p : roiData.pointsData.midPoints) {
            circle(hlsOutput, p, 1, cv::Scalar(255, 0, 0), 1);
        }
    }
}

// HONESTLY TOO MUCH SUSSYNESS
void LaneDetectionAlgorithm::filterDetLine(std::vector<DetLine> &detectedLines,
                                           bool draw = false) {
    const double angleLimit = 15;
    double smallAngleLimit = roiDataList.front().angle;
    double bigAngleLimit = roiDataList.back().angle;
    double range = abs(bigAngleLimit - smallAngleLimit);
    if (range < 10) {
        range = 10;
    }

    for (auto &d : detectedLines) {
        double a = d.angle;

        if (abs(a - bigAngleLimit) <= angleLimit ||
            abs(a - smallAngleLimit) <= angleLimit) {
            if ((a >= smallAngleLimit - 2 * range &&
                 a <= smallAngleLimit + 2 * range)) {
                filteredLines.push_back(d);
            }
        }
    }

    if (draw) {
        for (auto &d : filteredLines) {
            line(hlsOutput, d.start, d.end, cv::Scalar(0, 0, 255), 1,
                 cv::LINE_AA);
        }
    }
    std::cout << "filteredLines.size(): " << filteredLines.size() << std::endl;
}
/**
 * * Generate all possible line combinations from detected Lines
 * * Filter Out all combinations that are not parallel
 * * Generate all possible line combinations from detected Lines
 * * Filter Out all combinations that are not within the angle range
 * * Filter Out all combinations that are not within the distance range
 */
void LaneDetectionAlgorithm::generateLineCombo(std::vector<DetLine> &lines,
                                               int debug = -1,
                                               bool draw = false) {
    const int lineLimitSize = frame.size().height / 4;
    int count = 0;
    for (int i = 0; i < lines.size(); i++) {
        for (int j = i + 1; j < lines.size(); j++) {

            if (i == j) {
                continue;
            }

            LineCombination l;
            l.id = count;

            l.left = lines[i];
            l.right = lines[j];

            l.angleBetween = getAngleBetweenVector(
                l.left.start, l.intersection, l.right.start, l.intersection);

            if (isLineParallel(l.left.start, l.left.end, l.right.start,
                               l.right.end, 1)) {
                std::cout << "line is parallel -> skipping" << std::endl;
                continue;
            }
            l.intersection = getIntersectionPoint(l.left.start, l.left.end,
                                                  l.right.start, l.right.end);

            if (l.intersection == l.left.start &&
                l.intersection == l.right.start) {
                std::cout << "intersection is same as start point -> skipping"
                          << std::endl;
                continue;
            }

            if (l.intersection.y > l.left.start.y) {
                std::cout << "intersection is above start point -> skipping"
                          << std::endl;
                continue;
            }
            l.pointLeft = getAllPointY(l.left.start, l.intersection);

            if (l.intersection.y > l.right.start.y) {
                std::cout << "intersection is above start point -> skipping"
                          << std::endl;
                continue;
            }
            l.pointRight = getAllPointY(l.right.start, l.intersection);

            if (l.pointLeft.size() == 0 || l.pointRight.size() == 0) {
                continue;
            }
            l.midPoints = getAllPointY(
                cv::Point2f((l.left.start.x + l.right.start.x) / 2,
                            (l.left.start.y + l.right.start.y) / 2),
                l.intersection);

            if (l.midPoints.size() == 0) {
                continue;
            }
            if (l.pointLeft.size() < lineLimitSize ||
                l.pointRight.size() < lineLimitSize) {
                std::cout << "line size is too small -> skipping" << std::endl;
                continue;
            }

            l.midAngle = getAngle(l.intersection, l.midPoints.front());
            lineCombinations.push_back(l);
            count++;
        }
    }
    int target;
    if (debug != -1) {
        std::cout << "Generated: " << lineCombinations.size() << " lines"
                  << std::endl;

        if (debug > lineCombinations.size()) {
            srand((unsigned)time(0));
            std::cout
                << "Debug is larger than lineCombinations size -> randomizing"
                << std::endl;
            int random = rand() % lineCombinations.size();
            std::cout << "Random: " << random << std::endl;
            target = random;
        } else {
            std::cout << "Debug: " << debug << std::endl;
            target = debug;
        }

        LineCombination lineC = lineCombinations[target];
        std::cout << "id: " << lineC.id << std::endl;
        std::cout << "left: " << lineC.left.start << "  -->  " << lineC.left.end
                  << std::endl;
        std::cout << "right: " << lineC.right.start << "  -->  "
                  << lineC.right.end << std::endl;
        std::cout << "intersection: " << lineC.intersection << std::endl;
        std::cout << "angleBetween: " << lineC.angleBetween << std::endl;
        std::cout << "midAngle: " << lineC.midAngle << std::endl;

        cv::Mat debugIMG = hlsOutput.clone();
        std::string windowName = "Line Combo " + std::to_string(target);
        // cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
        circle(debugIMG, lineC.intersection, 3, cv::Scalar(255, 0, 0), 3);

        for (auto &p : lineC.pointLeft) {
            circle(debugIMG, p, 2, cv::Scalar(255, 0, 0), -1);
        }

        for (auto &p : lineC.pointRight) {
            circle(debugIMG, p, 2, cv::Scalar(255, 0, 0), -1);
        }

        // imshow(windowName, debugIMG);
    }

    if (draw) {

        for (auto &l : lineCombinations) {
            circle(hlsOutput, l.intersection, 3, cv::Scalar(255, 0, 0), 3);

            for (auto &p : l.pointLeft) {
                circle(hlsOutput, p, 1, cv::Scalar(255, 0, 0), 1);
            }

            for (auto &p : l.pointRight) {
                circle(hlsOutput, p, 1, cv::Scalar(255, 0, 0), 1);
            }
        }
    }
}

/**
 * * loop through every line combo
 * * and evaluate it
 * * sort the line combo by the lowest error
 */
void LaneDetectionAlgorithm::evaluateLineCombo(
    std::vector<LineCombination> lineCombos, std::vector<int> debug = {}) {

    for (LineCombination &l : lineCombinations) {
        EvaluationData e;
        e.lineCombination = l;
        e.error = runEvaluation(l, debug);
        evalData.push_back(e);
    }
    stable_sort(
        evalData.begin(), evalData.end(),
        [](EvaluationData a, EvaluationData b) { return a.error < b.error; });
}

// ! Deprecated
void LaneDetectionAlgorithm::generateBestImage(int count) {
    std::cout << "Generating best images" << std::endl;
    for (int i = imgGenCount; i < count; i++) {
        EvaluationData ed = evalData[i];
        cv::Mat img = hlsOutput.clone();
        std::string name = "ID: " + std::to_string(i) +
                           " ROI: " + std::to_string(ed.lineCombination.id) +
                           " error: " + std::to_string(ed.error);
        cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
        LineCombination lc = ed.lineCombination;
        for (auto &p : lc.pointLeft) {
            circle(img, p, 2, cv::Scalar(255, 0, 255), -1);
        }
        for (auto &p : lc.pointRight) {
            circle(img, p, 2, cv::Scalar(255, 0, 0), -1);
        }
        imshow(name, img);
        std::cout << "ID: " << ed.lineCombination.id
                  << "   Error : " << ed.error << std::endl;
    }
}

std::vector<cv::Mat> LaneDetectionAlgorithm::generateBestImageV(int count) {
    std::cout << "Generating best images from " << imgGenCount << " to "
              << imgGenCount + 10 << std::endl;
    std::vector<cv::Mat> images;
    for (int i = imgGenCount; i < count + imgGenCount; i++) {
        EvaluationData ed = evalData[i];
        cv::Mat img = hlsOutput.clone();
        std::string name = "ID: " + std::to_string(i) +
                           " ROI: " + std::to_string(ed.lineCombination.id) +
                           " error: " + std::to_string(ed.error);
        // cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
        LineCombination lc = ed.lineCombination;
        for (auto &p : lc.pointLeft) {
            circle(img, p, 2, cv::Scalar(255, 0, 255), -1);
        }
        for (auto &p : lc.pointRight) {
            circle(img, p, 2, cv::Scalar(255, 0, 0), -1);
        }
        // imshow(name, img);
        images.push_back(img);
        std::cout << "ID: " << ed.lineCombination.id
                  << "   Error : " << ed.error << std::endl;
    }
    return images;
}

cv::Mat LaneDetectionAlgorithm::generateComplexImage(int count,
                                                     int hLimit = 4) {
    std::vector<cv::Mat> imageArray = generateBestImageV(count);
    cv::Mat complexImage;
    std::vector<cv::Mat> tempHImgArray;
    std::vector<cv::Mat> tempConcat;

    int vLimit = (int)((imageArray.size() / (double)hLimit) + 0.5);
    for (int i = 1; i <= vLimit * hLimit; i++) {
        if (i <= imageArray.size()) {
            cv::Mat img = imageArray[i - 1];
            cv::putText(img, std::to_string(i - 1), cv::Point(50, 50),
                        cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 0, 255), 3,
                        cv::LINE_AA);
            tempHImgArray.push_back(img);
        }

        else {
            tempHImgArray.push_back(cv::Mat::zeros(
                imageArray[0].rows, imageArray[0].cols, CV_8UC3));
        }

        if (i % hLimit == 0 && i != 0) {
            cv::Mat temp;
            cv::hconcat(tempHImgArray, temp);
            tempConcat.push_back(temp);
            tempHImgArray.clear();
        }
    }
    cv::vconcat(tempConcat, complexImage);
    tempConcat.clear();

    double resizeFactorH, resizeFactorV;

    resizeFactorH = 1920.0 / complexImage.cols;
    cv::resize(complexImage, complexImage, cv::Size(), resizeFactorH,
               resizeFactorH);

    if (complexImage.rows > 1080) {
        resizeFactorV = 1080.0 / complexImage.rows;
        cv::resize(complexImage, complexImage, cv::Size(), resizeFactorV,
                   resizeFactorV);
    }

    return complexImage;
}

// Todo: reusable code
void LaneDetectionAlgorithm::generateEvalDataLeft(int choice) {
    if (evalDataLeft.size() > 0) {
        evalDataLeft.clear();
    }
    int selectedEval = choice + imgGenCount;
    EvaluationData ed = evalData[selectedEval];

    LineCombination lc = ed.lineCombination;

    const int TOLERANCE_PIXEL = 30;

    for (auto &eData : evalData) {
        if ((fabs(eData.lineCombination.pointLeft.front().x -
                  lc.pointLeft.front().x) < TOLERANCE_PIXEL) &&
            (fabs(eData.lineCombination.pointLeft.back().x -
                  lc.pointLeft.back().x) < TOLERANCE_PIXEL)) {
            evalDataLeft.push_back(eData);
        }
    }
}

// Todo: reusable code
cv::Mat LaneDetectionAlgorithm::generateComplexImageLeft(int count,
                                                         int hLimit = 4) {
    std::vector<cv::Mat> imageArray = generateBestImageLeft(count);
    cv::Mat complexImage;
    std::vector<cv::Mat> tempHImgArray;
    std::vector<cv::Mat> tempConcat;

    int vLimit = (int)((imageArray.size() / (double)hLimit) + 0.5);
    for (int i = 1; i <= vLimit * hLimit; i++) {
        if (i <= imageArray.size()) {
            cv::Mat img = imageArray[i - 1];
            cv::putText(img, std::to_string(i - 1), cv::Point(50, 50),
                        cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 0, 255), 3,
                        cv::LINE_AA);
            tempHImgArray.push_back(img);
        }

        else {
            tempHImgArray.push_back(cv::Mat::zeros(
                imageArray[0].rows, imageArray[0].cols, CV_8UC3));
        }

        if (i % hLimit == 0 && i != 0) {
            cv::Mat temp;
            cv::hconcat(tempHImgArray, temp);
            tempConcat.push_back(temp);
            tempHImgArray.clear();
        }
    }
    cv::vconcat(tempConcat, complexImage);
    tempConcat.clear();

    double resizeFactorH, resizeFactorV;

    resizeFactorH = 1920.0 / complexImage.cols;
    cv::resize(complexImage, complexImage, cv::Size(), resizeFactorH,
               resizeFactorH);

    if (complexImage.rows > 1080) {
        resizeFactorV = 1080.0 / complexImage.rows;
        cv::resize(complexImage, complexImage, cv::Size(), resizeFactorV,
                   resizeFactorV);
    }

    return complexImage;
}

// Todo: reusable code
std::vector<cv::Mat> LaneDetectionAlgorithm::generateBestImageLeft(int count) {
    std::vector<cv::Mat> images;
    for (int i = imgGenCountLeft; i < count + imgGenCountLeft; i++) {
        EvaluationData ed = evalDataLeft[i];
        cv::Mat img = hlsOutput.clone();
        LineCombination lc = ed.lineCombination;
        cv::line(img, lc.pointLeft.front(), lc.pointLeft.back(),
                 cv::Scalar(255, 0, 255), 2);
        cv::line(img, lc.pointRight.front(), lc.pointRight.back(),
                 cv::Scalar(255, 0, 0), 2);
        images.push_back(img);
    }
    return images;
}

// SETTERS
void LaneDetectionAlgorithm::setImgGenCount(int count) { imgGenCount = count; }

void LaneDetectionAlgorithm::setSelectedEvalData(int v) {
    selectedEvalData = v;
}

// GETTERS
int LaneDetectionAlgorithm::getImgGenCount() { return imgGenCount; }

EvaluationData LaneDetectionAlgorithm::getEvalData() {
    return evalData[selectedEvalData];
}

// STATIC METHODS

// check if lines are parallel to each other
bool LaneDetectionAlgorithm::isLineParallel(cv::Point2f p1, cv::Point2f p2,
                                            cv::Point2f p3, cv::Point2f p4,
                                            double limit = 1) {
    double angle1 = getAngle(p1, p2);
    double angle2 = getAngle(p3, p4);

    if (abs(angle1 - angle2) < limit) {
        return true;
    }
    return false;
}

// get Angle of vector from X axis counterclockwise
double LaneDetectionAlgorithm::getAngle(cv::Point2f p1, cv::Point2f p2) {

    cv::Vec2f v1 = cv::Vec2f(p2.x - p1.x, p2.y - p1.y);
    cv::Vec2f v2 = cv::Vec2f(100, 0);
    double cross = v1[0] * v2[1] - v1[1] * v2[0];
    double dot = v1[0] * v2[0] + v1[1] * v2[1];
    double angle = atan2(cross, dot);
    if (angle < 0) {
        angle += 2 * CV_PI;
    }
    double a = angle * 180 / CV_PI;
    return a;
}

// get intersection point of two lines
cv::Point2f LaneDetectionAlgorithm::getIntersectionPoint(cv::Point2f p1,
                                                         cv::Point2f p2,
                                                         cv::Point2f p3,
                                                         cv::Point2f p4) {
    float x, y;

    float x1 = p1.x;
    float y1 = p1.y;

    float x2 = p2.x;
    float y2 = p2.y;

    float x3 = p3.x;
    float y3 = p3.y;

    float x4 = p4.x;
    float y4 = p4.y;

    x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) /
        ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));

    y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) /
        ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));

    return cv::Point2f(x, y);
}

// get angle between two vectors
double LaneDetectionAlgorithm::getAngleBetweenVector(cv::Point2f p1,
                                                     cv::Point2f p2,
                                                     cv::Point2f p3,
                                                     cv::Point2f p4) {
    double angle1 = atan2(p2.y - p1.y, p2.x - p1.x);
    double angle2 = atan2(p4.y - p3.y, p4.x - p3.x);
    double angle = angle1 - angle2;
    return angle * 180 / CV_PI;
}

// get all point from line
std::vector<cv::Point2f>
LaneDetectionAlgorithm::getAllPointX(cv::Point2f &startPoint,
                                     cv::Point2f &intersection) {

    std::vector<cv::Point2f> points;

    // compute gradient
    // y = mx + c
    float m = static_cast<float>(intersection.y - startPoint.y) /
              static_cast<float>(intersection.x - startPoint.x);
    float c = startPoint.y - m * startPoint.x;
    int start, end;
    if (startPoint.x < intersection.x) {
        start = startPoint.x;
        end = intersection.x;
    } else {
        start = intersection.x;
        end = startPoint.x;
    }

    for (int x = start; x < end; x++) {
        float y = m * x + c;
        points.push_back(cv::Point2f(x, y));
    }

    return points;
}

// get All Points in Y direction
// todo add iteration
std::vector<cv::Point2f>
LaneDetectionAlgorithm::getAllPointY(cv::Point2f startPoint,
                                     cv::Point2f intersection) {

    std::vector<cv::Point2f> points;

    // compute gradient
    // y = mx + c
    float m = static_cast<float>(intersection.y - startPoint.y) /
              static_cast<float>(intersection.x - startPoint.x);
    float c = startPoint.y - m * startPoint.x;
    int start, end;

    // By Default StartPoint.y Should be ALways LARGER (located lower
    // position) than Intersection.y in any Directions
    if (startPoint.y < intersection.y) {
        std::cout << "SOMETHING SUSSY HAPPENED" << std::endl;
        std::cout << "STARTPOINT Y SHOULD BE LARGER THAN INTERSECTION Y"
                  << std::endl;
        exit(1);
    } else {
        start = startPoint.y;
        end = intersection.y;
    }

    // y start from bottom (Have larger number)
    // y progress towards intersection usually located above
    for (int y = start; y > end; y--) {
        float x = (y - c) / m;
        points.push_back(cv::Point2f(x, (float)y));
    }
    return points;
}

// evaluate line combos with requirements
double LaneDetectionAlgorithm::runEvaluation(LineCombination &l,
                                             std::vector<int> debug = {}) {
    double error;
    // midAngleError
    // evaluate the angle of the intersectionLine (left + right/2)
    // road mid angle shod be almost the same as ROI mid angle
    // the further the angle from ROI higher punishment
    double midAngleError = 0;
    if (l.midAngle != roiData.midAngle) {
        midAngleError += abs(l.midAngle - roiData.midAngle) * 10;
    }

    // angleBetweenError
    // evaluate the angle between left and right line
    // By Default the angle between left and right line should be larger
    // than ROI if the angle is smaller than ROI higher punishment
    double angleBetweenError = 0;
    if (l.angleBetween < roiData.angleBetween) {
        angleBetweenError += (roiData.angleBetween / l.angleBetween) * 10;
    }

    // roiIntersectionPointError
    // evaluate the intersection point of the line combo
    // ! Deprecated
    // // By Default the merging of lineCombo should be higher location than
    // ROI
    // // in some cases the intersection point of line combo is lower than
    // ROI
    // // thus tolerance is given 5 % of the Frame height
    // // any value larger will result in higher punishment
    // // if lineCombo is heading to the left side of the frame (180-270)
    // // the intersection point should be located (right-er) than ROI +
    // // tolerance
    // // if lineCombo is heading to the right side of the frame (270-360)
    // // the intersection point should be located (left-er) than ROI +
    // // tolerance

    double roiIntersectionPointError = 0;
    double distX = abs(l.intersection.x - roiData.intersection.x);
    if (distX < 10) {
        roiIntersectionPointError += distX * 1;
    }

    else if (distX < 100) {
        roiIntersectionPointError += distX * 10;
    }

    else if (distX < 1000) {
        roiIntersectionPointError += distX * 100;
    }

    else {
        roiIntersectionPointError += distX * 1000;
    }

    double distY = abs(l.intersection.y - roiData.intersection.y);
    if (distY < 10) {
        roiIntersectionPointError += distY * 1;
    }

    else if (distY < 100) {
        roiIntersectionPointError += distY * 10;
    }

    else if (distY < 1000) {
        roiIntersectionPointError += distY * 100;
    }

    else {
        roiIntersectionPointError += distY * 1000;
    }

    error = midAngleError + angleBetweenError + roiIntersectionPointError;

    for (int debugNr : debug) {
        if (debugNr == l.id) {
            std::cout << "id: " << l.id << std::endl;
            std::cout << "intersection: " << l.intersection << std::endl;
            std::cout << "distX: " << distX
                      << "  l.intersection.x: " << l.intersection.x
                      << "   roiData.intersection.x: " << roiData.intersection.x
                      << std::endl;
            std::cout << "distY: " << distY
                      << "  l.intersection.y: " << l.intersection.y
                      << "   roiData.intersection.y: " << roiData.intersection.y
                      << std::endl;
            std::cout << "midAngleError: " << midAngleError
                      << "  l.midAngle:" << l.midAngle
                      << "  roi.midAngle: " << roiData.midAngle << std::endl;
            std::cout << "angleBetweenError: " << angleBetweenError
                      << std::endl;
            std::cout << "roiIntersectionPointError: "
                      << roiIntersectionPointError << std::endl;
            std::cout << "error: " << error << std::endl;
            std::cout << "====================" << std::endl;
        }
    }
    return error;
}