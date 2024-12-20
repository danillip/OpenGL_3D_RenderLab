#pragma once

#include <GLFW/glfw3.h>
#include <functional>
#include <string>
#include "MouseEvent.h"
#include "WindowEvent.h"
#include "KeyEvent.h"
#include "Event.h" // Подключение базового класса событий

class GLFWWindowImpl
{
public:
    using EventCallbackFn = std::function<void(Event&)>;

    struct WindowData
    {
        WindowData(const std::string& windowName, int windowWidth, int windowHeight)
            : name(windowName), width(windowWidth), height(windowHeight) {}

        std::string name;
        int width;
        int height;
    };

public:
    GLFWWindowImpl() = delete;
    GLFWWindowImpl(const WindowData& windowData);
    virtual ~GLFWWindowImpl();

    void update();
    int width() const;
    int height() const;
    void setEventCallback(const EventCallbackFn& eventCallbackFn);
    void setVSync(bool isEnabled);
    bool isVSync() const;
    void* nativeWindow() const { return m_window; }

private:
    GLFWwindow* m_window = nullptr;
    bool m_isVSyncEnabled = false;

    struct WindowEvent
    {
        int width = 0;
        int height = 0;
        EventCallbackFn eventCallbackFn;
    } m_eventCallback;

    void shutDown();
};

// Реализация методов
GLFWWindowImpl::GLFWWindowImpl(const WindowData& windowData)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_eventCallback.width = windowData.width;
    m_eventCallback.height = windowData.height;

    m_window = glfwCreateWindow(windowData.width, windowData.height, windowData.name.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        glfwTerminate();
        return;
    }

    glfwSetWindowUserPointer(m_window, &m_eventCallback);
    glfwMakeContextCurrent(m_window);
    setVSync(true);

    // Установка callback-функций GLFW
    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
        {
            auto& eventCallback = *static_cast<WindowEvent*>(glfwGetWindowUserPointer(window));
            WindowCloseEvent event;
            eventCallback.eventCallbackFn(event);
        });

    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
        {
            auto& eventCallback = *static_cast<WindowEvent*>(glfwGetWindowUserPointer(window));
            eventCallback.width = width;
            eventCallback.height = height;
            WindowResizeEvent event(width, height);
            eventCallback.eventCallbackFn(event);
        });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
        {
            auto& eventCallback = *static_cast<WindowEvent*>(glfwGetWindowUserPointer(window));
            MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
            eventCallback.eventCallbackFn(event);
        });

    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            auto& eventCallback = *static_cast<WindowEvent*>(glfwGetWindowUserPointer(window));
            MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
            eventCallback.eventCallbackFn(event);
        });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
        {
            auto& eventCallback = *static_cast<WindowEvent*>(glfwGetWindowUserPointer(window));
            switch (action)
            {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event(static_cast<MouseCode>(button));
                eventCallback.eventCallbackFn(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
                eventCallback.eventCallbackFn(event);
                break;
            }
            }
        });

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            auto& eventCallback = *static_cast<WindowEvent*>(glfwGetWindowUserPointer(window));
            switch (action)
            {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(key, false);
                eventCallback.eventCallbackFn(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(key);
                eventCallback.eventCallbackFn(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent event(key, true);
                eventCallback.eventCallbackFn(event);
                break;
            }
            }
        });

    glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode)
        {
            auto& eventCallback = *static_cast<WindowEvent*>(glfwGetWindowUserPointer(window));
            KeyTypedEvent event(keycode);
            eventCallback.eventCallbackFn(event);
        });
}

GLFWWindowImpl::~GLFWWindowImpl()
{
    shutDown();
}

void GLFWWindowImpl::update()
{
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

int GLFWWindowImpl::width() const
{
    return m_eventCallback.width;
}

int GLFWWindowImpl::height() const
{
    return m_eventCallback.height;
}

void GLFWWindowImpl::setEventCallback(const EventCallbackFn& eventCallbackFn)
{
    m_eventCallback.eventCallbackFn = eventCallbackFn;
}

void GLFWWindowImpl::setVSync(bool isEnabled)
{
    m_isVSyncEnabled = isEnabled;
    glfwSwapInterval(isEnabled ? 1 : 0);
}

bool GLFWWindowImpl::isVSync() const
{
    return m_isVSyncEnabled;
}

void GLFWWindowImpl::shutDown()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
