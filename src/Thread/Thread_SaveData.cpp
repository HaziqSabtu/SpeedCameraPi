
#include "Event/Event_LoadImage.hpp"
#include "Event/Event_SaveData.hpp"
#include "Event/Event_UpdateStatus.hpp"
#include "Model/SessionData.hpp"
#include "UI/Dialog/SaveDataDialog.hpp"
#include "Utils/FileReader/fileWR.hpp"
#include <Thread/Thread_SaveData.hpp>
#include <wx/utils.h>

/**
 * @brief Construct a new Load File Thread:: Load File Thread object
 *
 * @param parent parent wxEvtHandler
 * @param threadPool pointer to ThreadPool
 * @param imgData pointer to ImageData vector
 * @param path path to file
 * @param maxFrame maximum number of frame to load
 */
SaveDataThread::SaveDataThread(wxEvtHandler *parent, DataPtr data)
    : wxThread(wxTHREAD_JOINABLE), parent(parent), data(data) {}

/**
 * @brief Destroy the Load File Thread:: Load File Thread object
 *
 */
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