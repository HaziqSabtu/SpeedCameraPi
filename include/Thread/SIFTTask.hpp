#ifndef SIFT_TASK_HPP
#define SIFT_TASK_HPP

#include <Algorithm/image_stabilizer/FeatureDetector.hpp>
#include <Thread/Task.hpp>
#include <Utils/DataStruct.hpp>

class SiftTask : public Task {
  public:
    SiftTask(std::vector<ImageData> *imgData, int id) {
        this->imgData = imgData;
        this->id = id;
    }
    virtual void Execute() {
        ImageData firstImage = (*imgData)[0];
        ImageData targetImage = (*imgData)[id];
        FeatureDetector featureDetector = FeatureDetector("SIFT", false, false);
        featureDetector.run(firstImage.image, targetImage.image);
        imgData->at(id).image = featureDetector.GetTransform().clone();
    }

  private:
    int id;
    std::vector<ImageData> *imgData;
};

#endif