// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "../Scripting/SunLuaTypeRegistrar.h"

#include <glm/glm.hpp>

// glm::vec2
template<> const std::string SunLuaTypeRegistrar<glm::vec2>::typeName = "Vec2";
template<> const std::map<std::string, SunScripting::SunLuaTypeDataMemberBase<glm::vec2> *> SunLuaTypeRegistrar<glm::vec2>::dataMembers = {
    {"x", new SunLuaTypeDataMember<float, glm::vec2>("x", &glm::vec2::x)},
    {"y", new SunLuaTypeDataMember<float, glm::vec2>("y", &glm::vec2::y)}
};

// glm::vec3
template<> const std::string SunLuaTypeRegistrar<glm::vec3>::typeName = "Vec3";
template<> const std::map<std::string, SunScripting::SunLuaTypeDataMemberBase<glm::vec3> *> SunLuaTypeRegistrar<glm::vec3>::dataMembers = {
    {"x", new SunLuaTypeDataMember<float, glm::vec3>("x", &glm::vec3::x)},
    {"y", new SunLuaTypeDataMember<float, glm::vec3>("y", &glm::vec3::y)},
    {"z", new SunLuaTypeDataMember<float, glm::vec3>("z", &glm::vec3::z)}
};

// glm::vec4
template<> const std::string SunLuaTypeRegistrar<glm::vec4>::typeName = "Vec4";
template<> const std::map<std::string, SunScripting::SunLuaTypeDataMemberBase<glm::vec4> *> SunLuaTypeRegistrar<glm::vec4>::dataMembers = {
    {"x", new SunLuaTypeDataMember<float, glm::vec4>("x", &glm::vec4::x)},
    {"y", new SunLuaTypeDataMember<float, glm::vec4>("y", &glm::vec4::y)},
    {"z", new SunLuaTypeDataMember<float, glm::vec4>("z", &glm::vec4::z)},
    {"w", new SunLuaTypeDataMember<float, glm::vec4>("w", &glm::vec4::w)}
};

// glm::mat2

// glm::mat3

// glm::mat4 
