#include "Model/ModelEnum.hpp"
#include <UI/CameraPanel/Panel2.hpp>
#include <wx/event.h>

CameraPanel2::CameraPanel2(wxWindow* parent,
                           wxWindowID id,
                           AppConfig* config,
                           Model* model)
    : wxPanel(parent, id), model(model) {
    //     , imgData(nullptr),
    // threadPool(config->GetPanelConfig().Thread_Pool_Size),
    // circleRadius(config->GetRadius()) {

    button_panel = new CameraPanelButton(this, Enum::CP_BUTTON_PANEL_ID);
    // button_panel_hough =
    //     new ButtonPanelHough(this, Enum::CP_BUTTON_PANEL_HOUGH_ID);
    // button_panel_result =
    //     new PanelButtonResult(this, Enum::CP_BUTTON_PANEL_RESULT_ID);

    img_bitmap = new ImagePanel(this, 10);

    main_sizer = new wxBoxSizer(wxVERTICAL);
    main_sizer->Add(button_panel, 0, wxEXPAND);
    // main_sizer->Add(button_panel_hough, 0, wxEXPAND);
    // main_sizer->Add(button_panel_result, 0, wxEXPAND);
    main_sizer->Add(img_bitmap, 1, wxEXPAND);

    // button_panel_hough->Hide();
    // button_panel_result->Hide();

    SetSizer(main_sizer);
    Fit();

    // img_bitmap->Bind(wxEVT_LEFT_DOWN, &CameraPanel2::OnLeftDown, this);

    // CameraConfig cameraConfig = config->GetCameraConfig();

    // camera.setHeight(cameraConfig.Camera_Height);
    // camera.setWidth(cameraConfig.Camera_Width);
    // camera.setFPS(cameraConfig.Camera_FPS);

    // if (!camera.start()) {
    //       wxMessageBox("Could not open camera", "Error", wxOK |
    //       wxICON_ERROR);
    //       Close();
    // }

    // processThread = nullptr;
    // houghThread = nullptr;
    // resultThread = nullptr;
    // speedThread = nullptr;
    // loadFileThread = nullptr;
    // loadCaptureThread = nullptr;
    // captureThread = nullptr;

    // captureThread = new CaptureThread(this, &camera);
    // captureThread->Run();

    // delete config;
    // config = nullptr;
}

CameraPanel2::~CameraPanel2() {

    //     waitThenDeleteThread(processThread);
    //     processThread = nullptr;

    //     deleteThread(houghThread);
    //     houghThread = nullptr;

    //     deleteThread(resultThread);
    //     resultThread = nullptr;

    //     deleteThread(speedThread);
    //     speedThread = nullptr;

    //     deleteThread(loadFileThread);
    //     loadFileThread = nullptr;

    //     deleteThread(loadCaptureThread);
    //     loadCaptureThread = nullptr;

    //     deleteThread(captureThread);
    //     captureThread = nullptr;

    //     camera.stop();

    //     if (imgData != nullptr) {
    //         imgData->clear();
    //         delete imgData;
    //         imgData = nullptr;
    //     }
}

// void CameraPanel2::OnIncrement() {
//     currentImageIndex < imgData->size() - 1 ? currentImageIndex++
//                                             : currentImageIndex;
// }

// void CameraPanel2::OnDecrement() {
//     currentImageIndex > 0 ? currentImageIndex-- : currentImageIndex;
// }

// void CameraPanel2::OnButton(wxCommandEvent &e) {
//     int id = e.GetId();

//     if (id == Enum::CP_Capture_Button_ID) {
//         AppConfig *config = new AppConfig();
//         CaptureConfig captureConfig = config->GetCaptureConfig();
//         deleteThread(captureThread);
//         captureThread = nullptr;

//         deleteThread(loadCaptureThread);
//         loadCaptureThread = new LoadCaptureThread(
//             button_panel->GetButton(CAPTURE_BUTTON), &camera,
//             captureConfig.maxFrame, captureConfig.Debug);
//         loadCaptureThread->Run();

//         delete config;
//         config = nullptr;
//     }

//     if (id == Enum::CP_Load_Button_ID) {
//         AppConfig *config = new AppConfig();
//         LoadConfig loadConfig = config->GetLoadConfig();
//         deleteThread(captureThread);
//         captureThread = nullptr;

