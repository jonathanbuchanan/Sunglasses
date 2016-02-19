// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef Sunglasses_SunNode_h
#define Sunglasses_SunNode_h

#include "Core/SunBase.h"
#include "SunService.h"
#include <vector>
#include <string>
#include <map>
#include "./Utility.h"
#include <functional>

class SunNode : public SunBase { 
public:
	virtual void processAction(SunAction action);


    virtual void sendActionToAllSubNodes(SunAction action);

    virtual void addSubNode(SunNode *_subNode);
    
    virtual void findNode(string _path, SunNode &_node);
    
    virtual void findNode(string _path, SunNode *&_node);
    
    virtual void findNodeWithName(string _name, SunNode &_node);
    
    virtual void findPointerNodeWithName(string _name, SunNode *&_node);
        
    inline vector<SunNode *> & getSubNodes() { return subNodes; }
    inline int getSubNodesSize() { return subNodes.size(); }
    inline SunNode * getSubNodeAtIndex(int i) { return subNodes[i]; }
    
    inline int getLevel() { return level; }
    inline void setLevel(int _level) { level = _level; }
    
	// Tags
	inline void addTag(std::string t) { tags.push_back(t); }
	inline bool tagPresent(std::string t) { return (std::find(tags.begin(), tags.end(), t) != tags.end()) ? true : false; } 

    inline SunNode * getRootNode() { return rootNode; }
    inline void setRootNode(SunNode *_rootNode) { rootNode = _rootNode; }
    
    inline vector<SunNode *> & getParents() { return parents; }
    inline int getParentsSize() { return parents.size(); }
    inline SunNode * getParentAtIndex(int i) { return parents[i]; }
private:
    GLuint parentsReady = 0;
    vector<SunNode *> subNodes;
    vector<SunNode *> parents;
    int level = 0; 

	// Tags
	std::vector<std::string> tags;

    SunNode *rootNode;
};

#endif
