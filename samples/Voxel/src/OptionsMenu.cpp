#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(graphics::Window &window) :
    GUI::Controller<GUI::Drawable::Color>(window, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)) {
    panel.addChild(done);

    connect(done.signal_deselected, slot_donePressed);
}

void OptionsMenu::donePressed() {
    navigationController->pop();
}
