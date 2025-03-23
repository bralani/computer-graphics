#include "utilities/Input.hpp"

GLFWwindow* Input::window = nullptr;

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