#include <Algorithm/image_stabilizer/FeatureDetector.hpp>

FeatureDetector::FeatureDetector(std::string type, bool imgMatches,
                                 bool imgFillOutput)
    : detector_type_(type), drawMatches_(imgMatches),
      drawFillOutput_(imgFillOutput) {
    std::cout << "type: " << type << std::endl;
    if (detector_type_ == "SIFT") {
        std::cout << "SIFT" << std::endl;
        detector_ = cv::SIFT::create();
        // detector = cv::SIFT::create(100);

    } else {
        detector_ = cv::ORB::create(nfeatures, scaleFactor, nlevels,
                                    edgeThreshold, firstLevel, WTA_K, scoreType,
                                    patchSize, fastThreshold);
    }
}

FeatureDetector::FeatureDetector() { FeatureDetector("SIFT", false, false); }

void FeatureDetector::run(cv::Mat &image1, cv::Mat &image2) {
    FeatureDetector::clearVector();
    detector_->detectAndCompute(image1, cv::Mat(), keyPoints1, descriptors1);
    detector_->detectAndCompute(image2, cv::Mat(), keyPoints2, descriptors2);

    DESCRIPTORMATCHER::FlannBasedMatcher(descriptors1, descriptors2, matchKP,
                                         "SIFT");
    DESCRIPTORMATCHER::FilterKeyPoints(matchKP, filterKP, 0.3);
    if (drawMatches_) {
        cv::drawMatches(image1, keyPoints1, image2, keyPoints2, filterKP,
                        siftResult, cv::Scalar::all(-1), cv::Scalar::all(-1),
                        std::vector<char>(),
                        cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    }

    HOMOGRAPHY::FindHomography(keyPoints1, keyPoints2, filterKP, obj, scene,
                               homographyMatrix, detector_type_);
    HOMOGRAPHY::PerscpectiveTransform(image2, transform, homographyMatrix);

    if (drawFillOutput_) {
        HOMOGRAPHY::FillTransform(image1, transform, homographyMatrix,
                                  fillOutput);
    }
}

void FeatureDetector::processImageData(std::vector<ImgData> &imgData) {
    cv::Mat firstImg = imgData.front().image;
    for (ImgData &img : imgData) {
        run(firstImg, img.image);
        img.image = transform.clone();
    }
}

cv::Mat FeatureDetector::GetFillOutput() { return fillOutput; }
cv::Mat FeatureDetector::GetTransform() { return transform; }