// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef BUTTON_H
#define BUTTON_H

#include <sunglasses/GUI/Panel.h>
#include <sunglasses/GUI/Drawable.h>
#include <sunglasses/GUI/Renderer2D.h>

#include <functional>
#include <vector>

namespace sunglasses {
namespace GUI {

/// A button in the GUI
template<typename T, typename S, typename R>
class Button : public Control {
public:
    /// An event class
    /**
     * This class holds actions that can be executed by a button.
     */
    class Action {
    public:
        /// Constructs the event with a callback
        Action(Event _event, std::function<void()> &&_callback) :
                event(_event), callback(_callback) {

        }

        /// Calls the callback if the change matches the event
        void change(Event change) {
            if (event == change)
                callback();
        }
    private:
        /// The event type of the event
        Event event;

        /// The callback for the event
        std::function<void()> callback;
    };

    /// Constructs the button with three different backgrounds
    Button(glm::ivec2 _position, glm::ivec2 _size, const T &_normalBackground,
            const S &_highlightedBackground, const R &_selectedBackground) :
            Control(_position, _size), normalBackground(_normalBackground),
            highlightedBackground(_highlightedBackground), selectedBackground(_selectedBackground) {
        addAction(Event::Select, [](){std::cout<<"HI"<<std::endl;});
    }

    /// Adds an event to the button
    void addAction(Event event, std::function<void()> &&function) {
        actions.emplace_back(event, function);
    }

    /// Adds an event to button
    template<typename F>
    void addAction(Event event, F function) {
        actions.emplace_back(event, std::function<void()>(function));
    }

    /// The background for the 'normal' state
    T normalBackground;

    /// The background for the 'highlighted' state
    S highlightedBackground;

    /// The background for the 'selected' state
    R selectedBackground;
protected:
    /// Draws the button
    virtual void draw(glm::ivec2 offset, Renderer2D &renderer) {
        switch (state) {
        case State::Normal:
            normalBackground.draw(offset + position, size, renderer);
            break;
        case State::Highlighted:
            highlightedBackground.draw(offset + position, size, renderer);
            break;
        case State::Selected:
            selectedBackground.draw(offset + position, size, renderer);
            break;
        }
    }

    /// Updates the button
    virtual void update(glm::ivec2 offset, UpdateInfo updateInfo) {

    }

    /// Called when the button's state changes
    virtual void event(Event event) {
        for (auto &action : actions)
            action.change(event);
    }
private:
    /// The list of events
    std::vector<Action> actions;
};

/// A 'basic' button
using BasicButton = Button<Drawable::Color, Drawable::Color, Drawable::Color>;

} // namespace
} // namespace

#endif
