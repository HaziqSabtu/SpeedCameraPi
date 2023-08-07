#include "UI/Theme/Data.hpp"
#include <UI/Button/TextButton/TextButton.hpp>

class MeasureTextButton : public TextButton {
  public:
    MeasureTextButton(wxWindow *parent, wxWindowID id,
                      const TextButtonData &data = Data::MeasureTextButton);

  protected:
  private:
};