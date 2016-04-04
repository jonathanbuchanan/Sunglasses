#ifndef SUNSHADOWMAPPER_H
#define SUNSHADOWMAPPER_H

#include "../Graphics/SunRenderNode.h"

class SunShadowMapper : public SunRenderNode {
public:
    /// Constructs the shadow mapper with a target.
    /**
     * @param _target The target of the shadow mapper
     */
    SunShadowMapper(SunBase *_target);

    virtual void render(SunAction action);

    virtual void bindOutputs(SunAction action);
private:
    /// This is the target of the render node. This is usually the root node of the scene.
    SunBase *target;
};

#endif
