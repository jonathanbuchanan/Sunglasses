// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunGUIMenu.h"
#include "../Scripting/SunGlobalScriptingEnvironment.h"
#include "../Graphics/SunWindowManager.h"

template<> const std::string SunLuaTypeRegistrar<SunGUIMenu>::typeName = "Menu";
template<> const std::map<std::string, SunScripting::SunLuaTypeDataMemberBase<SunGUIMenu> *> SunLuaTypeRegistrar<SunGUIMenu>::dataMembers = {
    {"visible", new SunLuaTypeDataMember<bool, SunGUIMenu>("visible", &SunGUIMenu::visible)}
};

SunGUIMenu::SunGUIMenu() {

}

void SunGUIMenu::init() {
    addAction("render", &SunGUIMenu::render);
    addAction("key", &SunGUIMenu::key);
}

void SunGUIMenu::loadScript(std::string _script) {
    script.loadFile(_script);
    services.get<SunGlobalScriptingEnvironment>()->registerScript(this, script);
    //script.registerObject("menu", this, "visible", &SunGUIMenu::visible);
    script.registerType<SunGUIMenu>();
    script.registerObject(this, "menu");
}

void SunGUIMenu::render(SunAction action) {
    if (visible)
        sendActionToAllSubNodes(action);
}

void SunGUIMenu::key(SunAction action) {
    int key = action.getParameter<int>("key");
    script["keyPressed"](key);
}
