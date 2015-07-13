//
//  main.cpp
//  OpenGL_Test_3
//
//  Created by Jonathan Buchanan on 4/18/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#include <iostream>
#include "SunGame.h"

SunGame game = SunGame();

int main(int argc, const char *argv[]) {
    game.initializeGLFWandGLEW(true, 4);
    
    game.loop();
    
    return 0;
}