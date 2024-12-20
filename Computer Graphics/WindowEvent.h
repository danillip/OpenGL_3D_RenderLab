// WindowEvent.h
#pragma once

#include "Event.h"

class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() = default;

    EventType eventType() const override { return EventType::WindowClose; }

    std::string toString() const override
    {
        return "WindowCloseEvent";
    }
};

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(int width, int height) : m_Width(width), m_Height(height) {}

    int getWidth() const { return m_Width; } // Добавлено
    int getHeight() const { return m_Height; } // Добавлено
    EventType eventType() const override { return EventType::WindowResize; }
    std::string toString() const override { return "WindowResizeEvent: " + std::to_string(m_Width) + ", " + std::to_string(m_Height); }

private:
    int m_Width, m_Height;
};