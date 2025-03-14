#include "scene/Scene.hpp"

int main() {

    try {
        Scene app;
    } catch (const std::exception& e) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}