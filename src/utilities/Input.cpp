#include "utilities/Input.hpp"

GLFWwindow* Input::window = nullptr;

static double scrollOffset = 0.0;

static void scroll_callback(GLFWwindow* /*w*/, double /*xoffset*/, double yoffset) {
    scrollOffset += yoffset;
}

void Input::setWindow(GLFWwindow* win) {
    window = win;
}

bool Input::getKey(int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

std::pair<double, double> Input::getCursorPos() {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return {xpos, ypos};
}

bool Input::getMouseButton(int button) {
    return glfwGetMouseButton(window, button) == GLFW_PRESS;
}

GLFWwindow* Input::getWindow() {
    return window;
}

void Input::initScrollCallback() {
    glfwSetScrollCallback(window, scroll_callback);
}

double Input::getScrollOffset() {
    double v = scrollOffset;
    scrollOffset = 0.0;
    return v;
}