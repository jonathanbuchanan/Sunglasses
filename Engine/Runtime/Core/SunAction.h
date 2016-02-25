// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNACTION_H
#define SUNACTION_H

#include <functional>
#include <string>
#include <map>

class SunBase;

typedef void * SunActionParameter;
typedef std::map<std::string, SunActionParameter> SunActionParameterMap;

class SunAction {
public:
	SunAction();
	SunAction(std::string a);
	SunAction(std::string a, SunActionParameterMap p);
	SunAction(std::string a, bool r);
	SunAction(std::string a, SunActionParameterMap p, bool r);
	SunAction(std::string a, bool r, SunActionParameterMap p);

	inline void setAction(std::string a) { action = a; }
	inline std::string getAction() { return action; }

	inline bool parameterExists(std::string p) { return parameters.find(p) != parameters.end(); }
	inline void * getParameter(std::string p) { return parameters[p]; }
	inline void addParameter(std::string k, void *v) { parameters[k] = v; }
	
	inline bool getRecursive() { return recursive; }
	inline void setRecursive(bool r) { recursive = r; }
private:
	std::string action;
	SunActionParameterMap parameters;
	bool recursive = false;
};

typedef std::function<void(SunAction)> SunActionFunction;

typedef std::function<void(SunBase *)> SunLambdaActionFunction;

class SunLambdaAction {
public:
	SunLambdaAction();
	SunLambdaAction(SunLambdaActionFunction f);
	
	void run(SunBase *base);
	
	inline void setFunction(SunLambdaActionFunction f) { function = f; }
private:
	SunLambdaActionFunction function;
};

#endif
