// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "EditorApp.h"

bool EditorApp::OnInit() {
    EditorFrame *frame = new EditorFrame(wxT("Sunglasses Editor"), wxPoint(50,50), wxSize(450,340));
    frame->Show(true);
    SetTopWindow( frame );
    return true;
}
