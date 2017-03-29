// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Sunglasses.hpp>

using namespace sunglasses;

#include "MainMenu.h"
#include "OptionsMenu.h"

class VoxelProgram : public Program {
public:
    VoxelProgram() :
            Program(glm::ivec2(1920, 1080), "Voxel", {}) {
                
    }
    
    virtual void start() {
        connect(window.signal_close, slot_stop);

        graphics::Texture::LibraryT textures({
            {"stone", graphics::Texture::LibraryT::ResourceHandle(graphics::Texture::Parameter(
                "./res/Graphics/Textures/stone.png", graphics::Texture::Format::RGBA, graphics::TextureMinification::Nearest, graphics::TextureMagnification::Nearest))}
        });

        MainMenu main(GUI, textures);

        GUI::NavigationController nav(GUI);
        nav.push(main);

        run();
    }
private:
    
};

int main(int argc, char **argv) {
    VoxelProgram program = VoxelProgram();
    program.start();
    return 0;
}
