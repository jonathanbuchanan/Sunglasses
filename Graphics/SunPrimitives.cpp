#include "./SunPrimitives.h"

uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0);
default_random_engine generator;

void clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}