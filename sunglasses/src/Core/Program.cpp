#include <sunglasses/Core/Program.h>

namespace sunglasses {

Program::Program(glm::ivec2 windowSize, std::string windowTitle, std::initializer_list<Module *> _modules) :
        window(windowSize, windowTitle), GUI(window), modules(_modules) {

}

void Program::run() {
    while (!shouldStop) {
        for (Module *module : modules) {
            module->update();
        }
        for (Module *module : modules) {
            module->run();
        }
        loop();
    }
}

void Program::loop() {

}

void Program::stop() {
    shouldStop = true;
}

}