//         deleteThread(loadFileThread);
//         loadFileThread = new LoadFileThread(
//             button_panel->GetButton(LOAD_BUTTON), &threadPool,
//             loadConfig.path, loadConfig.maxFrame);
//         loadFileThread->Run();

//         delete config;
//         config = nullptr;
//     }

//     if (id == Enum::CP_Next_Button_ID || id == Enum::CP_Prev_Button_ID)
//     {
//         id == Enum::CP_Next_Button_ID ? OnIncrement() : OnDecrement();
//         if (!imgData->at(currentImageIndex).hough.lines.empty()) {
//             img_bitmap->SetImageData(imgData->at(currentImageIndex));
//             return;
//         }
//         AppConfig *config = new AppConfig();
//         HoughConfig houghConfig = config->GetHoughConfig();
//         CannyConfig cannyConfig = config->GetCannyConfig();
//         deleteThread(houghThread);
//         houghThread = new HoughThread(button_panel_hough, &threadPool,
//                                       imgData->at(currentImageIndex),
//                                       cannyConfig, houghConfig);
//         houghThread->Run();

//         delete config;
//         config = nullptr;
//     }

//     if (id == Enum::CP_Canny_Button_ID) {
//         button_panel_hough->GetCannyState()
//             ? img_bitmap->SetShowType(SHOW_TYPE_CANNY)
//             : img_bitmap->SetShowType(SHOW_TYPE_IMAGE);
//     }

//     if (id == Enum::CP_Hough_Button_ID) {
//         img_bitmap->SetShowHoughLine(button_panel_hough->GetHoughState());
//     }

//     if (id == Enum::CP_Clear_Button_ID) {
//         selectedLine.clear();
//         img_bitmap->SetSelectedLine(selectedLine);
//     }

//     if (id == Enum::CP_Replay_Button_ID) {
//         deleteThread(resultThread);
//         resultThread = new ResultThread(button_panel_result, imgData);
//         resultThread->Run();
//     }

//     if (id == Enum::CP_BBox_Button_ID) {
//         img_bitmap->SetIsRect(button_panel_result->GetBBoxState());
//     }

//     if (id == Enum::CP_BotL_Button_ID) {
//         img_bitmap->SetIsBotLine(button_panel_result->GetBotLState());
//     }

//     if (id == Enum::CP_OptF_Button_ID) {
//         img_bitmap->SetIsOFPoint(button_panel_result->GetOFPntState());
//     }

//     if (id == Enum::CP_SelL_Button_ID) {
//         img_bitmap->SetShowSelectedLine(button_panel_result->GetSelLState());
//     }

//     if (id == Enum::CP_Reselect_Button_ID) {
//         button_panel_result->Hide();
//         button_panel_hough->Show();
//         GetSizer()->Layout();
//         img_bitmap->SetShowSelectedLine(true);
//     }

//     if (id == Enum::CP_Reset_Button_ID) {
//         waitThenDeleteThread(processThread);
//         processThread = nullptr;

//         deleteThread(houghThread);
//         houghThread = nullptr;

//         deleteThread(resultThread);
//         resultThread = nullptr;

//         deleteThread(speedThread);
//         speedThread = nullptr;

//         deleteThread(loadFileThread);
//         loadFileThread = nullptr;

//         deleteThread(loadCaptureThread);
//         loadCaptureThread = nullptr;

//         deleteThread(captureThread);
//         captureThread = nullptr;
//         captureThread = new CaptureThread(this, &camera);
//         captureThread->Run();

//         imgData->clear();
//         delete imgData;
//         imgData = nullptr;

//         selectedLine.clear();
//         selectedPoint.clear();

//         currentImageIndex = 0;
//         img_bitmap->SetDefaultState();
//         button_panel_hough->SetDefaultState();

//         if (button_panel_hough->IsShown()) {
//             button_panel_hough->Hide();
//         }

//         if (button_panel_result->IsShown()) {
//             button_panel_result->Hide();
//         }

//         button_panel->Show();
//         GetSizer()->Layout();
//     }
// }
void CameraPanel2::OnButton(wxCommandEvent& e) {
    if (e.GetId() == Enum::CP_Capture_Button_ID) {
        model->endPoint(this, ModelEnum::MODEL_START_LOADCAPTURE);
    }

    if (e.GetId() == Enum::CP_Camera_Button_ID) {
        model->endPoint(this, ModelEnum::MODEL_END_CAPTURE);
    }

    if (e.GetId() == Enum::CP_Load_Button_ID) {
        OnLoadButton(button_panel->Load_Button);
    }
}

