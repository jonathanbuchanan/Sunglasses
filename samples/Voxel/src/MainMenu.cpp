#include "MainMenu.h"

MainMenu::MainMenu(GUI::System &system) : tex("./res/Graphics/Textures/stone.png", graphics::Texture::Format::RGBA, graphics::TextureMinification::Linear, graphics::TextureMagnification::Nearest),
    GUI::Controller<GUI::Drawable::Image>(system, GUI::Drawable::Image(tex, glm::ivec2(128)))
{

}
