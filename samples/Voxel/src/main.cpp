// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Sunglasses.hpp>

using namespace sunglasses;

#include "MainMenu.h"
#include "OptionsMenu.h"

class VoxelProgram : public Program {
public:
    VoxelProgram(graphics::GraphicsModule &graphics) :
            Program({&graphics}) {
                
    }
    
    virtual void start() {
        //connect(window.signal_close, slot_stop);

        /*graphics::Texture::LibraryT textures({
            {"stone", graphics::Texture::LibraryT::ResourceHandle(graphics::Texture::Parameter(
                "./res/Graphics/Textures/stone.png", graphics::Texture::Format::RGBA, graphics::TextureMinification::Nearest, graphics::TextureMagnification::Nearest))}
        });

        MainMenu main(GUI, textures);

        GUI::NavigationController nav(GUI);
        nav.push(main);*/

        run();
    }
};

int main(int argc, char **argv) {
    graphics::GraphicsModule graphics = graphics::GraphicsModule(glm::ivec2(1920, 1080), "Voxel", {});
    
    graphics::Texture::LibraryT textures({
            {"stone", graphics::Texture::LibraryT::ResourceHandle(graphics::Texture::Parameter(
                "./res/Graphics/Textures/stone.png", graphics::Texture::Format::RGBA, graphics::TextureMinification::Nearest, graphics::TextureMagnification::Nearest))}
    });
    
    GUI::GUIModule gui = GUI::GUIModule(graphics);
    
    MainMenu menu(gui, textures);
    
    GUI::Controller *x = &menu;
    GUI::NavigationController nav(gui);
    nav.push(&menu);
    
    
    VoxelProgram program = VoxelProgram(graphics);
    program.start();
    return 0;
}
