// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Scripting/LuaTypeRegistrar.h>

#include <glm/glm.hpp>

namespace sunglasses {

// glm::vec2
template<> const std::string LuaTypeRegistrar<glm::vec2>::typeName = "Vec2";
template<> const std::map<std::string, Scripting::LuaTypeDataMemberBase<glm::vec2> *> LuaTypeRegistrar<glm::vec2>::dataMembers = {
    {"x", new LuaTypeDataMember<float, glm::vec2>("x", &glm::vec2::x)},
    {"y", new LuaTypeDataMember<float, glm::vec2>("y", &glm::vec2::y)}
};

// glm::vec3
template<> const std::string LuaTypeRegistrar<glm::vec3>::typeName = "Vec3";
template<> const std::map<std::string, Scripting::LuaTypeDataMemberBase<glm::vec3> *> LuaTypeRegistrar<glm::vec3>::dataMembers = {
    {"x", new LuaTypeDataMember<float, glm::vec3>("x", &glm::vec3::x)},
    {"y", new LuaTypeDataMember<float, glm::vec3>("y", &glm::vec3::y)},
    {"z", new LuaTypeDataMember<float, glm::vec3>("z", &glm::vec3::z)}
};

// glm::vec4
template<> const std::string LuaTypeRegistrar<glm::vec4>::typeName = "Vec4";
template<> const std::map<std::string, Scripting::LuaTypeDataMemberBase<glm::vec4> *> LuaTypeRegistrar<glm::vec4>::dataMembers = {
    {"x", new LuaTypeDataMember<float, glm::vec4>("x", &glm::vec4::x)},
    {"y", new LuaTypeDataMember<float, glm::vec4>("y", &glm::vec4::y)},
    {"z", new LuaTypeDataMember<float, glm::vec4>("z", &glm::vec4::z)},
    {"w", new LuaTypeDataMember<float, glm::vec4>("w", &glm::vec4::w)}
};

// glm::mat2

// glm::mat3

// glm::mat4 

} // namespace
