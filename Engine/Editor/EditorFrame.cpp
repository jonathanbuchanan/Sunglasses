#include "EditorFrame.h"

BEGIN_EVENT_TABLE(EditorFrame, wxFrame)
    EVT_MENU(ID_Exit,  EditorFrame::exit)
    EVT_MENU(ID_About, EditorFrame::about)
END_EVENT_TABLE()

EditorFrame::EditorFrame(wxString title, wxPoint position, wxSize size) : wxFrame((wxFrame *)NULL, -1, title, position, size) {
    wxMenu *menuFile = new wxMenu;

    menuFile->Append(ID_About, wxT("&About..." ));
    menuFile->AppendSeparator();
    menuFile->Append(ID_Exit, wxT("E&xit" ));

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, wxT("&File" ));

    SetMenuBar( menuBar );

    CreateStatusBar();
    SetStatusText( wxT("Welcome to wxWidgets!" ));
}

void EditorFrame::exit(wxCommandEvent& WXUNUSED(event))
{
    Close( true );
}

void EditorFrame::about(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxT("This is a wxWidgets' Hello world sample"), wxT("About Hello World"), wxOK | wxICON_INFORMATION );
}
