// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef VIEW_H
#define VIEW_H

#include <glm/glm.hpp>

#include <sunglasses/GUI/Window.h>
#include <sunglasses/GUI/Drawable.h>

#include <vector>
#include <memory>

namespace sunglasses {
namespace GUI {

class ViewController;
class Renderer;

/// The state of a control
enum class ControlState {
    Normal,
    Highlighted,
    Selected
};

/// A view in the GUI toolkit
class View {
friend ViewController;
public:
    /// Constructs the view
    View(glm::ivec2 _position,
        glm::ivec2 _size,
        const Drawable &_drawable,
        bool _visible = true);

    /// Updates all the sub-views and updates this view
    /**
     * @param parentPosition The absolute position of the parent view
     * @param info The info used to update the view
     */
    void updateTree(glm::ivec2 parentPosition, UpdateInfo info);

    /// Draws all the sub-views and draws this view
    /**
     * @param parentPosition The absolute position of the parent view
     * @param renderer The object used to draw the view
     */
    virtual void drawTree(glm::ivec2 parentPosition, Renderer &renderer);

    /// Adds a subview
    void addSubview(View *subview);

    /// The position of the view (In pixels, not NDC)
    glm::ivec2 position;

    /// The size of the view (In pixels, not NDC)
    glm::ivec2 size;
protected:
    /// Updates the view
    virtual void update(/*glm::ivec2 parentPosition, UpdateInfo info*/);

    /// Draws the view
    virtual void draw(glm::ivec2 parentPosition, Renderer &renderer);

    /// The drawable (a solid color, image, etc.)
    std::unique_ptr<Drawable> drawable;

    /// The visibility of the view
    bool visible;

    /// The state of the control
    ControlState state;
private:
    /// The vector of sub-views
    std::vector<View *> subviews;
};

} // namespace
} // namespace

#endif
