
#include <Event/Event.hpp>
#include <Thread/Thread_SaveData.hpp>

/**
 * @brief Construct a new Save Data Thread:: Save Data Thread object
 *
 * @param parent Pointer to the View
 * @param data Pointer to the SessionData
 */
SaveDataThread::SaveDataThread(wxEvtHandler *parent, DataPtr data)
    : BaseThread(parent, data) {}

/**
 * @brief Destroy the Save Data Thread:: Save Data Thread object
 *
 */
SaveDataThread::~SaveDataThread() {
    if (parent != nullptr) {
        parent = nullptr;
    }
}

/**
 * @brief Entry point of the thread
 * @details This function will be called when the thread is started
 * <ul>
 * <li>Post SaveDataStartEvent to parent to signal the start of saving</li>
 * <li>Check if capture data is empty</li>
 * <li>Save the data</li>
 * <li>Post SaveDataErrorEvent to parent if an error occurs</li>
 * <li>Post SaveDataEndEvent to parent to signal the end of saving</li>
 * </ul>
 *
 *
 * @return wxThread::ExitCode
 */
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