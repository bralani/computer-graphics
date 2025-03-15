#include "scene/TestScene.hpp"

int main() {

    try {
        TestScene app;
        app.run();
    } catch (const std::exception& e) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}