#ifndef SUNSERVICE_H
#define SUNSERVICE_H

#include <string>

class SunService {
public:
    
    SunService();
    SunService(std::string _name);
    
    virtual void update();
    
    std::string name;
    
private:
    
};

#endif