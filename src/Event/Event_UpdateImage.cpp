/**
 * @file Event_UpdateImage.cpp
 * @author Haziq Sabtu (mhaziq.sabtu@gmail.com)
 * @brief Custom Event for Update Image
 * @version 1.0.0
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <Event/Event_UpdateImage.hpp>

wxDEFINE_EVENT(c_UPDATE_IMAGE_EVENT, UpdateImageEvent);

/**
 * @brief Construct a new Update Image Event:: Update Image Event object
 *
 * @param eventType type of event to be created. Default to c_UPDATE_IMAGE_EVENT
 * @param id id of the event. See UPDATE_IMAGE_TYPE for more info
 */
UpdateImageEvent::UpdateImageEvent(wxEventType eventType, int id)
    : wxCommandEvent(eventType, id) {}

/**
 * @brief Construct a new Update Image Event:: Update Image Event object
 * @details Overloaded constructor for copying event
 * This is required for data to be transported
 * @see <a
 * href="https://wiki.wxwidgets.org/Custom_Events">wxWidgets Event
 * Handling</a>
 * @param e 
 */
UpdateImageEvent::UpdateImageEvent(const UpdateImageEvent &e)
    : wxCommandEvent(e) {
    this->SetImageData(e.GetImageData());
}

/**
 * @brief Clone the event
 * @details Required for sending event with wxPostEvent()
 * @see <a
 * href="https://wiki.wxwidgets.org/Custom_Events">wxWidgets Event
 * Handling</a>
 * 
 * @return wxEvent* 
 */
wxEvent *UpdateImageEvent::Clone() const { return new UpdateImageEvent(*this); }

/**
 * @brief Set the Image Data object to be transported
 * 
 * @param imgData 
 */
void UpdateImageEvent::SetImageData(const ImageData &imgData) {
    this->imgData = imgData;
}

/**
 * @brief Get the Image Data object
 * 
 * @return ImageData 
 */
ImageData UpdateImageEvent::GetImageData() const { return imgData; }
