#include <sunglasses/GUI/ImagePanel.h>

namespace sunglasses {
namespace GUI {

ImagePanel::ImagePanel(glm::ivec2 position, glm::ivec2 size,
	graphics::TexturedRectangle _background, bool visible) :
		Control(position, size, visible), background(_background) {
		
}

} // namespace
} // namespace