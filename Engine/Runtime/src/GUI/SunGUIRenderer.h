// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef SUNGUIRENDERER_H
#define SUNGUIRENDERER_H

#include "../Core/SunNode.h"
#include "SunTextRenderer.h"

class SunGUIRenderer {
public:
	SunGUIRenderer();

	void render();

	inline void setGUIRoot(SunNode *g) { guiRoot = g; }

	inline void setTextRenderer(SunTextRenderer *t) { textRenderer = t; }
private:
	SunNode *guiRoot;
	SunTextRenderer *textRenderer;
};

#endif
