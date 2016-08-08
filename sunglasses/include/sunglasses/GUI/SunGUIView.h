// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUIVIEW_H
#define SUNGUIVIEW_H

#include <glm/glm.hpp>

#include <sunglasses/GUI/SunGUIWindow.h>
#include <sunglasses/GUI/SunGUIDrawable.h>

#include <vector>
#include <memory>

class SunGUIViewController;
class SunGUIRenderer;

/// The state of a control
enum class SunGUIControlState {
    Normal,
    Highlighted,
    Selected
};

/// A view in the GUI toolkit
class SunGUIView {
friend SunGUIViewController;
public:
    /// Constructs the view
    SunGUIView(glm::ivec2 _position,
        glm::ivec2 _size,
        const SunGUIDrawable &_drawable,
        bool _visible = true);

    /// Updates all the sub-views and updates this view
    /**
     * @param parentPosition The absolute position of the parent view
     * @param info The info used to update the view
     */
    void updateTree(glm::ivec2 parentPosition, SunGUIUpdateInfo info);

    /// Draws all the sub-views and draws this view
    /**
     * @param parentPosition The absolute position of the parent view
     * @param renderer The object used to draw the view
     */
    virtual void drawTree(glm::ivec2 parentPosition, SunGUIRenderer &renderer);

    /// Adds a subview
    void addSubview(SunGUIView *subview);

    /// The position of the view (In pixels, not NDC)
    glm::ivec2 position;

    /// The size of the view (In pixels, not NDC)
    glm::ivec2 size;
protected:
    /// Updates the view
    virtual void update(glm::ivec2 parentPosition, SunGUIUpdateInfo info);

    /// Draws the view
    virtual void draw(glm::ivec2 parentPosition, SunGUIRenderer &renderer);

    /// The drawable (a solid color, image, etc.)
    std::unique_ptr<SunGUIDrawable> drawable;

    /// The visibility of the view
    bool visible;

    /// The state of the control
    SunGUIControlState state;
private:
    /// The vector of sub-views
    std::vector<SunGUIView *> subviews;
};

#endif
