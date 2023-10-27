\tableofcontents{HTML:2}

# Introduction

This section will guide you through the process of developing the application. It is assumed that you have already set up the development environment. If not, please refer to the previous section. This section will cover the following topics:

- **Adding a new Panel** - This section will guide you through the process of adding a new panel to the application.
- **Custom Event** - This section will guide you through the process of defining, triggering, and handling custom events.
- **Defining Process Threads** - This section will guide you through the process of defining process threads.
- **Creating Tasks** - This section will guide you through the process of creating tasks for ThreadPool.


# Add new Panel

This chapter will provide description on how to add new panel to the application. To add a new Panel to the Application, following steps are required:
- Define a new PanelID Enum
- Create a mew Controller class
- Create a new Panel class
- Define object in MainFrame


## Define a new PanelID Enum

The first step is to register a unique enum for the Panel. This enum will be used to identify the Panel in the application. To add a new Panel enum, modify the PanelID enum in the include/Model/Enum.hpp file. Following example will provide a simple example of a PanelID enum:

```cpp
enum PanelID {
    // ... other enum
    PANEL_INFO,
    PANEL_MY_PANEL, // Add new PanelID enum here
};
```

## Create a new Controller class

### Define a new Controller class
To create a new controller class, you first need to decide either the Panel will require a touch input or not. If touch input is required you can create a custom controller class that extends the BaseControllerWithTouch class. Otherwise you can create a custom controller class that extends the BaseController class. Following example will provide a simple example of a Controller class that extends the BaseControllerWithTouch class:

```cpp
class MyController : public BaseControllerWithTouch {
  public:
    MyController(ResourcePtr shared);
    ~MyController();

  private:
    static const PanelID currentPanelID = PanelID::    PANEL_MY_PANEL, // Add new PanelID enum here
;

  private:
    void throwIfAnyThreadIsRunning() override;

    void killAllThreads(wxEvtHandler *parent) override;

   void leftDownHandler(wxEvtHandler *parent, cv::Point point) override;
    void leftMoveHandler(wxEvtHandler *parent, cv::Point point) override;
    void leftUpHandler(wxEvtHandler *parent, cv::Point point) override;
};
```

Make sure that you implemented the pure virtual functions from the BaseControllerWithTouch class. The pure virtual functions are:
- void throwIfAnyThreadIsRunning() override;
- void killAllThreads(wxEvtHandler *parent) override;
- void leftDownHandler(wxEvtHandler *parent, cv::Point point) override;
- void leftMoveHandler(wxEvtHandler *parent, cv::Point point) override;
- void leftUpHandler(wxEvtHandler *parent, cv::Point point) override;

See the source code for LaneCalibrationController for example. 

To make the code more readable, it is adviced to define the controller shared pointer to a shorter name. Following example will provide a simple example of defining a shorter name for the Controller shared pointer:

```cpp
#define MCPtr std::shared_ptr<MyController>
```

### Add method to ControllerFactory

The ControllerFactory is used to connect the Controller with the Model component. Following example can be used:

```cpp
class ControllerFactory {
  public:
    ControllerFactory(wxWindow *parent);
    ~ControllerFactory();

    ResourcePtr getSharedModel();

    // ... other methods
    MyPtr createMyController();

  private:
    ResourcePtr shared;
};
```

```cpp
MyPtr ControllerFactory::createMyController() {
    return std::make_shared<MyController>(shared);
}
```


## Create a new Panel class

### Define a new Panel class

To create a new Panel class, you need to create a new class that extends either the BasePanel or the BasePanelWithTouch class. The BasePanel class has already implemented the basic functionality of a Panel, while the BasePanelWithTouch class has already implemented the basic functionality of a Panel with touch support. The BasePanelWithTouch class is recommended to be used if the Panel will be used in a touch screen device. Alternatively you can also create a whole new class that extends the wxPanel class from wxWidgets. Following example will provide a simple example of a Panel class that extends the BasePanelWithTouch class:

```cpp
class MyPanel : public BasePanelWithTouch {
  public:
    MyPanel(wxWindow *parent, wxWindowID id, MyPtr controller);
    ~MyPanel();

  private:
    const PanelID panel_id = PANEL_MY_PANEL;

    MyPtr controller;

    DECLARE_EVENT_TABLE()
};
```

Make sure that if you are using the BasePanelWithTouch class, you are also using the BaseControllerWithTouch class. Otherwise you will get a compilation error. 