void CameraPanel2::OnLoadButton(wxEvtHandler* parent) {
    wxFileDialog openFileDialog(this,
                                _("Open .bin file"),
                                "",
                                "",
                                "XYZ files (*.bin)|*.bin",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    std::string path = Utils::wxStringToString(openFileDialog.GetPath());
    model->endPoint(parent, ModelEnum::MODEL_START_LOADFILE, path);
}

void CameraPanel2::OnUpdateImage(UpdateImageEvent& e) {
    if (e.GetId() == UPDATE_IMAGE) {
        ImageData iData = e.GetImageData();
        img_bitmap->SetShowType(SHOW_TYPE_IMAGE);
        img_bitmap->SetImageData(iData);
    }

    if (e.GetId() == CLEAR_IMAGE) {
        img_bitmap->SetImageData();
    }
}

// void CameraPanel2::OnProcessImage(wxCommandEvent &e) {
//     if (e.GetId() == PROCESS_BEGIN) {
//         AppConfig *config = new AppConfig();
//         OpticalFlowConfig opticalFlowConfig =
//         config->GetOpticalFlowConfig();

//         waitThenDeleteThread(processThread);
//         processThread =
//             new ProcessThread(this, &threadPool, imgData,
//             opticalFlowConfig);
//         processThread->Run();

//         HoughConfig houghConfig = config->GetHoughConfig();
//         CannyConfig cannyConfig = config->GetCannyConfig();
//         deleteThread(houghThread);
//         houghThread = new HoughThread(button_panel_hough,
//         &threadPool,
//                                       imgData->at(currentImageIndex),
//                                       cannyConfig, houghConfig);
//         houghThread->Run();

//         delete config;
//         config = nullptr;

//         img_bitmap->SetShowHoughLine(true);
//     } else if (e.GetId() == PROCESS_END) {
//         waitThenDeleteThread(processThread);
//         processThread = nullptr;

//         if (selectedLine.size() == 2) {
//             button_panel_result->Show();
//             button_panel_hough->Hide();
//             GetSizer()->Layout();

//             AppConfig *config = new AppConfig();
//             SensorConfig sensorConfig = config->GetSensorConfig();

//             deleteThread(speedThread);
//             speedThread = new SpeedThread(button_panel_result,
//             &threadPool,
//                                           imgData, selectedLine,
//                                           sensorConfig);
//             speedThread->Run();

//             deleteThread(resultThread);
//             resultThread = new ResultThread(button_panel_result,
//             imgData); resultThread->Run();

//             img_bitmap->SetShowType(SHOW_TYPE_IMAGE);
//             img_bitmap->SetIsRect(button_panel_result->GetBBoxState());
//             img_bitmap->SetIsOFPoint(button_panel_result->GetOFPntState());
//             img_bitmap->SetIsBotLine(button_panel_result->GetBotLState());
//             img_bitmap->SetShowSelectedLine(
//                 button_panel_result->GetSelLState());

//             delete config;
//             config = nullptr;
//         }
//     }
// }

// void CameraPanel2::OnCaptureImage(CaptureImageEvent &e) {
//     if (e.GetId() == CAPTURE_START) {
//         img_bitmap->SetShowType(SHOW_TYPE_IMAGE);
//     } else if (e.GetId() == CAPTURE_END) {
//         imgData = e.GetImageData();

//         button_panel->Hide();
//         button_panel_hough->Show();
//         GetSizer()->Layout();
//     }
// }

// void CameraPanel2::OnHough(HoughEvent &e) {
//     if (e.GetId() == HOUGH_END) {
//         imgData->at(currentImageIndex).SetHough(*e.GetHoughData());
//         img_bitmap->SetImageData(imgData->at(currentImageIndex));
//     }
// }

// void CameraPanel2::OnLeftDown(wxMouseEvent &e) {
//     wxPoint mousePos = e.GetPosition();
//     cv::Point2f p = img_bitmap->calcMousePos(mousePos);
//     selectedPoint.push_back(p);
//     img_bitmap->SetSelectedPoint(selectedPoint);
//     img_bitmap->SetShowSelectedLine(true);
//     searchLine(p);

//     if (selectedLine.size() == 2 && processThread == nullptr) {
//         button_panel_result->Show();
//         button_panel_hough->Hide();
//         GetSizer()->Layout();

//         AppConfig *config = new AppConfig();
//         SensorConfig sensorConfig = config->GetSensorConfig();

//         deleteThread(speedThread);
//         speedThread = new SpeedThread(button_panel_result,
//         &threadPool, imgData,
//                                       selectedLine, sensorConfig);
//         speedThread->Run();

//         deleteThread(resultThread);
//         resultThread = new ResultThread(button_panel_result,
//         imgData); resultThread->Run();

//         img_bitmap->SetShowType(SHOW_TYPE_IMAGE);
//         img_bitmap->SetIsRect(button_panel_result->GetBBoxState());
//         img_bitmap->SetIsOFPoint(button_panel_result->GetOFPntState());
//         img_bitmap->SetIsBotLine(button_panel_result->GetBotLState());
//         img_bitmap->SetShowSelectedLine(button_panel_result->GetSelLState());

//         delete config;
//         config = nullptr;
//     }
// }

// void CameraPanel2::OnSpeed(SpeedCalcEvent &e) {
//     if (e.GetId() == CALC_OK) {
//         img_bitmap->SetSpeed(e.GetSpeed());
//     }
// }

// void CameraPanel2::searchLine(cv::Point2f realMousePos) {
//     if (imgData == nullptr || imgData->empty()) {
//         return;
//     }

//     std::vector<Detection::Line> detLines;
//     std::vector<Detection::Line> linesP =
//         imgData->at(currentImageIndex).hough.lines;

//     if (linesP.empty()) {
//         return;
//     }

//     for (auto line : linesP) {
//         if (line.isIntersect(realMousePos, circleRadius)) {
//             detLines.push_back(line);
//         }
//     }

//     if (detLines.size() == 0) {
//         return;
//     }

//     Detection::Line avgLine = Detection::Line::Average(detLines);
//     addLine(avgLine.Extrapolate(imgData->at(currentImageIndex).image));
// }

// void CameraPanel2::deleteThread(wxThread *thread) {
//     /**
//      * Error assigning pointer to nullptr
//      * need to pass reference instead of pointer
//      *
//      */
//     if (thread != nullptr) {
//         thread->Delete();
//         delete thread;
//         thread = nullptr;
//     }
// }

// void CameraPanel2::waitThenDeleteThread(wxThread *thread) {
//     if (thread != nullptr) {
//         thread->Wait();
//         delete thread;
//         thread = nullptr;
//     }
// }

// void CameraPanel2::addLine(Detection::Line line) {
//     if (selectedLine.size() <= 1) {
//         selectedLine.push_back(line);
//     } else {
//         selectedLine[1] = line;
//     }
//     img_bitmap->SetSelectedLine(selectedLine);
// }
void CameraPanel2::OnCaptureEvent(wxCommandEvent& e) {
    if (e.GetId() == CAPTURE_END) {
        model->endPoint(button_panel->Load_Button,
                        ModelEnum::MODEL_END_LOADCAPTURE);
    }
    e.Skip();
}

void CameraPanel2::OnError(ErrorEvent& e) {
    std::string msg = e.GetErrorData();
    wxMessageBox(msg, "Error", wxOK | wxICON_ERROR);
    Close();
}

// clang-format off
wxBEGIN_EVENT_TABLE(CameraPanel2, wxPanel)
    //     EVT_SPEED(wxID_ANY, CameraPanel2::OnSpeed)
    //     EVT_HOUGH(wxID_ANY, CameraPanel2::OnHough)
    EVT_UPDATEIMAGE(wxID_ANY, CameraPanel2::OnUpdateImage)
    //     EVT_CAPTUREIMAGE(wxID_ANY, CameraPanel2::OnCaptureImage)
    //     EVT_COMMAND(wxID_ANY, c_PROCESS_IMAGE_EVENT
    //     ,CameraPanel2::OnProcessImage) 
    EVT_BUTTON(wxID_ANY,CameraPanel2::OnButton) 
    EVT_COMMAND(wxID_ANY, c_CAPTURE_IMAGE_EVENT, CameraPanel2::OnCaptureEvent)
    EVT_ERROR(wxID_ANY, CameraPanel2::OnError)
    // EVT_LEFT_DOWN(CameraPanel2::OnLeftDown)
wxEND_EVENT_TABLE()
