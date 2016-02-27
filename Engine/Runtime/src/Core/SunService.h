// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNSERVICE_H
#define SUNSERVICE_H

#include <string>

enum SunButtonState {
    SunButtonStateUp = 0,
    SunButtonStateDown = 1
};

enum SunButtonEvent {
    SunButtonEventUpSingle = 0,
    SunButtonEventDownSingle = 1,
    
    SunButtonEventUpContinuous = 2,
    SunButtonEventDownContinuous = 3
};

class SunService {
public:
    
    SunService();
    SunService(std::string _name);
    
    virtual void update();
    
    std::string name;
    
private:
    
};

#endif