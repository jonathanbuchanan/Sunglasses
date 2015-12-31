#include "./SunPrimitives.h"

bool operator==(const SunVertex &v1, const SunVertex &v2) {
    return v1.position == v2.position;
} 

uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0);
default_random_engine generator;

void clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}