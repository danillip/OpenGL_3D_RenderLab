// KeyEvent.h
#pragma once

#include "Event.h"
#include "KeyCode.h" // Предполагается, что KeyCode определён отдельно

class KeyEvent : public Event
{
public:
    KeyCode getKeyCode() const { return m_KeyCode; }

protected:
    KeyEvent(const KeyCode keycode) : m_KeyCode(keycode) {}

    KeyCode m_KeyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
        : KeyEvent(keycode), m_IsRepeat(isRepeat) {}

    bool isRepeat() const { return m_IsRepeat; }

    EventType eventType() const override { return EventType::KeyPressed; }

    std::string toString() const override
    {
        return "KeyPressedEvent: " + std::to_string(static_cast<int>(m_KeyCode)) + " (repeat = " + std::to_string(m_IsRepeat) + ")";
    }

private:
    bool m_IsRepeat;
};

class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

    EventType eventType() const override { return EventType::KeyReleased; }

    std::string toString() const override
    {
        return "KeyReleasedEvent: " + std::to_string(static_cast<int>(m_KeyCode));
    }
};

class KeyTypedEvent : public KeyEvent
{
public:
    KeyTypedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

    EventType eventType() const override { return EventType::KeyTyped; }

    std::string toString() const override
    {
        return "KeyTypedEvent: " + std::to_string(static_cast<int>(m_KeyCode));
    }
};