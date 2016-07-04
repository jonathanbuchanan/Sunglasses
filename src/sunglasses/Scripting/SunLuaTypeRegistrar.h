// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNLUATYPEREGISTRAR_H
#define SUNLUATYPEREGISTRAR_H

#include "SunLuaCFunction.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <lua.hpp>

namespace SunScripting {
    /**
     * This struct is the abstract base for SunLuaTypeDataMember.
     * @see SunLuaTypeDataMember
     */
    template<typename T> // T is the type of the object
    struct SunLuaTypeDataMemberBase {
        /// Constructor with name
        SunLuaTypeDataMemberBase(std::string _name) : name(_name) { }

        /// Assigns the value from the top of the lua stack
        virtual void assignFromStack(lua_State *state, T *object, int index) = 0;

        /// Pushes the value to the top of the lua stack
        virtual void pushToStack(lua_State *state, T *object) = 0; 

        /// The name of the data member
        std::string name;
    };
}

template<typename T, typename S, typename... R> // T is the class type, S is the return type, R... are the parameters
struct SunLuaTypeMemberFunction : public SunScripting::SunLuaTypeDataMemberBase<T> {
    SunLuaTypeMemberFunction(std::string _name, S (T::* _function)(R...)) : SunScripting::SunLuaTypeDataMemberBase<T>(_name), function(_function) { }
    
    static int run(lua_State *state) {
        T *object = (T *)lua_touserdata(state, lua_upvalueindex(2));
        SunLuaTypeMemberFunction<T, S, R...> *function = (SunLuaTypeMemberFunction<T, S, R...> *)lua_touserdata(state, lua_upvalueindex(1));
        S result = function->execute(object, function->getArguments(state), typename _SunPrivateScripting::gens<sizeof...(R)>::type());
        SunScripting::pushToStack(state, result);
        return 1;
    }

    virtual void assignFromStack(lua_State *state, T *object, int index) {

    }

    virtual void pushToStack(lua_State *state, T *object) {
        lua_pushlightuserdata(state, (void *)this);
        lua_pushlightuserdata(state, (void *)object);
        lua_pushcclosure(state, run, 2);
    }

private:
    template<int... N>
    S execute(T *object, std::tuple<R...> tuple, _SunPrivateScripting::seq<N...>) {
        return (S)(object->*function)(std::get<N>(tuple)...);
    }

    template<int... N>
    std::tuple<R...> getArguments(lua_State *l, _SunPrivateScripting::seq<N...>) {
        return std::make_tuple(SunScripting::getFromStack<R>(l, N + 1)...);
    }


    std::tuple<R...> getArguments(lua_State *l) {
        return getArguments(l, typename _SunPrivateScripting::gens<sizeof...(R)>::type());
    }

    S (T::* function)(R...);
};

template<typename T, typename... R> // T is the class type, void is the return type, R... are the parameters
struct SunLuaTypeMemberFunction<T, void, R...> : public SunScripting::SunLuaTypeDataMemberBase<T> {
    SunLuaTypeMemberFunction(std::string _name, void (T::* _function)(R...)) : SunScripting::SunLuaTypeDataMemberBase<T>(_name), function(_function) { }
    
    static int run(lua_State *state) {
        T *object = (T *)lua_touserdata(state, lua_upvalueindex(2));
        SunLuaTypeMemberFunction<T, void, R...> *function = (SunLuaTypeMemberFunction<T, void, R...> *)lua_touserdata(state, lua_upvalueindex(1));
        function->execute(object, function->getArguments(state), typename _SunPrivateScripting::gens<sizeof...(R)>::type());
        return 0;
    }

    virtual void assignFromStack(lua_State *state, T *object, int index) {

    }

    virtual void pushToStack(lua_State *state, T *object) {
        lua_pushlightuserdata(state, (void *)this);
        lua_pushlightuserdata(state, (void *)object);
        lua_pushcclosure(state, run, 2);
    }

private:
    template<int... N>
    void execute(T *object, std::tuple<R...> tuple, _SunPrivateScripting::seq<N...>) {
        (object->*function)(std::get<N>(tuple)...);
    }

    template<int... N>
    std::tuple<R...> getArguments(lua_State *l, _SunPrivateScripting::seq<N...>) {
        return std::make_tuple(SunScripting::getFromStack<R>(l, N + 1)...);
    }


    std::tuple<R...> getArguments(lua_State *l) {
        return getArguments(l, typename _SunPrivateScripting::gens<sizeof...(R)>::type());
    }
    void (T::* function)(R...);
};

/**
 * This struct is used as a container for a data member of class.
 */
template<typename T, typename S> // T is the type of the data member, S is the class type
struct SunLuaTypeDataMember : public SunScripting::SunLuaTypeDataMemberBase<S> {
    /// Constructs the object with a pointer to the data member.
    SunLuaTypeDataMember(std::string _name, T S::* _data) : SunScripting::SunLuaTypeDataMemberBase<S>(_name), data(_data) { }

