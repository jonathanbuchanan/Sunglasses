#include "EditorApp.h"

bool EditorApp::OnInit() {
    EditorFrame *frame = new EditorFrame(wxT("Sunglasses Editor"), wxPoint(50,50), wxSize(450,340));
    frame->Show(true);
    SetTopWindow( frame );
    return true;
}
