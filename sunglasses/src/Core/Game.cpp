// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Core/Game.h>

#include <sunglasses/Services.hpp>

#include <sunglasses/Core/Scene.h>

namespace sunglasses {

Game::Game(int argc, char **argv, std::string title) {

}

void Game::run() {
    while (!endGame) {
        // Draw the window
        //window.draw();


        //updateServices();
        //services.get<WindowManager>()->calculateDelta();

        // Run the loop function (user defined logic goes here)
        loop();

        //scene->cycle();
    }
}

//void Game::updateServices() {
    /*for (auto &iterator : services.getServices()) {
        iterator.second->update();
    }*/
//}

void Game::stop() {
    endGame = true;
}

/*void Game::init(int argc, char **argv, std::string title, glm::vec4 color) {
    // Parse the command line options
    int width;
    int height;
    bool showCursor;
    CLValueOption<int> widthOpt("", "width", "The width of the window", "an integer value", 800, false, &width);
    CLValueOption<int> heightOpt("", "height", "The height of the window", "an integer value", 600, false, &height);
    CLSwitchOption cursorOpt("c", "cursor", "Show the cursor", false, &showCursor);
    std::vector<CLOption *> options = {
        &widthOpt,
        &heightOpt,
        &cursorOpt
    };
    
    parseOptions(options, "HELP MESSAGE", "alpha v0.0.1",  argc, argv);

    // Initialize the Audio Device Manager
    AudioDeviceManager *audioManager = new AudioDeviceManager();
    services.add(audioManager);

    // Initialize the Window Manager
    WindowManager *windowManager = new WindowManager(glm::vec2(width, height), title, color);
    windowManager->setName("window_manager");
    services.add(windowManager);
    window = windowManager->getWindow();

    // Initialize the Keyboard Manager
    KeyboardManager *keyboard = new KeyboardManager(window);
    keyboard->setName("keyboard_manager");
    services.add(keyboard);

    // Initialize the Cursor Manager
    CursorManager *cursor = new CursorManager(window, !showCursor);
    cursor->setName("cursor_manager");
    services.add(cursor);

    // Initialize the Mouse Button Manager
    MouseButtonManager *mouseButton = new MouseButtonManager(window);
    mouseButton->setName("mouse_button_manager");
    services.add(mouseButton);

    // Initialize the Logger
    Logger *logger = new Logger();
    logger->setName("logger");
    services.add(logger);

    // Initialize the Global Logic Environment
    GlobalScriptingEnvironment *globalEnvironment = new GlobalScriptingEnvironment();
    globalEnvironment->setName("global_logic_environment");
    services.add(globalEnvironment);

    // Initialize the Resource Management Service
    ResourceService *resourceService = new ResourceService();
    resourceService->setName("resource_service");
    services.add(resourceService);

    resourceService->addResourceManager("models", new ResourceManager());
    resourceService->addResourceManager("meshes", new ResourceManager());
    resourceService->addResourceManager("materials", new ResourceManager());
    resourceService->addResourceManager("textures", new ResourceManager());
    resourceService->addResourceManager("sounds", new ResourceManager());
}*/

} // namespace
