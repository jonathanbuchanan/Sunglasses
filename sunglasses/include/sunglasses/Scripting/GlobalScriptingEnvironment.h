// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef GLOBALSCRIPTINGENVIRONMENT_H
#define GLOBALSCRIPTINGENVIRONMENT_H

#include <sunglasses/Core/Service.h>
#include <sunglasses/Core/ServiceManager.h>
#include <sunglasses/Scripting/Script.h>
#include <glm/glm.hpp>
#include <map>
#include <string>
#include <memory>
#include <algorithm>

namespace sunglasses {

class Object;
namespace _PrivateScripting {
    struct LuaPrimitive;
}

template<typename T>
using ServiceNamePair = std::string;

class CursorManager;
class KeyboardManager;
class MouseButtonManager;
class WindowManager;

/// A variable template for the name of services in lua
template<typename T>
const std::string luaServiceName;

template<> const std::string luaServiceName<CursorManager> = "cursor_manager";
template<> const std::string luaServiceName<KeyboardManager> = "keyboard_manager";
template<> const std::string luaServiceName<MouseButtonManager> = "mouse_button_manager";
template<> const std::string luaServiceName<WindowManager> = "window_manager";

class GlobalScriptingEnvironment : public Service {
public:

    GlobalScriptingEnvironment();

    void initialize();
    void update();

    /// Registers an object with the logic environment.
    /**
     * This function registers an object within the logic environment. Upon calling
     * register with script, all registered objects within the logic environment will
     * be registered in the script.
     */
    void registerObject(Object *object);

    /// Removes a registered object from the logic environment.
    /**
     * This function takes a pointer and removes it from the list of objects if present.
     * It will also update all of the scripts by removing it from the globalenvironment
     * global table as well.
     * @retval  0   Function executed successfully
     * @retval  -1  Function did not execute successfully (object wasn't present, most likely)
     */
    int removeObject(Object *object);

    /// Registers the logic environment inside of a script.
    /**
     * This method registers the logic environment within the provided script.
     * This also registers all of the services into a script. Commonly used
     * types are registered as well.
     * @param script The script that will be used
     */
    template<typename T>
    void registerScript(T *object, Script &script) {
        //script.registerTypes<glm::vec2, glm::vec3, glm::vec4>();

        script.registerObject(this, "globalenvironment");

        registerServices(object->services, script);
    }

    /// Registers all the services into a script.
    void registerServices(ServiceManager &services, Script &script);
    
    void registerGlobal(std::string key, _PrivateScripting::LuaPrimitive value);

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
    void iterateTypes(ServiceManager &services, Script &script) {
        registerService<T>(services, script);
        iterateTypes<S, R...>(services, script);
    }

    template<typename T>
    void iterateTypes(ServiceManager &services, Script &script) {
        registerService<T>(services, script);
    }

    template<typename T>
    void registerService(ServiceManager &services, Script &script) {
        T *service = services.get<T>();
        script.registerObject(service, luaServiceName<T>);
    }
    std::map<std::string, _PrivateScripting::LuaPrimitive> globals;
    std::vector<Object *> objects;
    std::vector<Script *> scripts;
};

} // namespace

#endif
