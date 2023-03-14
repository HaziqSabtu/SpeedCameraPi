
#ifndef SPEED_TASK_HPP
#define SPEED_TASK_HPP

#include <Algorithm/speed_calculation/speedCalculation.hpp>
#include <Thread/Task/Task.hpp>
#include <Utils/DataStruct.hpp>
#include <Utils/Struct/D_Line.hpp>

class SpeedTask : public Task {
  public:
    SpeedTask(std::vector<ImageData> *imgData,
              std::vector<Detection::Line> &selectedLine,
              std::unique_ptr<float> &result);
    void Execute() override;
    TaskProperty GetProperty() const override;
    std::string GetName() const override;

  private:
    const TaskProperty property;

    std::vector<ImageData> *imgData;
    std::vector<Detection::Line> selectedLine;
    std::unique_ptr<float> &result;
};

#endif