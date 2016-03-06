// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNLUAOBJECTFUNCTION_H
#define SUNLUAOBJECTFUNCTION_H

#include "SunLuaCFunction.h"

template<typename S, typename... T>
class SunLuaObjectFunction : public _SunPrivateScripting::_SunLuaCFunction_Base {
public:
    template<typename Return, typename... Args>
    SunLuaObjectFunction(const char *_name, std::function<Return(Args...)> _function) {
        name = _name;
        function = _function;
    }

    SunLuaObjectFunction(SunLuaState *state, const char *_name, std::function<S(T...)> _function) {
        name = _name;
        function = _function;
        registerAsFunction(state);
    }

    void run(lua_State *state) {
        S result = execute(getArguments(state), typename _SunPrivateScripting::gens<sizeof...(T)>::type());
        _SunPrivateScripting::push(state, result);
    }

    void registerAsFunction(SunLuaState *state) {
        state->pushLightUserdata((void *)static_cast<_SunPrivateScripting::_SunLuaCFunction_Base *>(this));
        state->pushCClosure(&_SunPrivateScripting::callFunction, 1);
        state->setGlobal(name);
    }

    void setName(const char *n) { name = n; }
    template<typename Return, typename... Args>
    void setFunction(std::function<Return(Args...)> f) { function = f; }
private:
    template<int... N>
    S execute(std::tuple<T...> tuple, _SunPrivateScripting::seq<N...>) {
        return (S)function(std::get<N>(tuple)...);
    }

    template<int... N>
    std::tuple<T...> getArguments(lua_State *l, _SunPrivateScripting::seq<N...>) {
        return std::make_tuple(_SunPrivateScripting::get<T>(l, N + 1)...);
    }


    std::tuple<T...> getArguments(lua_State *l) {
        return getArguments(l, typename _SunPrivateScripting::gens<sizeof...(T)>::type());
    }

    const char *name;
    std::function<S(T...)> function;
};


// Partial Specialization of SunLuaObjectFunction for void returns
template<typename... T>
class SunLuaObjectFunction<void, T...> : public _SunPrivateScripting::_SunLuaCFunction_Base {
public:
    template<typename Return, typename... Args>
    SunLuaObjectFunction(const char *_name, std::function<Return(Args...)> _function) {
        name = _name;
        function = _function;
    }

    SunLuaObjectFunction(SunLuaState *state, const char *_name, std::function<void(T...)> _function) {
        name = _name;
        function = _function;
        registerAsFunction(state);
    }

    void run(lua_State *state) {
        execute(getArguments(state), typename _SunPrivateScripting::gens<sizeof...(T)>::type());
    }

    void registerAsFunction(SunLuaState *state) {
        //state->pushLightUserdata((void *)static_cast<_SunPrivateScripting::_SunLuaCFunction_Base *>(this));
        //state->pushCClosure(&_SunPrivateScripting::callFunction, 1);
        state->pushString(name); // Push name of function
        state->pushLightUserdata((void *)static_cast<_SunPrivateScripting::_SunLuaCFunction_Base *>(this)); // Upvalue pointer to this
        state->pushCClosure(&_SunPrivateScripting::callFunction, 1); // Push C Closure
        state->setTable(-3);
    }

    void setName(const char *n) { name = n; }
    template<typename Return, typename... Args>
    void setFunction(std::function<Return(Args...)> f) { function = f; }
private:
    template<int... N>
    void execute(std::tuple<T...> tuple, _SunPrivateScripting::seq<N...>) {
        function(std::get<N>(tuple)...);
    }

    template<int... N>
    std::tuple<T...> getArguments(lua_State *l, _SunPrivateScripting::seq<N...>) {
        return std::make_tuple(_SunPrivateScripting::get<T>(l, N + 1)...);
    }


    std::tuple<T...> getArguments(lua_State *l) {
        return getArguments(l, typename _SunPrivateScripting::gens<sizeof...(T)>::type());
    }

    const char *name;
    std::function<void(T...)> function;
};

#endif
