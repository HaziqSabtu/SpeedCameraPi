#include <UI/CameraPanel/Panel.hpp>

CameraPanel::CameraPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id), imgData(nullptr), threadPool(1),
      processThread(nullptr), houghThread(nullptr) {
    button_panel = new CameraPanelButton(this, Enum::CP_BUTTON_PANEL_ID,
                                         &camera, &threadPool);
    button_panel_hough =
        new ButtonPanelHough(this, Enum::CP_BUTTON_PANEL_HOUGH_ID);

    img_bitmap = new wxImagePanel(this);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(button_panel_hough, 0, wxEXPAND);
    main_sizer->Add(img_bitmap, 1, wxEXPAND);

    button_panel_hough->Hide();
    SetSizer(main_sizer);
    Fit();

    // img_bitmap->Bind(wxEVT_SIZE, &CameraPanel::OnSize, this);
    // img_bitmap->Bind(wxEVT_LEFT_DOWN, &CameraPanel::OnLeftDown, this);

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

    if (processThread != nullptr) {
        processThread->Delete();
        processThread->Wait();
        delete processThread;
        processThread = nullptr;
    }

    if (houghThread != nullptr) {
        houghThread->Delete();
        houghThread->Wait();
        delete houghThread;
        houghThread = nullptr;
    }

    delete button_panel;
    delete img_bitmap;
}

void CameraPanel::OnIncrement() {
    currentImageIndex < imgData->size() - 1 ? currentImageIndex++
                                            : currentImageIndex;
}

void CameraPanel::OnDecrement() {
    currentImageIndex > 0 ? currentImageIndex-- : currentImageIndex;
}

void CameraPanel::OnButton(wxCommandEvent &e) {

    if (e.GetId() == Enum::CP_Camera_Button_ID) {
        button_panel->Hide();
        button_panel_hough->Show();
        GetSizer()->Layout();
    }

    // if (e.GetId() == Enum::CP_Canny_Button_ID) {
    //     button_panel_hough->Hide();
    //     button_panel->Show();
    //     GetSizer()->Layout();
    // }

    if (e.GetId() == Enum::CP_Next_Button_ID) {
        OnIncrement();
        if (!imgData->at(currentImageIndex).hough.lines.empty()) {
            // img_bitmap->SetImage(imgData->at(currentImageIndex).hough.canny);
            img_bitmap->SetImageData(imgData->at(currentImageIndex));
            return;
        }
        if (houghThread != nullptr) {
            houghThread->Delete();
            houghThread->Wait();
            delete houghThread;
            houghThread = nullptr;
        }
        houghThread = new HoughThread(button_panel_hough, &threadPool,
                                      imgData->at(currentImageIndex));
        houghThread->Run();
    }

    if (e.GetId() == Enum::CP_Prev_Button_ID) {
        OnDecrement();
        if (!imgData->at(currentImageIndex).hough.lines.empty()) {
            // img_bitmap->SetImage(imgData->at(currentImageIndex).hough.canny);
            img_bitmap->SetImageData(imgData->at(currentImageIndex));
            return;
        }
        if (houghThread != nullptr) {
            houghThread->Delete();
            houghThread->Wait();
            delete houghThread;
            houghThread = nullptr;
        }
        houghThread = new HoughThread(button_panel_hough, &threadPool,
                                      imgData->at(currentImageIndex));
        houghThread->Run();
    }

    if (e.GetId() == Enum::CP_Canny_Button_ID) {
        button_panel_hough->GetCannyState()
            ? img_bitmap->SetShowType(SHOW_TYPE_CANNY)
            : img_bitmap->SetShowType(SHOW_TYPE_IMAGE);
    }

    if (e.GetId() == Enum::CP_Hough_Button_ID) {
        img_bitmap->SetShowHoughLine(button_panel_hough->GetHoughState());
    }
}

void CameraPanel::OnUpdateImage(UpdateImageEvent &e) {
    if (e.GetId() == UPDATE_IMAGE) {
        // cv::Mat imageData = e.GetImage();
        ImageData iData = ImageData(e.GetImage());
        // img_bitmap->SetImage(imageData);
        img_bitmap->SetImageData(iData);
        // img_bitmap->SetImageData(imgData->at(currentImageIndex));
    }

    if (e.GetId() == CLEAR_IMAGE) {
        // img_bitmap->SetImage();
        img_bitmap->SetImageData();
    }
}

void CameraPanel::OnProcessImage(wxCommandEvent &e) {
    if (e.GetId() == PROCESS_BEGIN) {

        processThread = new ProcessThread(this, &threadPool, imgData);
        processThread->Run();

        houghThread = new HoughThread(button_panel_hough, &threadPool,
                                      imgData->at(currentImageIndex));
        houghThread->Run();

        img_bitmap->SetShowHoughLine(true);
    } else if (e.GetId() == PROCESS_END) {
        // start speed calculation
    }
}

void CameraPanel::OnCaptureImage(CaptureImageEvent &e) {
    if (e.GetId() == CAPTURE_END) {
        imgData = e.GetImageData();

        button_panel->Hide();
        button_panel_hough->Show();
        GetSizer()->Layout();
    }
}

void CameraPanel::OnHough(HoughEvent &e) {
    if (e.GetId() == HOUGH_END) {
        imgData->at(currentImageIndex).SetHough(*e.GetHoughData());
        img_bitmap->SetImageData(imgData->at(currentImageIndex));
    }
}

// clang-format off
wxBEGIN_EVENT_TABLE(CameraPanel, wxPanel) 
    EVT_HOUGH(wxID_ANY, CameraPanel::OnHough)
    EVT_UPDATEIMAGE(wxID_ANY, CameraPanel::OnUpdateImage)
    EVT_CAPTUREIMAGE(wxID_ANY, CameraPanel::OnCaptureImage)
    EVT_COMMAND(wxID_ANY, c_PROCESS_IMAGE_EVENT ,CameraPanel::OnProcessImage)
    EVT_BUTTON(wxID_ANY, CameraPanel::OnButton)
wxEND_EVENT_TABLE()
