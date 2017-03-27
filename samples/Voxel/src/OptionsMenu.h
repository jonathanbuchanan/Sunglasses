#ifndef VOXEL_OPTIONSMENU_H
#define VOXEL_OPTIONSMENU_H

#include <sunglasses/Sunglasses.hpp>

using namespace sunglasses;

class OptionsMenu : public GUI::Controller<GUI::Drawable::Color> {
public:
    OptionsMenu(graphics::Window &window);
private:
    void donePressed();

    GUI::BasicButton done = GUI::BasicButton(glm::ivec2(740, 700), glm::ivec2(440, 50), glm::vec4(1.0f), glm::vec4(0.5f), glm::vec4(0.0f));

    Slot<void(OptionsMenu::*)(), &OptionsMenu::donePressed> slot_donePressed = Slot<void(OptionsMenu::*)(), &OptionsMenu::donePressed>(*this);
};

#endif