### Create ButtonPanel
Now create a ButtonPanel for the Panel. The ButtonPanel is a panel that contains buttons to perform certain actions. To create a ButtonPanel, you need to create a new class that extends the BaseButtonPanel class. Following example will provide a simple example of a ButtonPanel class that extends the BaseButtonPanel class:

```cpp
class CustomButtonPanel : public BaseButtonPanel {
  public:
    CustomButtonPanel(wxWindow *parent, wxWindowID id);

    void update(const AppState &state) override;

    // define all buttons here

    DECLARE_EVENT_TABLE();
};
```
Make sure that the update() method is implemented. The update() method will be called by the Panel to update the state of the buttons.

### Implement the Panel class

Now that you have created the ButtonPanel, you can now implement the Panel class. Following example can be used as a reference to implement the Panel class:

```cpp
MyPanel::MyPanel(wxWindow *parent, wxWindowID id,
                                           MyPtr controller)
    : BasePanelWithTouch(parent, id, controller), controller(controller) {

    button_panel =
        new CustomButtonPanel(this, wxID_ANY);
    title_panel = new TitlePanel(this, panel_id);

    size();
}
```

make sure the size() method is called at the end of the constructor. The size() method will set the the sizer of the Panel.

### Add method to PanelFactory

In this step, you need to modify the PanelFactory class. Following example can be used:

```cpp
    wxPanel *createPanel(wxWindow *parent, PanelID panelID) {
        // ... other if case

        if (panelID == PANEL_MY_PANEL) {
            return createMyPanel(parent);
        }
    }


    MyPanel *createMyPanel(wxWindow *parent) {
        return new MyPanel(parent, wxID_ANY, controllerFactory->createMyController());
    }
```

## Define object in MainFrame

The last step is to define the Panel in the MainFrame class. Following example can be used:

```cpp

class MainFrame : public wxFrame {
    // ... other methods

    private:
    // ... other methods
    MyPanel *myPanel;
    // ... other methods
}
```

```cpp
MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, Data::AppName) {

    // ... other methods

    // ... other registerPanel
    registerPanel(PANEL_MY_PANEL);

    showFirstPanel();
}
```

Now you have successfully added a new Panel to the application.

# Custom Event

Events are used as a response mechanism for the View component. There are two types of events in this application:
- DataEvent
- EmptyEvent

## DataEvent

DataEvent is an event that contains data. The data can be any type of data. To create a new DataEvent, you need to create a new class that extends the wxCommandEvent class. Following example will provide a simple example of a DataEvent class:

```cpp
class CustomEvent;
wxDECLARE_EVENT(c_CUSTOM_EVENT, CustomEvent);

enum CUSTOM_EVENT_TYPE {
    CUSTOM_EVENT_TYPE_1 = 1,
    CUSTOM_EVENT_TYPE_2,
    CUSTOM_EVENT_TYPE_3,
};

class CustomEvent : public wxCommandEvent {
  public:
    CustomEvent(wxEventType type, int id = 1);

    CustomEvent(const CustomEvent &event);
    virtual wxEvent *Clone() const override;

    // Define set and get method for the data here
    void setData(const std::string &data);
    std::string getData() const;

  private:
    std::string data;
};

// this part is important
typedef void (wxEvtHandler::*CustomFunction)(CustomEvent &);
#define CustomHandler(func)                                             \
    wxEVENT_HANDLER_CAST(CustomFunction, func)
#define EVT_CUSTOM(id, func)                                           \
    wx__DECLARE_EVT1(c_CUSTOM_EVENT, id, CustomHandler(func))
```
```cpp
wxDEFINE_EVENT(c_CUSTOM_EVENT, CustomEvent);

CustomEvent::CustomEvent(wxEventType type, int id)
    : wxCommandEvent(type, id) {
}

CustomEvent::CustomEvent(const CustomEvent &event)
    : wxCommandEvent(event) {
    this->setData(event.getData());
}

wxEvent *UpdatePreviewEvent::Clone() const {
    return new CustomEvent(*this);
}

void CustomEvent::setData(const std::string &data) {
    this->data = data;
}

std::string CustomEvent::getData() const {
    return data;
}
```

Following class can be refer as example:
-   UpdatePreviewEvent
-   UpdateStateEvent
-   ErrorEvent

## EmptyEvent

EmptyEvent is an event that does not contain any data. It is normally used to signal the View component to perform certain action. To create a new EmptyEvent, you need to create a new class that extends the wxCommandEvent class. Following example will provide a simple example of a EmptyEvent class:

