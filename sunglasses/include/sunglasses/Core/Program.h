#ifndef PROGRAM_H
#define PROGRAM_H

#include <sunglasses/Graphics/Window.h>
#include <sunglasses/GUI/System.h>

#include <set>
#include <functional>
#include <initializer_list>
#include <glm/glm.hpp>

namespace sunglasses {

/// A module of the program
class Module {
public:
    /// Updates the module (called once every program loop)
    virtual void update() = 0;
    
    /// Code that 'runs' the module (called once every program loop)
    virtual void run() = 0;
};

/// A class that sets up all the necessary components for a program (not a game)
/**
 * This class should be subclassed to make a specialized program. It should also
 * be instantiated by the main() function.
 */
class Program {
public:
    /// Constructs the program
    Program(glm::ivec2 windowSize, std::string windowTitle, std::initializer_list<Module *> _modules);

    /// Starts the program and should call run()
    virtual void start() = 0;

    /// This method runs the game loop indefinitely
    void run();

    /// Stops at the beginning of the next loop
    void stop();


    /// The slot for stopping the loop
    Slot<void(Program::*)(), &Program::stop> slot_stop = Slot<void(Program::*)(), &Program::stop>(*this);
protected:
    /// The code to be executed every game loop
    virtual void loop();

    /// The window of the program
    graphics::Window window;

    /// The GUI System
    GUI::System GUI;

    /// The set of modules in the program
    std::set<Module *> modules;
private:
    /// The loop should stop if this is on
    bool shouldStop = false;
};

}

#endif
