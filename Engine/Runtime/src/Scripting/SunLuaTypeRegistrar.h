// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNLUATYPEREGISTRAR_H
#define SUNLUATYPEREGISTRAR_H

#include <string>
#include <vector>
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
        virtual void assignFromStack(lua_State *state, T *object) = 0;

        /// Pushes the value to the top of the lua stack
        virtual void pushToStack(lua_State *state, T *object) = 0; 

        /// The name of the data member
        std::string name;
    };
}

/**
 * This struct is used as a container for a data member of class.
 */
template<typename T, typename S> // T is the type of the data member, S is the class type
struct SunLuaTypeDataMember : public SunScripting::SunLuaTypeDataMemberBase<S> {
    /// Constructs the object with a pointer to the data member.
    SunLuaTypeDataMember(std::string _name, T S::* _data) : SunScripting::SunLuaTypeDataMemberBase<S>(_name), data(_data) { }

    /// Assigns the value from the top of the lua stack
    virtual void assignFromStack(lua_State *state, S *object) {
        // This must be called if it is not int, float, or string because of specialization
    }

    /// Pushes the value to the top of the lua stack
    virtual void pushToStack(lua_State *stat, S *object) {
        // This must be called if it is not int, float, or string because of specialization
    }

    /// The pointer to the data member
    T S::* data;
};

#include <iostream>

template<typename T>
struct SunLuaTypeDataMember<int, T> : public SunScripting::SunLuaTypeDataMemberBase<T> {
    SunLuaTypeDataMember(std::string _name, int T::* _data) : SunScripting::SunLuaTypeDataMemberBase<T>(_name), data(_data) { }

    virtual void assignFromStack(lua_State *state, T *object) {
        object->*data = lua_tointeger(state, -1);
    }

    virtual void pushToStack(lua_State *state, T *object) {
        lua_pushinteger(state, object->*data);
    }

    int T::* data;
};

template<typename T>
struct SunLuaTypeDataMember<float, T> : public SunScripting::SunLuaTypeDataMemberBase<T> {
    SunLuaTypeDataMember(std::string _name, float T::* _data) : SunScripting::SunLuaTypeDataMemberBase<T>(_name), data(_data) { }

    virtual void assignFromStack(lua_State *state, T *object) {
        object->*data = lua_tonumber(state, -1);
    }

    virtual void pushToStack(lua_State *state, T *object) {
        lua_pushnumber(state, object->*data);
    }

    float T::* data;
};

template<typename T>
struct SunLuaTypeDataMember<std::string, T> : public SunScripting::SunLuaTypeDataMemberBase<T> {
    SunLuaTypeDataMember(std::string _name, std::string T::* _data) : SunScripting::SunLuaTypeDataMemberBase<T>(_name), data(_data) { }

    virtual void assignFromStack(lua_State *state, T *object) {
        object->*data = std::string(lua_tostring(state, -1));
    }

    virtual void pushToStack(lua_State *state, T *object) {
        lua_pushstring(state, (object->*data).c_str());
    }

    std::string T::* data;
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

    static int constructor(lua_State *state) {
        T *object = new T();
        
        for (size_t i = 0; i < dataMembers.size(); ++i) {
            lua_pushstring(state, dataMembers[i]->name.c_str());
            lua_gettable(state, -2);
            if (!lua_isnil(state, -1)) { // Value exists
                dataMembers[i]->assignFromStack(state, object);
            }
            lua_pop(state, 1);
        }

        lua_newtable(state);

        for (size_t i = 0; i < dataMembers.size(); ++i) {
            lua_pushstring(state, dataMembers[i]->name.c_str());
            dataMembers[i]->pushToStack(state, object);
            lua_settable(state, -3);
        }
        return 1;
    }
private:
    /// The name of the type - this must be set for each type that is used
    const static std::string typeName;

    /// The vector of data members - this must be set for each type that is used
    const static std::vector<SunScripting::SunLuaTypeDataMemberBase<T> *> dataMembers;
};

#endif