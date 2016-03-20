// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunLuaValue.h"

namespace _SunPrivateScripting {
    SunLuaValue::SunLuaValue(SunLuaState *s, bool _isFunctionReturn, int _index) {
        state = s;
        isFunctionReturn = _isFunctionReturn;
        index = _index;
    }

    void SunLuaValue::newTable() {
        if (tables.size() > 1) {
            setUpSetTable();
            state->pushString((const char *)tables[tables.size() - 1]);
        }
        state->newTable();
        if (tables.size() < 2)
            state->setGlobal((const char *)tables[tables.size() - 1]);
        else
            state->setTable(-3);
    }

    SunLuaValue::operator int() {
        getGlobal();
        int x = state->getInteger(index);
        cleanGet();
        return x;
    }

    SunLuaValue::operator double() {
        getGlobal();
        double x = state->getNumber(index);
        cleanGet();
        return x;
    }

    SunLuaValue::operator bool() {
        getGlobal();
        bool x = state->getBoolean(index);
        cleanGet();
        return x;
    }

    SunLuaValue::operator std::string() {
        getGlobal();
        std::string x = std::string(state->getString(index));
        cleanGet();
        return x;
    }

    SunLuaValue SunLuaValue::operator[](const int &element) {
        return SunLuaValue(state, tables, _SunPrivateScripting::SunLuaPrimitive(element));
    }

    SunLuaValue SunLuaValue::operator[](const char *element) {
        return SunLuaValue(state, tables, _SunPrivateScripting::SunLuaPrimitive(element));
    }

    void SunLuaValue::operator=(const int &x) {
        if (tables.size() < 2) {
            state->pushInteger(x);
            state->setGlobal((const char *)tables[tables.size() - 1]);
        } else {
            setUpSetTable();
            tables[tables.size() - 1].push(state);
            state->pushInteger(x);
            state->setTable(-3);
            cleanUpSetTable();
        }
    }

    void SunLuaValue::operator=(const double &x) {
        if (tables.size() < 2) {
            state->pushNumber(x);
            state->setGlobal((const char *)tables[tables.size() - 1]);
        } else {
            setUpSetTable();
            tables[tables.size() - 1].push(state);
            state->pushNumber(x);
            state->setTable(-3);
            cleanUpSetTable();
        }
    }

    void SunLuaValue::operator=(const bool &x) {
        if (tables.size() < 2) {
            state->pushBoolean(x);
            state->setGlobal((const char *)tables[tables.size() - 1]);
        } else {
            setUpSetTable();
            tables[tables.size() - 1].push(state);
            state->pushBoolean(x);
            state->setTable(-3);
            cleanUpSetTable();
        }
    }

    void SunLuaValue::operator=(const char *x) {
        if (tables.size() < 2) {
            state->pushString(x);
            state->setGlobal((const char *)tables[tables.size() - 1]);
        } else {
            setUpSetTable();
            tables[tables.size() - 1].push(state);
            state->pushString(x);
            state->setTable(-3);
            cleanUpSetTable();
        }
    }

    void SunLuaValue::setNil() {
        if (tables.size() < 2) {
            state->pushNil();
            state->setGlobal((const char *)tables[tables.size() - 1]);
        } else {
            setUpSetTable();
            tables[tables.size() - 1].push(state);
            state->pushNil();
            state->setTable(-3);
            cleanUpSetTable();
        }
    }

    void SunLuaValue::getGlobal() {
        if (isFunctionReturn)
            return;
        if (tables.size() < 2)
            state->getGlobal((const char *)tables[tables.size() - 1]);
        else
            setUpGetTable();
    }

    void SunLuaValue::cleanGet() {
        if (tables.size() < 2)
            state->remove(index);
        else
            cleanUpGetTable();
    }

    void SunLuaValue::setUpGetTable() {
        // Global Table
        state->getGlobal((const char *)tables[0]);
        tables[1].push(state);
        state->getTable(-2);
        for (size_t i = 1; i < tables.size() - 1; i++) {
            tables[i + 1].push(state);
            state->getTable(-2);
        }
    }

    void SunLuaValue::cleanUpGetTable() {
        state->pop(tables.size());
    }

    void SunLuaValue::setUpSetTable() {
        // Global Table
        state->getGlobal((const char *)tables[0]);
        for (size_t i = 1; i < tables.size() - 1; i++) {
            tables[i].push(state);
            state->getTable(-2);
        }
    }

    void SunLuaValue::cleanUpSetTable() {
        state->pop(tables.size());
    }
}
