// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Scripting/SunLuaTypeRegistrar.h>

template<typename T>
const std::string SunLuaTypeRegistrar<T>::memberTableName = "__dataMembers";
