#include <Utils/FileReader/fileWR.hpp>
#include <gtest/gtest.h>

// TODO: Add tests for the following functions:
class FILEWRTest : public testing::Test {
  public:
    FILEWRTest() {}
    ~FILEWRTest() {}

  protected:
    virtual void SetUp() {
        imgData = std::make_shared<std::vector<ImageData>>();
        imgData->push_back({cv::Mat(2, 2, CV_8UC3),
                            std::chrono::high_resolution_clock::now()});
    }
    std::shared_ptr<std::vector<ImageData>> imgData;
    FILEWR fileWR;
};

TEST_F(FILEWRTest, TestReadFile) {
    std::string filename = Utils::dateToString() + ".bin";
    fileWR.WriteFile(filename, imgData);
    std::shared_ptr<std::vector<ImageData>> imgDataRead =
        std::make_shared<std::vector<ImageData>>();
    fileWR.ReadFile(filename, imgDataRead);
    ASSERT_EQ(imgDataRead->size(), 1);
    ASSERT_EQ(imgDataRead->at(0).image.cols, 2);
    ASSERT_EQ(imgDataRead->at(0).image.rows, 2);
    ASSERT_EQ(imgDataRead->at(0).image.channels(), 3);
}
