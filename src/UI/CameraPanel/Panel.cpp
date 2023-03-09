#include <UI/CameraPanel/Panel.hpp>

CameraPanel::CameraPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id) {
    button_panel = new CameraPanelButton(this, Enum::CP_BUTTON_PANEL_ID);

    img_bitmap = new CameraBitmap(this, Enum::CP_IMG_PANEL_ID);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(img_bitmap, 1, wxEXPAND);

    SetSizer(main_sizer);
    Fit();

    img_bitmap->Bind(wxEVT_SIZE, &CameraPanel::OnSize, this);
    img_bitmap->Bind(wxEVT_LEFT_DOWN, &CameraPanel::OnLeftDown, this);

    Bind(SET_IMAGE_EVENT_TYPE, &CameraPanel::OnSetImage, this);
};

CameraPanel::~CameraPanel() { delete m_imageThread; }

void CameraPanel::OnLeftDown(wxMouseEvent &e) {}

void CameraPanel::OnSize(wxSizeEvent &e) { img_bitmap->drawBitMap(); }

void CameraPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::CP_Capture_Button_ID) {
        // OnCapture();
        if (m_imageThread == nullptr) {
            m_imageThread = new ImageThread(this);
            m_imageThread->Run();
        }
    }

    if (e.GetId() == Enum::CP_Load_Button_ID) {
        // OnLoadFile();
        if (m_imageThread != nullptr) {
            m_imageThread->Delete();
            m_imageThread->Wait();
            delete m_imageThread;
            m_imageThread = nullptr;
        }
    }

    if (e.GetId() == Enum::CP_Camera_Button_ID) {
        // OnToggleCamera();
    }
}

void CameraPanel::OnSetImage(SetImageEvent &e) {
    std::cout << "test2" << std::endl;
    // Get the image data from the custom event
    std::string imageData = e.GetImageData();
    std::cout << "Image data: " << imageData << std::endl;
    // Convert the image data to a wxImage
    // wxImage image(imageData.cols, imageData.rows, imageData.data, true);
    // if (image.IsOk()) {
    //     // Convert the wxImage to a wxBitmap
    //     m_bitmap = wxBitmap(image);
    //     Refresh();
    // }
}

// clang-format off
wxBEGIN_EVENT_TABLE(CameraPanel, wxPanel) 
    EVT_MYFOO(wxID_ANY, CameraPanel::OnSetImage)
    EVT_BUTTON(wxID_ANY, CameraPanel::OnButton)
wxEND_EVENT_TABLE()
