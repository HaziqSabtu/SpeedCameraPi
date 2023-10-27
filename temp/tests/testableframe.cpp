///////////////////////////////////////////////////////////////////////////////
// Name:        testableframe.cpp
// Purpose:     An improved wxFrame for unit-testing
// Author:      Steven Lamerton
// Copyright:   (c) 2010 Steven Lamerton
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
//#include "testprec.h"

#include "testableframe.h"
#include "wx/app.h"
#include <gtest/gtest.h>
#include <iostream>

wxTestableFrame::wxTestableFrame()
    : wxFrame(nullptr, wxID_ANY, wxASCII_STR("Test Frame")) {
    // Use fixed position to facilitate debugging.
    Move(200, 200);

    Show();
}

void wxTestableFrame::OnEvent(wxEvent &evt) {
    m_count[evt.GetEventType()]++;
    std::cerr << "OnEvent: " << evt.GetEventType() << std::endl;
    std::cerr << "Count : " << m_count[evt.GetEventType()] << std::endl;

    if (!evt.IsCommandEvent())
        evt.Skip();
}

int wxTestableFrame::GetEventCount(wxEventType type) {
    std::cerr << "GetEventCount: " << type << std::endl;
    std::cerr << "Count : " << m_count[type] << std::endl;

    return m_count[type];
}

void wxTestableFrame::ClearEventCount(wxEventType type) {
    std::cerr << "ClearEventCount: " << type << std::endl;
    m_count[type] = 0;
}

EventCounter::EventCounter(wxWindow *win, wxEventType type)
    : m_type(type), m_win(win)

{
    m_frame = wxStaticCast(wxTheApp->GetTopWindow(), wxTestableFrame);

    m_win->Connect(m_type, wxEventHandler(wxTestableFrame::OnEvent), nullptr,
                   m_frame);
}

EventCounter::~EventCounter() {
    m_win->Disconnect(m_type, wxEventHandler(wxTestableFrame::OnEvent), nullptr,
                      m_frame);

    //This stops spurious counts from previous tests
    std::cerr << "Clearing event count" << std::endl;
    Clear();

    m_frame = nullptr;
    m_win = nullptr;
}

bool EventCounter::OldWaitEvent(int timeInMs) {
    static const int SINGLE_WAIT_DURATION = 50;

    for (int i = 0; i < timeInMs / SINGLE_WAIT_DURATION; ++i) {
        wxYield();

        const int count = GetCount();
        if (count) {

            // CHECK(count == 1);
            //ASSERT_TRUE(count == 1);
            //
            Clear();
            return true;
        }

        wxMilliSleep(SINGLE_WAIT_DURATION);
    }

    return false;
}

void EventCounter::WaitEvent(int timeInMs, int targetCount) {
    static const int SINGLE_WAIT_DURATION = 50;

    for (int i = 0; i < timeInMs / SINGLE_WAIT_DURATION; ++i) {
        wxYield();

        const int count = GetCount();
        if (count > 0) {
            EXPECT_EQ(count, targetCount);

            // is Clear necessary?
            // Clear();
            return;
        }

        wxMilliSleep(SINGLE_WAIT_DURATION);
    }

    // If the loop completes without an event, it's considered a failure
    FAIL() << "Event not received within the specified time.";
}

void EventCounter::WaitEventNoSkip(int timeInMs, int targetCount) {
    static const int SINGLE_WAIT_DURATION = 50;

    for (int i = 0; i < timeInMs / SINGLE_WAIT_DURATION; ++i) {
        wxYield();

        wxMilliSleep(SINGLE_WAIT_DURATION);
    }

    // If the loop completes without an event, it's considered a failure
    // FAIL() << "Event not received within the specified time.";
}

bool TestApp::OnInit() {
    new wxTestableFrame();
    Connect(wxEVT_IDLE, wxIdleEventHandler(TestApp::OnIdle));

    return true;
}

int TestApp::FilterEvent(wxEvent &event) {
    // Continue processing other events
    return wxApp::FilterEvent(event);
}

int TestApp::OnExit() {
    delete GetTopWindow();
    return wxApp::OnExit();
}

void TestApp::OnIdle(wxIdleEvent &event) { event.Skip(); }