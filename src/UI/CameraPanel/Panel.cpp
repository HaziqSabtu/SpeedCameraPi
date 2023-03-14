#include <UI/CameraPanel/Panel.hpp>

CameraPanel::CameraPanel(wxWindow *parent, wxWindowID id)
    : wxPanel(parent, id), imgData(nullptr), threadPool(3),
      processThread(nullptr), houghThread(nullptr), resultThread(nullptr),
      speedThread(nullptr) {
    button_panel = new CameraPanelButton(this, Enum::CP_BUTTON_PANEL_ID,
                                         &camera, &threadPool);
    button_panel_hough =
        new ButtonPanelHough(this, Enum::CP_BUTTON_PANEL_HOUGH_ID);
    button_panel_result =
        new PanelButtonResult(this, Enum::CP_BUTTON_PANEL_RESULT_ID);

    img_bitmap = new wxImagePanel(this);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    main_sizer->Add(button_panel_hough, 0, wxEXPAND);
    main_sizer->Add(button_panel_result, 0, wxEXPAND);
    main_sizer->Add(img_bitmap, 1, wxEXPAND);

    button_panel_hough->Hide();
    button_panel_result->Hide();

    SetSizer(main_sizer);
    Fit();

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

    if (resultThread != nullptr) {
        resultThread->Delete();
        resultThread->Wait();
        delete resultThread;
        resultThread = nullptr;
    }
}

void CameraPanel::OnIncrement() {
    currentImageIndex < imgData->size() - 1 ? currentImageIndex++
                                            : currentImageIndex;
}

void CameraPanel::OnDecrement() {
    currentImageIndex > 0 ? currentImageIndex-- : currentImageIndex;
}

void CameraPanel::OnButton(wxCommandEvent &e) {

    if (e.GetId() == Enum::CP_Next_Button_ID ||
        e.GetId() == Enum::CP_Prev_Button_ID) {
        e.GetId() == Enum::CP_Next_Button_ID ? OnIncrement() : OnDecrement();
        if (!imgData->at(currentImageIndex).hough.lines.empty()) {
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

    if (e.GetId() == Enum::CP_Clear_Button_ID) {
        selectedLine.clear();
        img_bitmap->SetSelectedLine(selectedLine);
    }

    if (e.GetId() == Enum::CP_Replay_Button_ID) {
        if (resultThread != nullptr) {
            resultThread->Delete();
            resultThread->Wait();
            delete resultThread;
            resultThread = nullptr;
        }
        resultThread = new ResultThread(button_panel_result, imgData);
        resultThread->Run();
    }

    if (e.GetId() == Enum::CP_BBox_Button_ID) {
        img_bitmap->SetIsRect(button_panel_result->GetBBoxState());
    }

    if (e.GetId() == Enum::CP_BotL_Button_ID) {
        img_bitmap->SetIsBotLine(button_panel_result->GetBotLState());
    }

    if (e.GetId() == Enum::CP_OptF_Button_ID) {
        img_bitmap->SetIsOFPoint(button_panel_result->GetOFPntState());
    }

    if (e.GetId() == Enum::CP_SelL_Button_ID) {
        img_bitmap->SetShowSelectedLine(button_panel_result->GetSelLState());
    }

    if (e.GetId() == Enum::CP_Reselect_Button_ID) {
        button_panel_result->Hide();
        button_panel_hough->Show();
        GetSizer()->Layout();
        img_bitmap->SetShowSelectedLine(true);
    }
}

void CameraPanel::OnUpdateImage(UpdateImageEvent &e) {
    if (e.GetId() == UPDATE_IMAGE) {
        ImageData iData = e.GetImageData();
        img_bitmap->SetImageData(iData);
    }

    if (e.GetId() == CLEAR_IMAGE) {
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
    if (e.GetId() == CAPTURE_START) {
        img_bitmap->SetShowType(SHOW_TYPE_IMAGE);
    } else if (e.GetId() == CAPTURE_END) {
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

void CameraPanel::OnLeftDown(wxMouseEvent &e) {
    wxPoint mousePos = e.GetPosition();
    cv::Point2f p = img_bitmap->calcMousePos(mousePos);
    selectedPoint.push_back(p);
    img_bitmap->SetSelectedPoint(selectedPoint);
    img_bitmap->SetShowSelectedLine(true);
    searchLine(p);
}

void CameraPanel::OnSpeed(SpeedCalcEvent &e) {
    if (e.GetId() == CALC_OK) {
        img_bitmap->SetSpeed(e.GetSpeed());
    }
}

void CameraPanel::searchLine(cv::Point2f realMousePos) {
    std::vector<Detection::Line> detLines;
    std::vector<Detection::Line> linesP =
        imgData->at(currentImageIndex).hough.lines;

    if (linesP.empty()) {
        return;
    }

    for (auto line : linesP) {
        if (line.isIntersect(realMousePos, 20)) {
            detLines.push_back(line);
        }
    }

    if (detLines.size() == 0) {
        return;
    }

    Detection::Line avgLine = Detection::Line::Average(detLines);
    addLine(avgLine.Extrapolate(imgData->at(currentImageIndex).image));
}

void CameraPanel::addLine(Detection::Line line) {
    if (selectedLine.size() <= 1) {
        selectedLine.push_back(line);
    } else {
        selectedLine[1] = line;
    }
    img_bitmap->SetSelectedLine(selectedLine);
    wxYield();

    if (selectedLine.size() == 2) {
        button_panel_result->Show();
        button_panel_hough->Hide();
        GetSizer()->Layout();

        if (processThread != nullptr) {
            processThread->Delete();
            processThread->Wait();
            delete processThread;
            processThread = nullptr;
        }

        if (speedThread != nullptr) {
            speedThread->Delete();
            speedThread->Wait();
            delete speedThread;
            speedThread = nullptr;
        }

        speedThread = new SpeedThread(button_panel_result, &threadPool, imgData,
                                      selectedLine);
        speedThread->Run();
        resultThread = new ResultThread(button_panel_result, imgData);
        resultThread->Run();
        img_bitmap->SetShowType(SHOW_TYPE_IMAGE);
        img_bitmap->SetIsRect(button_panel_result->GetBBoxState());
        img_bitmap->SetIsOFPoint(button_panel_result->GetOFPntState());
        img_bitmap->SetIsBotLine(button_panel_result->GetBotLState());
        img_bitmap->SetShowSelectedLine(button_panel_result->GetSelLState());
    }
}

// clang-format off
wxBEGIN_EVENT_TABLE(CameraPanel, wxPanel) 
    EVT_SPEED(wxID_ANY, CameraPanel::OnSpeed)
    EVT_HOUGH(wxID_ANY, CameraPanel::OnHough)
    EVT_UPDATEIMAGE(wxID_ANY, CameraPanel::OnUpdateImage)
    EVT_CAPTUREIMAGE(wxID_ANY, CameraPanel::OnCaptureImage)
    EVT_COMMAND(wxID_ANY, c_PROCESS_IMAGE_EVENT ,CameraPanel::OnProcessImage)
    EVT_BUTTON(wxID_ANY, CameraPanel::OnButton)
    EVT_LEFT_DOWN(CameraPanel::OnLeftDown)
wxEND_EVENT_TABLE()
