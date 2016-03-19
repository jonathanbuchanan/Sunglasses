// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGLOBALLOGICENVIRONMENT_H
#define SUNGLOBALLOGICENVIRONMENT_H

#include "../Core/SunService.h"
#include "../Scripting/SunLuaValue.h"
#include "../Scripting/SunLuaType.h"
#include <map>
#include <string>
#include <memory>

class SunObject;
class SunScript;
namespace _SunPrivateScripting {
    struct SunLuaPrimitive;
}

class SunGlobalLogicEnvironment : public SunService {
public:

    SunGlobalLogicEnvironment();

    void initialize();
    void update();

    /// Registers an object with the logic environment.
    /**
     * This function registers an object within the logic environment. Upon calling
     * register with script, all registered objects within the logic environment will
     * be registered in the script.
     */
    void registerObject(std::string name, SunObject *object);
    void registerWithScript(SunScript *script);

    void registerGlobal(std::string key, _SunPrivateScripting::SunLuaPrimitive value);

    template<typename S, typename... T>
    void registerType(std::string type, T... members) {
        types[type] = std::shared_ptr<_SunPrivateScripting::_SunLuaType_Base>(new _SunPrivateScripting::SunLuaType<S, T...>(members...));
    }

    template<typename T>
    void registerObjectAsType(std::string name, std::string type, T *object) {

    }

    template<typename T>
    void registerObjectAsType(_SunPrivateScripting::SunLuaValue value, std::string type, T *object) {

    }

    bool globalExists(const char *key);

    void setInteger(const char *key, int value);
    void setBoolean(const char *key, bool value);
    void setNumber(const char *key, double value);
    void setString(const char *key, const char *value);

    int getInteger(const char *key);
    bool getBoolean(const char *key);
    double getNumber(const char *key);
    const char * getString(const char *key);

private:
    std::map<std::string, _SunPrivateScripting::SunLuaPrimitive> globals;
    std::vector<std::shared_ptr<_SunPrivateScripting::_SunLuaObject_Base>> objects;
    std::map<std::string, std::shared_ptr<_SunPrivateScripting::_SunLuaType_Base>> types;
};

#endif
