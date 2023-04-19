#include <UI/Panel/RoiPanel/Panel_Image.hpp>

RoiImagePanel::RoiImagePanel(wxPanel *parent) : BaseImagePanel(parent) {
    Bind(wxEVT_LEFT_DOWN, &RoiImagePanel::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &RoiImagePanel::OnLeftUp, this);
    Bind(wxEVT_MOTION, &RoiImagePanel::OnMotion, this);
}

void RoiImagePanel::render(wxDC &dc) {
    calcRatio(dc);

    if (!image.IsOk()) {
        image = errorBitmap;
    }

    widthRatio = (float)image.GetWidth() / (float)w;
    heightRatio = (float)image.GetHeight() / (float)h;

    resized = resize(image, wxSize(w, h));

    dc.DrawBitmap(resized, 0, 0, false);

    wxBrush greenBrush(wxColour(255, 0, 0, 50), wxBRUSHSTYLE_SOLID);
    dc.SetBrush(greenBrush);
    dc.DrawRectangle(0, 0, w, h);

    if (rect.IsEmpty()) {
        return;
    }

    wxBitmap cropped = CropBitmap(resized, rect);
    dc.DrawBitmap(cropped, rect.GetX(), rect.GetY(), false);
}

wxBitmap RoiImagePanel::CropBitmap(wxBitmap &originalBitmap, wxRect region) {
    wxMemoryDC originalDC(originalBitmap);
    wxBitmap croppedBitmap(region.width, region.height);
    wxMemoryDC croppedDC(croppedBitmap);

    croppedDC.Blit(0, 0, region.width, region.height, &originalDC, region.x,
                   region.y);

    return croppedBitmap;
}

wxRect RoiImagePanel::getRect(wxPoint p1, wxPoint p2) {
    int x = p1.x < p2.x ? p1.x : p2.x;
    int y = p1.y < p2.y ? p1.y : p2.y;
    int width = abs(p1.x - p2.x);
    int height = abs(p1.y - p2.y);

    return wxRect(x, y, width, height);
}

void RoiImagePanel::OnLeftDown(wxMouseEvent &e) {
    p1 = e.GetPosition();
    isDown = true;
}

void RoiImagePanel::OnLeftUp(wxMouseEvent &e) {

    if (!isDown) {
        return;
    }

    isDown = false;

    wxPoint p2 = e.GetPosition();

    rect = getRect(p1, p2);

    Refresh();
}

void RoiImagePanel::OnMotion(wxMouseEvent &e) {

    if (!isDown) {
        return;
    }

    wxPoint p2 = e.GetPosition();

    rect = getRect(p1, p2);

    Refresh();
}

BEGIN_EVENT_TABLE(RoiImagePanel, BaseImagePanel)
END_EVENT_TABLE()