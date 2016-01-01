#ifndef EDITORFRAME_H
#define EDITORFRAME_H

#include <wx/wxprec.h>
#include <wx/wx.h>

class EditorFrame : public wxFrame {
public:
	EditorFrame(wxString title, wxPoint position, wxSize size);
	
	wxButton *newProject;
	
	void onExit(wxCommandEvent &event);
	void onNewProject(wxCommandEvent &event);
	
	enum {
		ID_Exit = 1,
		ID_NewProject,
	};
	
private:
	DECLARE_EVENT_TABLE()
};

#endif
