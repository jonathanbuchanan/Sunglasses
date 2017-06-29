#ifndef IMAGEPANEL_H
#define IMAGEPANEL_H

#include <sunglasses/GUI/Control.h>
#include <sunglasses/Graphics/2D/TexturedRectangle.h>
namespace sunglasses {
namespace GUI {

/// An image panel in the GUI toolkit
/**
 * An image panel is a control that displays a textured rectangle.
 */
class ImagePanel : public Control {
public:
	/// Constructs the image panel
	ImagePanel(glm::ivec2 position, glm::ivec2 size,
		graphics::TexturedRectangle _background, bool visible = true);
		
	graphics::TexturedRectangle background;
private:

};

} // namespace
} // namespace

#endif
