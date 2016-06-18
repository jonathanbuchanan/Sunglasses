#ifndef GUIGAME_H
#define GUIGAME_H

#include <Sunglasses/Sunglasses.hpp>

class GUIGame : public SunGame {
public:
    GUIGame(int argc, char **argv);

    void loop();
};

#endif
