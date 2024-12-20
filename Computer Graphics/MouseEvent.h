#pragma once

#include "Event.h"
#include "MouseCode.h"

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

    float getX() const { return m_MouseX; } // Переименовано из x()
    float getY() const { return m_MouseY; } // Переименовано из y()
    EventType eventType() const override { return EventType::MouseMoved; }
    std::string toString() const override { return "MouseMovedEvent: " + std::to_string(m_MouseX) + ", " + std::to_string(m_MouseY); }

private:
    float m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

    float getOffsetX() const { return m_XOffset; } // Изменено название для консистентности
    float getOffsetY() const { return m_YOffset; }
    EventType eventType() const override { return EventType::MouseScrolled; }
    std::string toString() const override { return "MouseScrolledEvent: " + std::to_string(m_XOffset) + ", " + std::to_string(m_YOffset); }

private:
    float m_XOffset, m_YOffset;
};

class MouseButtonEvent : public Event {
public:
    MouseCode getMouseButton() const { return m_Button; }

protected:
    MouseButtonEvent(MouseCode button) : m_Button(button) {}

    MouseCode m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    MouseButtonPressedEvent(MouseCode button) : MouseButtonEvent(button) {}
    EventType eventType() const override { return EventType::MouseButtonPressed; }
    std::string toString() const override { return "MouseButtonPressedEvent: " + std::to_string(static_cast<int>(m_Button)); }
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    MouseButtonReleasedEvent(MouseCode button) : MouseButtonEvent(button) {}
    EventType eventType() const override { return EventType::MouseButtonReleased; }
    std::string toString() const override { return "MouseButtonReleasedEvent: " + std::to_string(static_cast<int>(m_Button)); }
};
