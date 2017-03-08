#ifndef VOXEL_MAINMENU
#define VOXEL_MAINMENU

#include <sunglasses/Sunglasses.hpp>

using namespace sunglasses;

class MainMenu : public GUI::Controller<GUI::Drawable::Image> {
public:
    MainMenu(GUI::System &system);
private:
    graphics::Texture tex;
};

#endif
