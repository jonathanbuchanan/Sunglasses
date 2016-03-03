#include "SunLuaValue.h"

SunLuaValue::SunLuaValue(SunLuaState *s, const char *_var) {
    state = s;
    var = _var;
}

SunLuaValue::SunLuaValue(SunLuaState *s, bool _isFunctionReturn, int _index) {
    state = s;
    isFunctionReturn = _isFunctionReturn;
    index = _index;
}

SunLuaValue::SunLuaValue(SunLuaState *s, const char *_var, bool _i, SunLuaValue *p) {
    state = s;
    var = _var;
    isTableValue = _i;
    parentTable = p;
    level = parentTable->level + 1;
}

void SunLuaValue::newTable() {
    state->newTable();
    state->setGlobal(var);
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

SunLuaValue SunLuaValue::operator[](const char *element) {
    isTable = true;
    return SunLuaValue(state, element, true, this);
}

void SunLuaValue::operator=(const int &x) {
    if (!isTableValue) {
        state->pushInteger(x);
        state->setGlobal(var);
    } else {
        setUpSetTable(var);
        state->pushString(var);
        state->pushInteger(x);
        state->setTable(-3);
        cleanUpSetTable();
    }
}

void SunLuaValue::operator=(const double &x) {
    if (!isTableValue) {
        state->pushNumber(x);
        state->setGlobal(var);
    } else {
        setUpSetTable(var);
        state->pushString(var);
        state->pushNumber(x);
        state->setTable(-3);
        cleanUpSetTable();
    }
}

void SunLuaValue::operator=(const bool &x) {
    if (!isTableValue) {
        state->pushBoolean(x);
        state->setGlobal(var);
    } else {
        setUpSetTable(var);
        state->pushString(var);
        state->pushBoolean(x);
        state->setTable(-3);
        cleanUpSetTable();
    }
}

void SunLuaValue::operator=(const char *x) {
    if (!isTableValue) {
        state->pushString(x);
        state->setGlobal(var);
    } else {
        setUpSetTable(var);
        state->pushString(var);
        state->pushString(x);
        state->setTable(-3);
        cleanUpSetTable();
    }
}



void SunLuaValue::getGlobal() {
    if (isFunctionReturn)
        return;
    if (!isTableValue)
        state->getGlobal(var);
    else
        setUpGetTable(var);
}

void SunLuaValue::cleanGet() {
    //if (isFunctionReturn)
    //    return;
    if (!isTableValue)
        state->remove(index);
    else
        cleanUpGetTable();
}

void SunLuaValue::setUpGetTable(const char *key) {
    if (isTableValue) { // Not a global
        parentTable->setUpGetTable(var);
        if (state->isTable(-1)) {
            state->pushString(key);
            state->getTable(-2);
        }
    } else { // Global
        getGlobal();
        state->pushString(key);
        state->getTable(-2);
    }
}

void SunLuaValue::cleanUpGetTable() {
    if (isTableValue) { // Not a global
        parentTable->cleanUpGetTable();
        state->pop(1);
    } else { // Global
        state->pop(1);
    }
}

void SunLuaValue::setUpSetTable(const char *key) {
    if (isTableValue) { // Not a global
        parentTable->setUpSetTable(var);
        if (isTable) {
            state->pushString(var);
            state->getTable(-2);
        }
    } else { // Global
        getGlobal();
    }
}

void SunLuaValue::cleanUpSetTable() {
    if (isTableValue) { // Not a global
        parentTable->cleanUpSetTable();
        state->pop(1);
    }
}
