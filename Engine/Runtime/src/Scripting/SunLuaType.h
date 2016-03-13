// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNLUATYPE_H
#define SUNLUATYPE_H

#include "SunLuaObject.h"
#include <vector>
#include <memory>
#include <tuple>

namespace _SunPrivateScripting {
    class _SunLuaType_Base {
    public:
        virtual void registerObject(SunLuaState *state, const char *name, void *_object) = 0;
        virtual void registerObject(SunLuaState *state, SunLuaValue value, void *_object) = 0;
    private:

    };

    template<typename S, typename... T> // S is object type, T are the members
    class SunLuaType : public _SunLuaType_Base {
    public:
        SunLuaType(T... funcs) {
            functions = std::make_tuple(funcs...);
        }

        void registerObject(SunLuaState *state, const char *name, void *_object) {
            S *object = (S *)_object;
            constructObject(state, name, object, typename _SunPrivateScripting::gens<sizeof...(T)>::type());
        }

        void registerObject(SunLuaState *state, SunLuaValue value, void *_object) {
            S *object = (S *)_object;
            constructObject(state, value, object, typename _SunPrivateScripting::gens<sizeof...(T)>::type());
        }

    private:
        template<int... N>
        void constructObject(SunLuaState *state, const char *name, S *object, _SunPrivateScripting::seq<N...>) {
            SunLuaObject<S, T...> *x = new SunLuaObject<S, T...>(state, name, object, std::get<N>(functions)...);
        }

        template<int... N>
        void constructObject(SunLuaState *state, SunLuaValue value, S *object, _SunPrivateScripting::seq<N...>) {
            SunLuaObject<S, T...> *x = new SunLuaObject<S, T...>(state, value, object, std::get<N>(functions)...);
        }

        std::tuple<T...> functions;
    };
}

#endif
