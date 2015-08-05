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
    glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
    glm::vec3 direction = glm::vec3(0.0, 0.0, 1.0);
    
    void setPositionAndDirection() {
        sf::Listener::setPosition(position.x, position.y, position.z);
        sf::Listener::setDirection(direction.x, direction.y, direction.z);
    }
    
private:
    
};

#endif

