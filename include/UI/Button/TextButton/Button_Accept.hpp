#include "UI/Theme/Data.hpp"
#include <UI/Button/TextButton/TextButton.hpp>

class AcceptTextButton : public TextButton {
  public:
    AcceptTextButton(wxWindow *parent, wxWindowID id,
                     const TextButtonData &data = Data::AcceptTextButton);

  protected:
  private:
};