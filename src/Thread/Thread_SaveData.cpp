
#include "Event/Event_LoadImage.hpp"
#include "Event/Event_SaveData.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/SessionData.hpp"
#include "Thread/Thread_Base.hpp"
#include "UI/Dialog/SaveDataDialog.hpp"
#include "Utils/FileReader/fileWR.hpp"
#include <Thread/Thread_SaveData.hpp>
#include <wx/utils.h>

SaveDataThread::SaveDataThread(wxEvtHandler *parent, DataPtr data)
    : BaseThread(parent, data) {}

SaveDataThread::~SaveDataThread() {
    if (parent != nullptr) {
        parent = nullptr;
    }
}

wxThread::ExitCode SaveDataThread::Entry() {
    try {
        wxCommandEvent startSaveDataEvent(c_SAVE_DATA_EVENT, SAVE_DATA_START);
        wxPostEvent(parent, startSaveDataEvent);

        if (data->isCaptureDataEmpty()) {
            throw std::runtime_error("Capture data is empty");
        }

        wxMilliSleep(5000);

        Utils::FileReadWrite().WriteFile(data);

    } catch (const std::exception &e) {
        wxCommandEvent errorSaveDataEvent(c_SAVE_DATA_EVENT, SAVE_DATA_ERROR);
        wxPostEvent(parent, errorSaveDataEvent);

        ErrorEvent::Submit(parent, e.what());
    }

    wxCommandEvent endSaveDataEvent(c_SAVE_DATA_EVENT, SAVE_DATA_END);
    wxPostEvent(parent, endSaveDataEvent);
    return 0;
}

/**
 * @brief Get the Thread Id object
 *
 * @return ThreadID
 */
ThreadID SaveDataThread::getID() const { return id; }