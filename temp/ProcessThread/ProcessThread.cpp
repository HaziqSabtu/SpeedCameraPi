#include <Thread/ProcessThread.hpp>

ProcessThread::ProcessThread(std::vector<ImageData> *imgData, int id)
    : wxThread(wxTHREAD_JOINABLE), imgData(imgData), id(id) {
    wxLogMessage("creating new thread");
    featureDetector = FeatureDetector("SIFT", false, false);
    firstImage = imgData->at(0);
    targetImage = imgData->at(id);
}

ProcessThread::~ProcessThread() { wxLogMessage("deleting Process thread"); }

void *ProcessThread::Entry() {
    wxLogMessage("running on Process thread");
    try {
        featureDetector.run(firstImage.image, targetImage.image);
        imgData->at(id).image = featureDetector.GetTransform().clone();
    } catch (cv::Exception &e) {
        std::cout << "Exception from : " << id << "  ---> " << e.what()
                  << std::endl;
    }
    return NULL;
};
