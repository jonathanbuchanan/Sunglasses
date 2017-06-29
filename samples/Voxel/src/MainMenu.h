#ifndef VOXEL_MAINMENU_H
#define VOXEL_MAINMENU_H

#include <sunglasses/Sunglasses.hpp>

#include "OptionsMenu.h"

using namespace sunglasses;

class MainMenu : public GUI::Controller {
public:
    MainMenu(GUI::GUIModule &_system, graphics::Texture::LibraryT &textures);
private:
    void playPressed();
    void optionsPressed();
    void quitPressed();

    //GUI::BasicButton play = GUI::BasicButton(glm::ivec2(740, 700), glm::ivec2(440, 50), glm::vec4(1.0f), glm::vec4(0.5f), glm::vec4(0.0f));
    //GUI::BasicButton options = GUI::BasicButton(glm::ivec2(740, 860), glm::ivec2(200, 50), glm::vec4(1.0f), glm::vec4(0.5f), glm::vec4(0.0f));
    //GUI::BasicButton quit = GUI::BasicButton(glm::ivec2(980, 860), glm::ivec2(200, 50), glm::vec4(1.0f), glm::vec4(0.5f), glm::vec4(0.0f));

    Slot<void(MainMenu::*)(), &MainMenu::playPressed> slot_playPressed = Slot<void(MainMenu::*)(), &MainMenu::playPressed>(*this);
    Slot<void(MainMenu::*)(), &MainMenu::optionsPressed> slot_optionsPressed = Slot<void(MainMenu::*)(), &MainMenu::optionsPressed>(*this);

    OptionsMenu optionsMenu;
};

#endif
