/* 
 * File:   SunRenderingNode.h
 * Author: jonathan
 *
 * Created on July 17, 2015, 12:39 AM
 */

#include <map>

#include "../SunNode.h"

#ifndef SunRenderingNode_h
#define	SunRenderingNode_h

using namespace std;

class SunRenderingNode;

typedef SunRenderingNode * SunRenderingNodePointer;

enum SunRenderingNodeType {
    SunRenderingNodeTypeDisplayOutput,
    SunRenderingNodeTypeBuffer
};

class SunRenderingNode : SunNode {
public:
    SunRenderingNodeType type;
    map<string, SunRenderingNodePointer> inputs;
    
private:
    
};

#endif

