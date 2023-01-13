#include "OtherFrame.hpp"
#include <wx/wx.h>

OtherFrame::OtherFrame() : wxFrame(nullptr, wxID_ANY, "Other Frame") {
    m_button = new wxButton(this, ID_BUTTON2, "Open Frame 1");
}

void OtherFrame::OnOpenFrame1(wxCommandEvent &event) {
    this->Destroy();
    //
}

// clang-format off
wxBEGIN_EVENT_TABLE(OtherFrame, wxFrame)
EVT_BUTTON(ID_BUTTON2, OtherFrame::OnOpenFrame1) 
wxEND_EVENT_TABLE()