#include <sunglasses/Graphics/RenderingPipeline.h>

#include <sunglasses/Graphics/Renderer.h>

namespace sunglasses {
namespace graphics {

RenderingPipeline::RenderingPipeline(std::initializer_list<const Renderer *> _passes) : passes(_passes) {

}

void RenderingPipeline::render() {
	for (const Renderer *r : passes)
		r->render();
}

}
}