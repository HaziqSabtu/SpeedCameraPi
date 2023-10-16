#include <UI/Panel/Common/DividerPanel.hpp>

DividerPanel::DividerPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY) {
    m_lineColor = wxColour(0, 0, 0); // Default line color is black

    // Bind the paint event to the OnPaint function
    Bind(wxEVT_PAINT, &DividerPanel::OnPaint, this);
}

void DividerPanel::OnPaint(wxPaintEvent &event) {
    wxPaintDC dc(this);
    dc.SetPen(wxPen(m_lineColor, 1, wxPENSTYLE_SOLID));
    dc.DrawLine(0, 0, GetClientSize().GetWidth(), 0);
}

void DividerPanel::SetLineColor(const wxColour &color) {
    m_lineColor = color;
    Refresh(); // Redraw the panel
}

// clang-format off
wxBEGIN_EVENT_TABLE(DividerPanel, wxPanel) 
    EVT_PAINT(DividerPanel::OnPaint)
wxEND_EVENT_TABLE()