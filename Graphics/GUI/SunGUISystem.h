//
//  SunGUISystem.h
//  Sunglasses
//
//  Created by Jonathan Buchanan on 6/12/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef Sunglasses_SunGUISystem_h
#define Sunglasses_SunGUISystem_h

#include <vector>
#include <string>

#include "../../Utility.h"

#include "../../pugixml.hpp"

#include "./SunGUIMenu.h"
#include "./SunGUIItem.h"

using namespace std;

struct SunGUIFont {
    string file;
    string name;
};

class SunGUISystem : public SunNode {
public:
    string name;
    
    vector<SunGUIFont> fonts;
    bool fontsLoaded = false;
    
    GLFWwindow *window;
    
    SunGUISystem() {
        initializeDefaultPropertyAndFunctionMap();
    }
    
    SunGUISystem(const char *filepath, GLFWwindow *_window, SunNode *_rootNode) {
        window = _window;
        setRootNode(_rootNode);
        
        initializeDefaultPropertyAndFunctionMap();
        
        pugi::xml_document document;
        document.load_file(filepath);
        
        pugi::xml_node system = document.child("GUISystem");
        
        for (pugi::xml_attribute attribute = system.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "name") == 0) {
                name = attribute.value();
            }
        }
        
        processXMLGUISystemNode(system);
    }
    
    virtual void initializeDefaultPropertyAndFunctionMap() {
        SunNode::initializeDefaultPropertyAndFunctionMap();
        
        // Add the "render" function to the function map
        addToFunctionMap("update", bind(&SunGUISystem::update, this, std::placeholders::_1));
        addToFunctionMap("render", bind(&SunGUISystem::render, this, std::placeholders::_1));
    }
    
    virtual void update(SunNodeSentAction _action) {
        // Loop through the sub-objects and force them to update
        sendActionToAllSubNodes(_action);
    }
    
    virtual void render(SunNodeSentAction _action) {
        glEnable(GL_BLEND);
        
        // Loop through the sub-objects and force them to render
        sendActionToAllSubNodes(_action);
        
        glDisable(GL_BLEND);
    }
    
    void loadFonts(SunTextRenderer *_textRenderer) {
        for (int i = 0; i < fonts.size(); i++) {
            _textRenderer->loadFont(fonts[i].file, fonts[i].name);
        }
        
        fontsLoaded = true;
    }
    
    void processXMLGUISystemNode(pugi::xml_node _node) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            if (strcmp(node.name(), "menus") == 0) {
                processXMLMenusNode(node);
            } else if (strcmp(node.name(), "fonts") == 0) {
                processXMLFontsNode(node);
            }
        }
    }
    
    void processXMLFontsNode(pugi::xml_node _node) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            if (strcmp(node.name(), "font") == 0)
                processXMLFontNode(node);
        }
    }
    
    void processXMLFontNode(pugi::xml_node _node) {
        SunGUIFont font;
        
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "file") == 0) {
                font.file = attribute.value();
            } else if (strcmp(attribute.name(), "name") == 0) {
                font.name = attribute.value();
            }
        }
        
        fonts.push_back(font);
    }
    
    void processXMLMenusNode(pugi::xml_node _node) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            if (strcmp(node.name(), "menu") == 0)
                processXMLMenuNode(node);
        }
    }
    
    void processXMLMenuNode(pugi::xml_node _node) {
        SunGUIMenu *menu = new SunGUIMenu();
        menu->window = window;
        
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "name") == 0) {
                menu->name = attribute.value();
            } else if (strcmp(attribute.name(), "visible") == 0) {
                menu->visible = attribute.as_bool();
            }
        }
        
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            if (strcmp(node.name(), "items") == 0) {
                processXMLItemsNode(node, menu);
            } else if (strcmp(node.name(), "actions") == 0) {
                processXMLMenuActionsNode(node, menu);
            }
        }
        
        addSubNode(menu);
    }
    
    void processXMLMenuActionsNode(pugi::xml_node _node, SunGUIMenu *_menu) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            if (strcmp(node.name(), "action") == 0)
                processXMLMenuActionNode(node, _menu);
        }
    }
    
    void processXMLMenuActionNode(pugi::xml_node _node, SunGUIMenu *_menu) {
        SunNodeSentAction action;
        
        string temporaryValue;
        
        vector<string> parameterKeys;
        vector<SunNodePropertyType> parameterValueTypes;
        vector<string> tempParameterValues;
        vector<void *> parameterValues;
        
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "trigger") == 0) {
                action.properties["trigger"] = new std::string(attribute.value());
            } else if (strcmp(attribute.name(), "target-path") == 0) {
                action.properties["target-path"] = new std::string(attribute.value());
                if (strcmp(attribute.value(), "@self") == 0)
                    action.properties["receiver"] = _menu;
            } else if (strcmp(attribute.name(), "action") == 0) {
                action.action = attribute.value();
            } else if (strcmp(attribute.name(), "targetProperty") == 0) {
                action.parameters["targetProperty"] = new std::string(attribute.value());
            } else if (strcmp(attribute.name(), "valueType") == 0) {
                action.properties["valueType"] = new std::string(attribute.value());
            } else if (strcmp(attribute.name(), "value") == 0) {
                temporaryValue = attribute.value();
            } else if (strcmp(attribute.name(), "parameterKeys") == 0) {
                parameterKeys = splitString(attribute.value(), *",");
            } else if (strcmp(attribute.name(), "parameterValueTypes") == 0) {
                vector<string> tempParameterValueTypes = splitString(attribute.value(), *",");
                for (int i = 0; i < tempParameterValueTypes.size(); i++) {
                    if (tempParameterValueTypes[i] == "vec3")
                        parameterValueTypes.push_back(SunNodePropertyTypeVec3);
                    else if (tempParameterValueTypes[i] == "bool")
                        parameterValueTypes.push_back(SunNodePropertyTypeBool);
                    else if (tempParameterValueTypes[i] == "string")
                        parameterValueTypes.push_back(SunNodePropertyTypeString);
                }
            } else if (strcmp(attribute.name(), "parameterValues") == 0) {
                tempParameterValues = splitString(attribute.value(), *",");
            }
        }
        
        for (int i = 0; i < tempParameterValues.size(); i++) {
            SunNodePropertyType type = parameterValueTypes[i];
            if (type == SunNodePropertyTypeString)
                parameterValues.push_back(new string(tempParameterValues[i]));
        }
        
        map<string, void *> parameterMap;
        
        for (int i = 0; i < parameterKeys.size(); i++) {
            parameterMap[parameterKeys[i]] = parameterValues[i];
        }
        
        for (SunNodeSentActionPropertyMapIterator iterator = parameterMap.begin(); iterator != parameterMap.end(); iterator++) {
            action.parameters[iterator->first] = iterator->second;
        }
        
        if (*(string *)action.properties["valueType"] == "vec3") {
            vector<string> values = splitString(temporaryValue, *",");
            
            action.parameters["value"] = new glm::vec3(stod(values[0]), stod(values[1]), stod(values[2]));
        }
        
        _menu->sentActions.push_back(action);
    }
    
    void processXMLItemsNode(pugi::xml_node _node, SunGUIMenu *_menu) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            processXMLItemNode(node, _menu);
        }
    }
    
    void processXMLItemNode(pugi::xml_node _node, SunGUIMenu *_menu) {
        SunGUIItem *item = new SunGUIItem();
        item->window = window;
        
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "name") == 0) {
                item->name = attribute.value();
            } else if (strcmp(attribute.name(), "button") == 0) {
                if (strcmp(attribute.value(), "true") == 0) {
                    item->isButton = true;
                } else if (strcmp(attribute.value(), "false") == 0) {
                    item->isButton = false;
                }
            }
        }
        
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            processXMLItemPropertyNode(node, item);
        }
        
        if (item->textured == true)
            item->loadTexture();
        
        _menu->addSubNode(item);
    }
    
    void processXMLItemPropertyNode(pugi::xml_node _node, SunGUIItem *_item) {
        if (strcmp(_node.name(), "text") == 0) {
            _item->text = _node.text().as_string();
        } else if (strcmp(_node.name(), "font") == 0) {
            _item->font = _node.text().as_string();
        } else if (strcmp(_node.name(), "width") == 0) {
            _item->size.x = _node.text().as_float();
        } else if (strcmp(_node.name(), "height") == 0) {
            _item->size.y = _node.text().as_float();
        } else if (strcmp(_node.name(), "x") == 0) {
            _item->position.x = _node.text().as_float();
        } else if (strcmp(_node.name(), "y") == 0) {
            _item->position.y = _node.text().as_float();
        } else if (strcmp(_node.name(), "r") == 0) {
            _item->color.r = _node.text().as_float();
        } else if (strcmp(_node.name(), "g") == 0) {
            _item->color.g = _node.text().as_float();
        } else if (strcmp(_node.name(), "b") == 0) {
            _item->color.b = _node.text().as_float();
        } else if (strcmp(_node.name(), "r-highlighted") == 0) {
            _item->highlightColor.r = _node.text().as_float();
        } else if (strcmp(_node.name(), "g-highlighted") == 0) {
            _item->highlightColor.g = _node.text().as_float();
        } else if (strcmp(_node.name(), "b-highlighted") == 0) {
            _item->highlightColor.b = _node.text().as_float();
        } else if (strcmp(_node.name(), "textured") == 0) {
            _item->textured = _node.text().as_bool();
        } else if (strcmp(_node.name(), "texturepath") == 0) {
            _item->texturePath = _node.text().as_string();
        } else if (strcmp(_node.name(), "actions") == 0) {
            processXMLItemActionsNode(_node, _item);
        }
    }
                   
    void processXMLItemActionsNode(pugi::xml_node _node, SunGUIItem *_item) {
        for (pugi::xml_node node = _node.first_child(); node; node = node.next_sibling()) {
            if (strcmp(node.name(), "action") == 0)
                processXMLItemActionNode(node, _item);
        }
    }
    
    void processXMLItemActionNode(pugi::xml_node _node, SunGUIItem *_item) {
        SunNodeSentAction action;
        
        string temporaryValue;
        
        vector<string> parameterKeys;
        vector<SunNodePropertyType> parameterValueTypes;
        vector<string> tempParameterValues;
        vector<void *> parameterValues;
        
        for (pugi::xml_attribute attribute = _node.first_attribute(); attribute; attribute = attribute.next_attribute()) {
            if (strcmp(attribute.name(), "trigger") == 0) {
                action.properties["trigger"] = new std::string(attribute.value());
            } else if (strcmp(attribute.name(), "target-path") == 0) {
                action.properties["target-path"] = new std::string(attribute.value());
                if (strcmp(attribute.value(), "@self") == 0)
                    action.properties["receiver"] = _item;
            } else if (strcmp(attribute.name(), "action") == 0) {
                action.action = attribute.value();
            } else if (strcmp(attribute.name(), "targetProperty") == 0) {
                action.parameters["targetProperty"] = new std::string(attribute.value());
            } else if (strcmp(attribute.name(), "valueType") == 0) {
                action.properties["valueType"] = new std::string(attribute.value());
            } else if (strcmp(attribute.name(), "value") == 0) {
                temporaryValue = attribute.value();
            } else if (strcmp(attribute.name(), "parameterKeys") == 0) {
                parameterKeys = splitString(attribute.value(), *",");
            } else if (strcmp(attribute.name(), "parameterValueTypes") == 0) {
                vector<string> tempParameterValueTypes = splitString(attribute.value(), *",");
                for (int i = 0; i < tempParameterValueTypes.size(); i++) {
                    if (tempParameterValueTypes[i] == "vec3")
                        parameterValueTypes.push_back(SunNodePropertyTypeVec3);
                    else if (tempParameterValueTypes[i] == "bool")
                        parameterValueTypes.push_back(SunNodePropertyTypeBool);
                    else if (tempParameterValueTypes[i] == "string")
                        parameterValueTypes.push_back(SunNodePropertyTypeString);
                }
            } else if (strcmp(attribute.name(), "parameterValues") == 0) {
                tempParameterValues = splitString(attribute.value(), *",");
            }
        }
        
        for (int i = 0; i < tempParameterValues.size(); i++) {
            SunNodePropertyType type = parameterValueTypes[i];
            if (type == SunNodePropertyTypeString)
                parameterValues.push_back(new string(tempParameterValues[i]));
        }
        
        map<string, void *> parameterMap;
        
        for (int i = 0; i < parameterKeys.size(); i++) {
            parameterMap[parameterKeys[i]] = parameterValues[i];
        }
        
        for (SunNodeSentActionPropertyMapIterator iterator = parameterMap.begin(); iterator != parameterMap.end(); iterator++) {
            action.parameters[iterator->first] = iterator->second;
        }
        
        if (*(string *)action.properties["valueType"] == "vec3") {
            vector<string> values = splitString(temporaryValue, *",");
            
            action.parameters["value"] = new glm::vec3(stod(values[0]), stod(values[1]), stod(values[2]));
        }
        
        _item->sentActions.push_back(action);
    }
    
    void mapSentActionTargets() {
        for (int i = 0; i < getSubNodesSize(); ++i) {
            if (dynamic_cast<SunGUIMenu *>(getSubNodeAtIndex(i)) != NULL) {
                for (int j = 0; j < ((SunGUIMenu *)getSubNodeAtIndex(i))->sentActions.size(); ++j) {
                    SunNodeSentAction *action = &((SunGUIMenu *)getSubNodeAtIndex(i))->sentActions[j];
                    
                    SunNode target;
                    
                    string targetPath = *(string *)action->properties["target-path"];
                    
                    if (targetPath != "@self") {
                        getRootNode()->findNode(targetPath, target);
                        
                        ((SunGUIMenu *)getSubNodeAtIndex(i))->sentActions[j].properties["receiver"] = getRootNode();
                    }
                }
                
                for (int j = 0; j < ((SunGUIMenu *)getSubNodeAtIndex(i))->getSubNodesSize(); ++j) {
                    if (dynamic_cast<SunGUIItem *>(getSubNodeAtIndex(i)->getSubNodeAtIndex(j))) {
                        for (int k = 0; k < ((SunGUIItem *)getSubNodeAtIndex(i)->getSubNodeAtIndex(j))->sentActions.size(); ++k) {
                            SunNodeSentAction *action = &((SunGUIItem *)getSubNodeAtIndex(i)->getSubNodeAtIndex(i))->sentActions[k];
                            
                            SunNode *target;
                            
                            string targetPath = *(string *)action->properties["target-path"];
                            
                            if (targetPath != "@self") {
                                getRootNode()->findNode(*(string *)action->properties["target-path"], target);
                                
                                ((SunGUIItem *)getSubNodeAtIndex(i)->getSubNodeAtIndex(j))->sentActions[k].properties["receiver"] = target;
                            }
                        }
                    }
                }
            }
        }
    }
    
private:
    
};

#endif
