#pragma once

#include <UI/Button/TextButton/Type2/TextButtonT2.hpp>
#include <UI/Theme/Data.hpp>

class OnOffT2TextButton : public TextButtonT2 {
  public:
    OnOffT2TextButton(wxWindow *parent, wxWindowID id,
                      const TextButtonDataT2 &data = Data::OnOffT2TextButton);
};