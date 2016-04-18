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
     * This struct is used as a container for a data member of class.
     */
    template<typename T, typename S> // T is the type of the data member, S is the class type
    class SunLuaTypeDataMember {
    public:

    private:
        T S::* data;
    };
}

/**
 * This class is used as a container for the data used in registering a type in
 * a Lua script.
 */
template<typename T>
class SunLuaTypeRegistrar {
public:
    /// This method registers the type within a state
    /**
     * @params state The lua state to register the type in
     */
    static void registerInState(lua_State *state) {
    
    }
private:
    /// The name of the type - this must be set for each type that is used
    const static std::string typeName;

    /// The vector of data members - this must be set for each type that is used
    const static std::vector<void *> dataMembers;
};

#endif
