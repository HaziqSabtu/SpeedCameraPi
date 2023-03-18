/**
 * @file Event_CaptureImage.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom Event for Capture Image
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <Event/Event_CaptureImage.hpp>

wxDEFINE_EVENT(c_CAPTURE_IMAGE_EVENT, CaptureImageEvent);

/**
 * @brief Construct a new Capture Image Event:: Capture Image Event object
 *
 * @param eventType type of event to be created. Default to
 * c_CAPTURE_IMAGE_EVENT
 * @param id id of the event. See CAPTURE_IMAGE_TYPE for more info
 */
CaptureImageEvent::CaptureImageEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

/**
 * @brief Construct a new Capture Image Event:: Capture Image Event object
 * @details Overloaded constructor for copying event
 * This is required for data to be transported
 * @see <a
 * href="https://wiki.wxwidgets.org/Custom_Events">wxWidgets
 * Event Handling</a>
 * @param e
 */
CaptureImageEvent::CaptureImageEvent(const CaptureImageEvent &e)
    : wxCommandEvent(e) {
    this->SetImageData(e.GetImageData());
}

/**
 * @brief Clone the event
 * @details Required for sending event with wxPostEvent()
 * @see <a
 * href="https://wiki.wxwidgets.org/Custom_Events">wxWidgets
 * Event Handling</a>
 * @return wxEvent*
 */
wxEvent *CaptureImageEvent::Clone() const {
    return new CaptureImageEvent(*this);
}

/**
 * @brief Set the Image Data object to be transported
 *
 * @param imgData the data
 */
void CaptureImageEvent::SetImageData(std::vector<ImageData> *imgData) {
    this->imgData = imgData;
}

/**
 * @brief Get the Image Data object
 *
 * @return std::vector<ImageData>*
 */
std::vector<ImageData> *CaptureImageEvent::GetImageData() const {
    return imgData;
}
