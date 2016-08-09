// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Scripting/LuaTypeRegistrar.h>

namespace sunglasses {

template<typename T>
const std::string LuaTypeRegistrar<T>::memberTableName = "__dataMembers";

} // namespace