    /// Assigns the value from the top of the lua stack
    virtual void assignFromStack(lua_State *state, S *object, int index) {
        object->*data = SunScripting::getFromStack<T>(state, index);
    }

    /// Pushes the value to the top of the lua stack
    virtual void pushToStack(lua_State *state, S *object) {
        SunScripting::pushToStack(state, object->*data);
    }

    /// The pointer to the data member
    T S::* data;
};

template<typename T>
class SunLuaTypeRegistrar;

/**
 * This struct is used as a container for a data member of a class that
 * is not a primitive.
 */
template<typename T, typename S> // T is the type of the data member, S is the class type
struct SunLuaComplexDataMember : public SunScripting::SunLuaTypeDataMemberBase<S> {
    /// Constructs the object with a pointer to the data member.
    SunLuaComplexDataMember(std::string _name, T S::* _data) : SunScripting::SunLuaTypeDataMemberBase<S>(_name), data(_data) { }

    /// Assigns the value from the top of the lua stack
    virtual void assignFromStack(lua_State *state, S *object, int index) {
        lua_getfield(state, index, "__object");
        T *member = (T *)lua_touserdata(state, -1);
        object->*data = *member;
        lua_pop(state, 1);
    }

    /// Pushes the value to the top of the lua stack
    virtual void pushToStack(lua_State *state, S *object) {
        SunLuaTypeRegistrar<T>::registerObject(state, &(object->*data));
    }

    /// The pointer to the data member
    T S::* data;
};

/**
 * This class is used as a container for the data used in registering a type in
 * a Lua script.
 * @warning This type should be a friend of any class you intend to register in
 * Lua if you want to access its private members.
 */
template<typename T>
class SunLuaTypeRegistrar {
public:
    /// This method registers the type within a state
    /**
     * @params state The lua state to register the type in
     */
    static void registerInState(lua_State *state) {
        lua_pushcfunction(state, &SunLuaTypeRegistrar<T>::constructor);
        lua_setglobal(state, typeName.c_str());
    }

    /// Registers an existing object in C++ within a Lua state and pushes it to the top of the stack
    /**
     * @param state The Lua state to register the object in
     * @param name The name of the object
     * @param object A pointer to the object
     */
    static void registerObject(lua_State *state, T *object) {
        lua_newtable(state);

        // Set the table's object pointer
        lua_pushlightuserdata(state, (void *)object);
        lua_setfield(state, -2, "__object");

        // Set the table's metatable
        lua_newtable(state);

        lua_pushcfunction(state, &SunLuaTypeRegistrar<T>::index);
        lua_setfield(state, -2, "__index");

        lua_pushcfunction(state, &SunLuaTypeRegistrar<T>::newindex);
        lua_setfield(state, -2, "__newindex");

        lua_setmetatable(state, -2); 
    }

    static int constructor(lua_State *state) {
        T *object = new T();
        
        for (auto &iterator : dataMembers) {
            lua_pushstring(state, iterator.first.c_str());
            lua_gettable(state, -2);
            if (!lua_isnil(state, -1)) { // Value exists
                iterator.second->assignFromStack(state, object, -1);
            }
            lua_pop(state, 1);
        }

        lua_newtable(state);

        // Set the table's object pointer
        lua_pushlightuserdata(state, (void *)object);
        lua_setfield(state, -2, "__object");

        // Set the table's metatable
        lua_newtable(state);

        lua_pushcfunction(state, &SunLuaTypeRegistrar<T>::index);
        lua_setfield(state, -2, "__index");

        lua_pushcfunction(state, &SunLuaTypeRegistrar<T>::newindex);
        lua_setfield(state, -2, "__newindex");

        lua_setmetatable(state, -2);
        return 1;
    }
private:
    /// The '__index' metamethod for the object
    static int index(lua_State *state) {
        lua_pushstring(state, "__object");
        lua_gettable(state, 1);

        T *object = (T *)lua_touserdata(state, -1);
        lua_pop(state, 1);

        const char *key = SunScripting::getFromStack<const char *>(state, 2);
        dataMembers.at(std::string(key))->pushToStack(state, object);
        return 1;
    }

    /// The '__newindex' metamethod for the object
    static int newindex(lua_State *state) {
        // IMPLEMENT CHECK FOR FUNCTIONS HERE
        lua_pushstring(state, "__object");
        lua_gettable(state, 1);

        T *object = (T *)lua_touserdata(state, -1);
        lua_pop(state, 1);

        const char *key = SunScripting::getFromStack<const char *>(state, 2);

        dataMembers.at(std::string(key))->assignFromStack(state, object, 3);

        return 0;
    }

    /// The name of the type - this must be set for each type that is used
    const static std::string typeName;

    /// The vector of data members - this must be set for each type that is used
    const static std::map<std::string, SunScripting::SunLuaTypeDataMemberBase<T> *> dataMembers;

    /// The name of the subtable containing the data members
    /**
     * @warning Override this if you are registering a member named '__dataMembers'
     */
    const static std::string memberTableName;
};

#endif