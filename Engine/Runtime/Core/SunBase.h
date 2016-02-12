// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNBASE_H
#define SUNBASE_H

#include <string>
#include <map>

#include "SunAction.h"
#include "SunService.h"

class SunBase {
public:
    SunBase();
    SunBase(std::string n);
    
    virtual void init();
	
	template<typename Ret, typename Class, typename Param>
	void addAction(std::string function, Ret (Class::*f)(Param)) {
		std::function<void(SunAction)> bound = std::bind(f, static_cast<Class *>(this), std::placeholders::_1);
		functions[function] = bound;
	}
	
	void processAction(SunAction action);
	
    inline std::string & getName() { return name; }
    inline void setName(std::string n) { name = n; }
    
    inline std::map<std::string, SunService *> & getServices() { return services; }
	inline SunService * getService(std::string s) { return services[s]; }
    inline void addService(SunService *s) { services[s->name] = s; }

	static std::map<std::string, SunService *> services;
private:
    std::string name;
        
    std::map<std::string, SunActionFunction> functions;	
};

extern void sendAction(SunAction action, SunBase *base);

#endif
