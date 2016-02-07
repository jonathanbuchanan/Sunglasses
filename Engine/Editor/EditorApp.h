// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#ifndef EDITORAPP_H
#define EDITORAPP_H

#include <wx/wx.h>
#include <string>
#include "EditorFrame.h"

class EditorApp : public wxApp {
public:
	virtual bool OnInit();
};

IMPLEMENT_APP(EditorApp)

#endif
