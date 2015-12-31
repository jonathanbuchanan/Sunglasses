/* 
 * File:   SunSoundListener.h
 * Author: jonathan
 *
 * Created on August 4, 2015, 7:10 PM
 */

#ifndef SUNSOUNDLISTENER_H
#define	SUNSOUNDLISTENER_H

#include <vector>
using namespace std;

#include "../Libraries/glm/glm.hpp"
#include "../Libraries/glm/gtc/matrix_transform.hpp"

#include <SFML/Audio.hpp>

class SunSoundListener {
public:
    SunSoundListener() { }
    SunSoundListener(glm::vec3 _position, glm::vec3 _direction);
    
    void setPositionAndDirection();
    
    inline glm::vec3 & getPosition() { return position; }
    inline void setPosition(glm::vec3 _position) { position = _position; }
    
    inline glm::vec3 & getDirection() { return direction; }
    inline void setDirection(glm::vec3 _direction) { direction = _direction; }
private:
    // Position and Direction
    glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
    glm::vec3 direction = glm::vec3(0.0, 0.0, 1.0);
};

#endif

