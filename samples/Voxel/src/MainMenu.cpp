#include "MainMenu.h"

MainMenu::MainMenu(graphics::Window &window, graphics::Texture::LibraryT &textures) :
    GUI::Controller<GUI::Drawable::Image>(window, GUI::Drawable::Image(textures["stone"], glm::ivec2(128))),
    optionsMenu(window)
{
    panel.addChild(play);
    panel.addChild(options);
    panel.addChild(quit);

    connect(play.signal_deselected, slot_playPressed);
    connect(options.signal_deselected, slot_optionsPressed);
    connect(quit.signal_deselected, slot_quitPressed);
}

void MainMenu::playPressed() {

}

void MainMenu::optionsPressed() {
    navigationController->push(optionsMenu);
}

void MainMenu::quitPressed() {

}
