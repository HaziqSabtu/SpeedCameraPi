#include "UI/Theme/Theme.hpp"
#include <UI/Panel/Base/Panel_Image.hpp>
#include <wx/gdicmn.h>
#include <wx/gtk/bitmap.h>
#include <wx/gtk/colour.h>

BaseImagePanel::BaseImagePanel(wxPanel *parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(640, 480)) {
    noImageBitmap = createBitmapPNG(noImage);
    errorBitmap = createBitmapText("Error");

    image = noImageBitmap;

    w = -1;
    h = -1;
}

void BaseImagePanel::setImage(wxBitmap &image) {
    this->image = image;
    Refresh();
}

void BaseImagePanel::setNoImage() {
    image = noImageBitmap;
    Refresh();
}

wxSize BaseImagePanel::getImageSize() { return image.GetSize(); }

const wxBitmap BaseImagePanel::createBitmapText(wxString text) {
    wxImage image(DEF_WIDTH, DEF_HEIGHT, true);

    for (int i = 0; i < DEF_WIDTH; i++) {
        for (int j = 0; j < DEF_HEIGHT; j++) {
            wxColour color = Theme::ImageBackground;
            image.SetRGB(i, j, color.Red(), color.Green(), color.Blue());
        }
    }

    wxFont font(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_NORMAL, false, "Roboto");

    wxBitmap bitmap(image);

    wxMemoryDC dc;
    dc.SelectObject(bitmap);
    dc.SetFont(font);
    dc.SetTextForeground(Theme::ImageText);
    dc.SetTextBackground(Theme::ImageBackground);

    wxSize size = dc.GetTextExtent(text);

    int x = (DEF_WIDTH - size.GetWidth()) / 2;
    int y = (DEF_HEIGHT - size.GetHeight()) / 2;

    dc.DrawText(text, x, y);

    dc.SelectObject(wxNullBitmap);

    return bitmap;
}
const wxBitmap BaseImagePanel::createBitmapPNG(wxString fileName) {
    wxImage image(DEF_WIDTH, DEF_HEIGHT, true);

    for (int i = 0; i < DEF_WIDTH; i++) {
        for (int j = 0; j < DEF_HEIGHT; j++) {
            wxColour color = Theme::ImageBackground;
            image.SetRGB(i, j, color.Red(), color.Green(), color.Blue());
        }
    }

    wxImage pngImage(fileName, wxBITMAP_TYPE_PNG);
    if (!pngImage.IsOk()) {
        return createBitmapText("No Image");
    }

    for (int i = 0; i < pngImage.GetWidth(); i++) {
        for (int j = 0; j < pngImage.GetHeight(); j++) {
            wxColour color =
                pngImage.GetRed(i, j) == 0 && pngImage.GetGreen(i, j) == 0 &&
                        pngImage.GetBlue(i, j) == 0
                    ? Theme::ImageBackground
                    : wxColour(pngImage.GetRed(i, j), pngImage.GetGreen(i, j),
                               pngImage.GetBlue(i, j));
            pngImage.SetRGB(i, j, color.Red(), color.Green(), color.Blue());
        }
    }

    int x = (DEF_WIDTH - pngImage.GetWidth()) / 2;
    int y = (DEF_HEIGHT - pngImage.GetHeight()) / 2;

    pngImage.ClearAlpha();
    image.Paste(pngImage, x, y);

    return wxBitmap(image);
}

void BaseImagePanel::calcRatio(wxDC &dc) {
    int newW, newH;
    dc.GetSize(&newW, &newH);
    if (newW == w && newH == h) {
        return;
    }
    w = newW;
    h = newH;
}

void BaseImagePanel::render(wxDC &dc) {
    calcRatio(dc);

    if (!image.IsOk()) {
        image = errorBitmap;
    }

    widthRatio = (float)image.GetWidth() / (float)w;
    heightRatio = (float)image.GetHeight() / (float)h;

    resized = resize(image, wxSize(w, h));

    dc.DrawBitmap(resized, 0, 0, false);
}

wxBitmap BaseImagePanel::resize(wxBitmap &bitmap, const wxSize &size) {
    wxImage image = bitmap.ConvertToImage();
    image.Rescale(size.GetWidth(), size.GetHeight(), wxIMAGE_QUALITY_HIGH);
    return wxBitmap(image);
}

void BaseImagePanel::OnPaint(wxPaintEvent &e) {
    wxPaintDC dc(this);
    render(dc);
}

void BaseImagePanel::OnSize(wxSizeEvent &event) {
    Refresh();
    event.Skip();
}

BEGIN_EVENT_TABLE(BaseImagePanel, wxPanel)
EVT_PAINT(BaseImagePanel::OnPaint)
EVT_SIZE(BaseImagePanel::OnSize)
END_EVENT_TABLE()