#include "UI/Theme/Data.hpp"
#include <UI/Button/TextButton/TextButton.hpp>

class BackTextButton : public TextButton {
  public:
    BackTextButton(wxWindow *parent, wxWindowID id,
                   const TextButtonData &data = Data::BackTextButton);

  protected:
  private:
};