```cpp
wxDECLARE_EVENT(c_CUSTOM_EVENT, wxCommandEvent);

enum CUSTOM_EVENT_TYPE {
    CUSTOM_EVENT_TYPE_1 = 1,
    CUSTOM_EVENT_TYPE_2,
    CUSTOM_EVENT_TYPE_3,
};
```

```cpp
wxDEFINE_EVENT(c_CUSTOM_EVENT, wxCommandEvent);
```

## Bind Event

To bind an event to a method, you need to use the following syntax in the Panel class:

```cpp
BEGIN_EVENT_TABLE(BasePanel, wxPanel)
    // ... other event

    // For EmptyEvent
    EVT_COMMAND(wxID_ANY, c_CUSTOM_EVENT, BasePanel::OnCustomEvent)

    // For DataEvent
    EVT_CUSTOM(c_CUSTOM_EVENT, BasePanel::OnCustomEvent)
END_EVENT_TABLE()
```
Make sure the function to handle the event is implemented.

## Submit Event

To submit an event, you need to use the following syntax:

```cpp

// For EmptyEvent
wxCommandEvent event(c_CUSTOM_EVENT, CUSTOM_EVENT_TYPE_1);
wxPostEvent(this, event);

// For DataEvent
CustomEvent event(c_CUSTOM_EVENT, CUSTOM_EVENT_TYPE_1);
event.setData("data");
wxPostEvent(this, event);
```

# Thread

Thread is used to perform a long running task.

## Define unique ThreadID

To define a unique ThreadID, you need to modify the ThreadID enum in the include/Thread/Thread_ID.hpp file. Following example will provide a simple example of a ThreadID enum:

```cpp
enum ThreadID {
    // ... other enum
    THREAD_MY_THREAD, // Add new ThreadID enum here
};
```

## Create a new Thread class
Now you need to create a new class that extends the BaseThread class. Following example will provide a simple example of a Thread class:

```cpp
class CustomThread : public BaseThread {
  public:
    CustomThread(wxEvtHandler *parent, DataPtr data);
    ~CustomThread();

    ThreadID getID() const override;

  protected:
    virtual ExitCode Entry() override;


  private:
    // ... other methods
    const ThreadID thread_id = ThreadID::THREAD_MY_THREAD; // Add new ThreadID enum here
};
```

```cpp
CustomThread::CustomThread(wxEvtHandler *parent, DataPtr data)
    : BaseThread(parent, data) {
}

CustomThread::~CustomThread() {
}

ThreadID CustomThread::getID() const {
    return thread_id;
}

wxThread::ExitCode CustomThread::Entry() {
    // ... other code, do process
    return (wxThread::ExitCode)0;
}
```

Additionally following classes can be inherited to add more functionality:

<!-- table -->

| Class | Description |
| --- | --- |
| PreviewableThread | Enable the thread to send image to ImagePanel |
| ImageSizeDataThread | Add variable imageSize, which is the size of the captured image |
| ImageDataThread | Add variable image, which is the camera|
| CameraAccessor | Enable camera access |


## Add method to ThreadController

In this step, you need to modify the ThreadController class. Following example can be used:

```cpp
class ThreadController {
  public:
    ThreadController(wxEvtHandler *parent, DataPtr data);
    ~ThreadController();

    // ... other methods

    virtual void startCustomThread(wxEvtHandler *parent, PanelID panelID);

    void endCustomThread();

    CustomThread *getCustomThread();

  private:

    // ... other variables 
    CustomThread *custom_thread;
};
```

# Task for ThreadPool

ThreadPool enables parallel processing, which can be used to speed up the application. To add a new Task to the ThreadPool, following steps are required:

## Define unique TaskType

To define a unique TaskType, you need to modify the TaskType enum in the include/Thread/Task/Task.hpp file. Following example will provide a simple example of a TaskType enum:

```cpp
enum TaskType {
    // ... other enum
    TASK_MY_TASK, // Add new TaskType enum here
};
```

## Create a new Task class

Now you need to create a new class that extends the Task class. Following example will provide a simple example of a Task class:

```cpp
class CustomTask : public Task {
  public:
    CustomTask(wxEvtHandler *parent, DataPtr data);
    void Execute() override;

  private:
    // ... other methods
    const std::string currentName = "CustomTask";
    const TaskType currentType = TaskType::TASK_MY_TASK; // Add new TaskType enum here
};
```

```cpp
CustomTask::CustomTask(wxEvtHandler *parent, DataPtr data)
    : Task(parent, data) {
    property = TaskProperty(currentType);
    name = currentName;
}

void CustomTask::Execute() {
    // ... other code, do process
}
```

