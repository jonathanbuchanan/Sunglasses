// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef RENDERER_H
#define RENDERER_H

namespace sunglasses {
namespace graphics {

/// An abstract class representing a pass in the drawing pipeline to derive other renderers from
class Renderer {
public:
	/// Renders a set of items known by the renderer into its framebuffer
	virtual void render() const = 0;
private:

};

} // namespace
} // namespace

#endif
