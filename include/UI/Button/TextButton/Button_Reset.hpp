#include "UI/Theme/Data.hpp"
#include <UI/Button/TextButton/TextButton.hpp>

class ResetTextButton : public TextButton {
  public:
    ResetTextButton(wxWindow *parent, wxWindowID id,
                    const TextButtonData &data = Data::ResetTextButton);

  protected:
  private:
};