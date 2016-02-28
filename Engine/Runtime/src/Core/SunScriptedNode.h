// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNSCRIPTEDNODE_H
#define SUNSCRIPTEDNODE_H

#include <selene.h>

#include "SunNode.h"

class SunScriptedNode : public SunNode {
public:
    SunScriptedNode();
    SunScriptedNode(std::string file);

    void loadFile(std::string file);

    inline sel::Selector operator[](const char *name) { return state[name]; }
    inline sel::Selector getElement(const char *name) { return state[name]; }
    inline sel::Selector getObject(const char *name) { return state[name]; }
    inline sel::Selector getVariable(const char *name) { return state[name]; }
    inline sel::Selector getFunction(const char *name) { return state[name]; }

    void run(const char *code);
    void operator()(const char *code);

    template<typename N, typename... T> // Register std::function
    void registerFunction(const char *name, std::function<N(T...)> function) {
        state[name] = function;
    }
    template<typename T> // Register lambda
    void registerFunction(const char *name, T lambda) {
        state[name] = lambda;
    }
    template<typename N, typename... T> // Register C Function
    void registerFunction(const char *name, N (* function)(T...)) {
        state[name] = function;
    }

    template<typename M, typename N, typename... T>
    void registerClass(const char *name, T... functions) {
        state[name].SetClass<M, N>(functions...);
    }

    template<typename N, typename... T>
    void registerObject(const char *name, N &object, T... functions) {
        state[name].SetObj(object, functions...);
    }
private:
    sel::State state{true};
};

#endif
