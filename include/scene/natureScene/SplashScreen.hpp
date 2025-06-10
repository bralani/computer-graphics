#ifndef NATURE_SCENE_SPLASH_SCREEN_HPP
#define NATURE_SCENE_SPLASH_SCREEN_HPP

enum class AppState {
    SPLASH_SCREEN,
    INITIALIZE_VULKAN,
    RUNNING_GAME,
    CLEANUP,
    EXIT
};

namespace SplashScreen {
    AppState run();
}

#endif // NATURE_SCENE_SPLASH_SCREEN_HPP