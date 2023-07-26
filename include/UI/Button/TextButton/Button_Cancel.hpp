#include "UI/Theme/Data.hpp"
#include <UI/Button/TextButton/TextButton.hpp>

class CancelTextButton : public TextButton {
  public:
    CancelTextButton(wxWindow *parent, wxWindowID id,
                     const TextButtonData &data = Data::CancelTextButton);

  protected:
  private:
};