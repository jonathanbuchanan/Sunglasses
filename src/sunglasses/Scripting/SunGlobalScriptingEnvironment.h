// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGLOBALSCRIPTINGENVIRONMENT_H
#define SUNGLOBALSCRIPTINGENVIRONMENT_H

#include <sunglasses/Core/SunService.h>
#include <sunglasses/Core/SunServiceManager.h>
#include <sunglasses/Scripting/SunScript.h>
#include <glm/glm.hpp>
#include <map>
#include <string>
#include <memory>
#include <algorithm>

class SunObject;
namespace _SunPrivateScripting {
    struct SunLuaPrimitive;
}

template<typename T>
using SunServiceNamePair = std::string;

class SunCursorManager;
class SunKeyboardManager;
class SunMouseButtonManager;
class SunWindowManager;

/// A variable template for the name of services in lua
template<typename T>
const std::string luaServiceName;

template<> const std::string luaServiceName<SunCursorManager> = "cursor_manager";
template<> const std::string luaServiceName<SunKeyboardManager> = "keyboard_manager";
template<> const std::string luaServiceName<SunMouseButtonManager> = "mouse_button_manager";
template<> const std::string luaServiceName<SunWindowManager> = "window_manager";

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
     * This also registers all of the services into a script. Commonly used
     * types are registered as well.
     * @param script The script that will be used
     */
    template<typename T>
    void registerScript(T *object, SunScript &script) {
        //script.registerTypes<glm::vec2, glm::vec3, glm::vec4>();

        script.registerObject(this, "globalenvironment");

        registerServices(object->services, script);
    }

    /// Registers all the services into a script.
    void registerServices(SunServiceManager &services, SunScript &script);
    
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
    template<typename T, typename S, typename... R>
    void iterateTypes(SunServiceManager &services, SunScript &script) {
        registerService<T>(services, script);
        iterateTypes<S, R...>(services, script);
    }

    template<typename T>
    void iterateTypes(SunServiceManager &services, SunScript &script) {
        registerService<T>(services, script);
    }

    template<typename T>
    void registerService(SunServiceManager &services, SunScript &script) {
        T *service = services.get<T>();
        script.registerObject(service, luaServiceName<T>);
    }
    std::map<std::string, _SunPrivateScripting::SunLuaPrimitive> globals;
    std::vector<SunObject *> objects;
    std::vector<SunScript *> scripts;
};
#endif
