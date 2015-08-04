/* 
 * File:   SunSoundObject.h
 * Author: jonathan
 *
 * Created on August 1, 2015, 7:33 PM
 */

#ifndef SUNSOUNDOBJECT_H
#define	SUNSOUNDOBJECT_H
#include "../SunNode.h"

class SunSoundObject : public SunNode {
    
    SunSoundObject() {
        initializeDefaultPropertyAndFunctionMap();
    }
    
    void initializeDefaultPropertyAndFunctionMap() {
        SunNode::initializeDefaultPropertyAndFunctionMap();
        
        functionMap["playSound"] = bind(&SunSoundObject::playSound, this, placeholders::_1);
    }
    
    void playSound(SunNodeSentAction _action) {
        string soundName = *(string *)_action.parameters["soundName"];
        
    }
    
};

#endif

