#include <UI/SelectLinePanel/bit.hpp>

Bit::Bit(wxWindow *parent, wxWindowID id) : wxPanel(parent, id) {
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    m_bitmap = new SelectLineBitmap(this, wxID_ANY, wxNullBitmap);
    ptns = new std::vector<cv::Point2f>();
    m_bitmap->SetPoints(ptns);
    m_bitmap->Bind(wxEVT_LEFT_DOWN, &Bit::OnLeftDown, this);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_bitmap, 1, wxEXPAND);
    SetSizer(sizer);
}

void Bit::SetImage(cv::Mat &img) {
    this->img = img.clone();
    m_bitmap->SetImage(img);
}

void Bit::OnLeftDown(wxMouseEvent &e) {
    wxPoint mousePos = e.GetPosition();
    wxLogMessage("[LOGGING] Left Mouse Clicked: Current MousePos: (%d, %d) "
                 "---> Real MousePos: ",
                 mousePos.x, mousePos.y);
    wxPoint realPos = m_bitmap->GetRealMousePos(mousePos);
    cv::Point2f p(realPos.x, realPos.y);
    ptns->push_back(p);
    m_bitmap->drawBitMap();
}

void Bit::OnSize(wxSizeEvent &e) {
    m_bitmap->SetSize(GetSize());
    m_bitmap->drawBitMap();
}

// clang-format off
wxBEGIN_EVENT_TABLE(Bit, wxPanel)
EVT_SIZE(Bit::OnSize)
wxEND_EVENT_TABLE()
