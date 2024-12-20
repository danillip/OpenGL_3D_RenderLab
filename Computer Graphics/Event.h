// Event.h
#pragma once

#include <string>

// ���� �������
enum class EventType
{
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

// ������� ����� ��� ���� �������
class Event
{
public:
    virtual ~Event() = default;

    virtual EventType eventType() const = 0;
    virtual std::string toString() const = 0;
};
