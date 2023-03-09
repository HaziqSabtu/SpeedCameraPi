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

    AppConfig *config = new AppConfig();
    CameraConfig cameraConfig = config->GetCameraConfig();
    camera.open(cameraConfig.Camera_ID);
    if (!camera.isOpened()) {
        wxMessageBox("Could not open camera", "Error", wxOK | wxICON_ERROR);
        Close();
    }
    camera.set(cv::CAP_PROP_FRAME_WIDTH, cameraConfig.Camera_Width);
    camera.set(cv::CAP_PROP_FRAME_HEIGHT, cameraConfig.Camera_Height);
    camera.set(cv::CAP_PROP_FPS, cameraConfig.Camera_FPS);
};

CameraPanel::~CameraPanel() {
    if (camera.isOpened()) {
        camera.release();
    }

    if (m_imageThread != nullptr) {
        m_imageThread->Delete();
        m_imageThread->Wait();
        delete m_imageThread;
        m_imageThread = nullptr;
    }
}

void CameraPanel::OnLeftDown(wxMouseEvent &e) {}

void CameraPanel::OnSize(wxSizeEvent &e) { img_bitmap->drawBitMap(); }

void CameraPanel::OnButton(wxCommandEvent &e) {
    if (e.GetId() == Enum::CP_Capture_Button_ID) {
        // OnCapture();
        if (m_imageThread == nullptr) {
            m_imageThread = new ImageThread(this, &camera);
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

void CameraPanel::OnImageUpdate(UpdateImageEvent &e) {
    cv::Mat imageData = e.GetImageData();
    img_bitmap->SetImage(imageData);
}

// clang-format off
wxBEGIN_EVENT_TABLE(CameraPanel, wxPanel) 
    EVT_UPDATEIMAGE(wxID_ANY, CameraPanel::OnImageUpdate)
    EVT_BUTTON(wxID_ANY, CameraPanel::OnButton)
wxEND_EVENT_TABLE()
