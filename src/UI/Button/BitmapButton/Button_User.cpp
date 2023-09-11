#include "UI/Button/BitmapButton/Button_User.hpp"
#include "UI/Data/Data.hpp"
#include "UI/Data/Theme.hpp"

BitmapUser::BitmapUser(wxWindow *parent, wxWindowID id)
    : BitmapButton(parent, id, Data::BitmapUser) {}