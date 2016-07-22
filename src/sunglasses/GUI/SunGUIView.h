// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUIVIEW_H
#define SUNGUIVIEW_H

#include <glm/glm.hpp>

#include <sunglasses/GUI/SunGUIWindow.h>

#include <vector>

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
        glm::vec4 color,
        bool _visible = true);

    /// Updates the view from the position of the cursor
    /**
     * @param parentPosition The absolute position of the parent view
     * @param info The info used to update the view
     */
    virtual void update(glm::ivec2 parentPosition, SunGUIUpdateInfo info);

    /// Draws the view
    /**
     * For any SunGUIView, this only draws the background color in
     * the area covered by the view and draws all of the subviews.
     * Custom drawing functionality should be provided by overriding
     * this method.
     * @param parentPosition The absolute position of the parent view
     * @param renderer The object used to draw the view
     */
    virtual void draw(glm::ivec2 parentPosition, SunGUIRenderer &renderer);

    /// Adds a subview
    void addSubview(SunGUIView *subview);
protected:
    /// The position of the view (In pixels, not NDC)
    glm::ivec2 position;

    /// The size of the view (In pixels, not NDC)
    glm::ivec2 size;

    /// The background color of the view
    glm::vec4 backgroundColor;

    /// The visibility of the view
    bool visible;

    /// The state of the control
    SunGUIControlState state;
private:
    /// The vector of sub-views
    std::vector<SunGUIView *> subviews;
};

#endif
