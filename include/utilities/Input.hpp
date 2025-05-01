#ifndef INPUT_HPP
#define INPUT_HPP

#include <GLFW/glfw3.h>
#include <utility>
#include "scene/Scene.hpp"

class Input {
public:
    static void setWindow(GLFWwindow* win);

    static bool getKey(int key);

    static std::pair<double, double> getCursorPos();

    static bool getMouseButton(int button);

    static GLFWwindow* getWindow();

    static void initScrollCallback(); 
                
    static double getScrollOffset();  

private:
    static GLFWwindow* window;
};

#endif
