#ifndef BLOCK_H
#define BLOCK_H

#include <Sunglasses/Sunglasses.hpp>

class Block : public SunObject {
public:
    void init();

    void update(SunAction action);

    void render(SunAction action);
private:

};

#endif
