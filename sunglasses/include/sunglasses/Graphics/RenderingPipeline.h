#ifndef RENDERINGPIPELINE_H
#define RENDERINGPIPELINE_H

#include <vector>

namespace sunglasses {
namespace graphics {

class Renderer;

/// An object representing an ordered list of renderers
class RenderingPipeline {
public:
	/// Constructs the pipeline
	RenderingPipeline(std::initializer_list<const Renderer *> _passes);
	
	/// Renders all the renderers in order
	void render();
private:
	/// The vector of renderers to be used
	const std::vector<const Renderer *> passes;
};

}
}

#endif
