#include "MainMenu.h"

MainMenu::MainMenu(GUI::GUIModule &_system, graphics::Texture::LibraryT &textures) :
    GUI::Controller<GUI::Drawable::Image>(_system, GUI::Drawable::Image(textures["stone"], glm::ivec2(128))),
    optionsMenu(system)
{
    panel.addChild(play);
    panel.addChild(options);
    panel.addChild(quit);

    connect(play.signal_deselected, slot_playPressed);
    connect(options.signal_deselected, slot_optionsPressed);
    //connect(quit.signal_deselected, );
}

void MainMenu::playPressed() {

}

void MainMenu::optionsPressed() {
    navigationController->push(optionsMenu);
}

void MainMenu::quitPressed() {

}
