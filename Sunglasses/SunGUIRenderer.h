//
//  SunGUIRenderer.h
//  Sunglasses
//
//  Created by Jonathan Buchanan on 6/12/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef Sunglasses_SunGUIRenderer_h
#define Sunglasses_SunGUIRenderer_h

#include <vector>

#include "SunGUISystem.h"

class SunGUIRenderer {
public:
    SunTextRenderer textRenderer;
    
    SunGUIRenderer() {
        
    }
    
    void initialize() {
        // Initialize the text renderer
        textRenderer = SunTextRenderer();
        textRenderer.initialize();
    }
    
    void renderSystem(SunGUISystem *_system) {
        // Check to see if the GUI system's fonts have been loaded
        if (_system->fontsLoaded == false)
            _system->loadFonts(&textRenderer);
        
        // Force the system to render
        _system->render(&textRenderer);
    }
    
private:
    
};

#endif
