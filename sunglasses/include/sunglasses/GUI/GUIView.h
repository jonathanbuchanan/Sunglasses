// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef GUIVIEW_H
#define GUIVIEW_H

#include <glm/glm.hpp>

#include <sunglasses/GUI/GUIWindow.h>
#include <sunglasses/GUI/GUIDrawable.h>

#include <vector>
#include <memory>

namespace sunglasses {

class GUIViewController;
class GUIRenderer;

/// The state of a control
enum class GUIControlState {
    Normal,
    Highlighted,
    Selected
};

/// A view in the GUI toolkit
class GUIView {
friend GUIViewController;
public:
    /// Constructs the view
    GUIView(glm::ivec2 _position,
        glm::ivec2 _size,
        const GUIDrawable &_drawable,
        bool _visible = true);

    /// Updates all the sub-views and updates this view
    /**
     * @param parentPosition The absolute position of the parent view
     * @param info The info used to update the view
     */
    void updateTree(glm::ivec2 parentPosition, GUIUpdateInfo info);

    /// Draws all the sub-views and draws this view
    /**
     * @param parentPosition The absolute position of the parent view
     * @param renderer The object used to draw the view
     */
    virtual void drawTree(glm::ivec2 parentPosition, GUIRenderer &renderer);

    /// Adds a subview
    void addSubview(GUIView *subview);

    /// The position of the view (In pixels, not NDC)
    glm::ivec2 position;

    /// The size of the view (In pixels, not NDC)
    glm::ivec2 size;
protected:
    /// Updates the view
    virtual void update(glm::ivec2 parentPosition, GUIUpdateInfo info);

    /// Draws the view
    virtual void draw(glm::ivec2 parentPosition, GUIRenderer &renderer);

    /// The drawable (a solid color, image, etc.)
    std::unique_ptr<GUIDrawable> drawable;

    /// The visibility of the view
    bool visible;

    /// The state of the control
    GUIControlState state;
private:
    /// The vector of sub-views
    std::vector<GUIView *> subviews;
};

} // namespace

#endif
