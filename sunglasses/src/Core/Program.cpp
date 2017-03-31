#include <sunglasses/Core/Program.h>

namespace sunglasses {

Program::Program(std::initializer_list<Module *> _modules) :
        modules(_modules) {

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
