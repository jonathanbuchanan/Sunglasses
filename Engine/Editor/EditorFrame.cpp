#include "EditorFrame.h"

BEGIN_EVENT_TABLE(EditorFrame, wxFrame)
    EVT_MENU(ID_Exit,  EditorFrame::onExit)
    EVT_MENU(ID_NewProject, EditorFrame::onNewProject)
END_EVENT_TABLE()

EditorFrame::EditorFrame(wxString title, wxPoint position, wxSize size) : wxFrame((wxFrame *)NULL, -1, title, position, size) {
    wxMenu *menuFile = new wxMenu;
    
    menuFile->Append(ID_Exit, wxT("E&xit" ));

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, wxT("&File" ));

    SetMenuBar( menuBar );

    CreateStatusBar();
    SetStatusText( wxT("Welcome to wxWidgets!" ));
    
    newProject = new wxButton(this, wxID_ANY, wxT("New Project"), wxPoint(0, 0), wxSize(50, 50));
    newProject->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EditorFrame::onNewProject), NULL, this);
}

void EditorFrame::onExit(wxCommandEvent& event) {
    Close( true );
}

void EditorFrame::onNewProject(wxCommandEvent &event) {
	wxDirDialog *directory = new wxDirDialog(this, wxT("Choose Directory for Project"), wxT("/"), wxDD_DEFAULT_STYLE, wxPoint(0, 0), wxSize(500, 500), wxT("Select"));
	directory->ShowModal();
	wxMessageBox(wxT("You Chose: " + directory->GetPath()));
}
