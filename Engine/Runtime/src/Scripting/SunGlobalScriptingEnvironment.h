// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGLOBALSCRIPTINGENVIRONMENT_H
#define SUNGLOBALSCRIPTINGENVIRONMENT_H

#include "../Core/SunService.h"
#include "../Scripting/SunLuaValue.h"
#include "../Scripting/SunLuaType.h"
#include <map>
#include <string>
#include <memory>
#include <algorithm>

class SunObject;
class SunScript;
namespace _SunPrivateScripting {
    struct SunLuaPrimitive;
}

class SunGlobalScriptingEnvironment : public SunService {
public:

    SunGlobalScriptingEnvironment();

    void initialize();
    void update();

    /// Registers an object with the logic environment.
    /**
     * This function registers an object within the logic environment. Upon calling
     * register with script, all registered objects within the logic environment will
     * be registered in the script.
     */
    void registerObject(SunObject *object);

    /// Removes a registered object from the logic environment.
    /**
     * This function takes a pointer and removes it from the list of objects if present.
     * It will also update all of the scripts by removing it from the globalenvironment
     * global table as well.
     * @retval  0   Function executed successfully
     * @retval  -1  Function did not execute successfully (object wasn't present, most likely)
     */
    int removeObject(SunObject *object);

    /// Registers the logic environment inside of a script.
    /**
     * This method registers the logic environment within the provided script.
     * @param script The script that will be used
     */
    void registerWithScript(SunScript &script);

    void registerGlobal(std::string key, _SunPrivateScripting::SunLuaPrimitive value);

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
    std::vector<SunObject *> objects;
    std::vector<SunScript *> scripts;
};
#endif
