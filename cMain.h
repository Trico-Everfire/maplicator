
#include "wx/wx.h"
#include "cMapFrame.h"
#include <map>
using namespace std;

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	
	wxToolBar* m_ToolBar = nullptr;
	wxMenuBar* m_MenuBar = nullptr;
	map<wxString, wxBitmap>* m_ImageData = new map<wxString, wxBitmap>;
	wxBitmap* m_MainImage = nullptr;
	wxString* m_currentMapType = nullptr;

	void OnMenuNew(wxCommandEvent& evt);
	void OnMenuOpen(wxCommandEvent& evt);
	void OnMenuSave(wxCommandEvent& evt);
	void OnMenuExit(wxCommandEvent& evt);

	void OnDraw(wxDC& dc);
	void OnPaint(wxPaintEvent& evt);

	void OnSelectMapType(wxCommandEvent& evt);
	void OnImportClicked(wxCommandEvent& evt);
	void EnableDisableMenuItems(wxMenu*& menu, int startidentifier, int amnt, bool enable);
	void EnableDisableToolbarItems(wxToolBar*& menu, int startidentifier, int amnt, bool enable);
	wxMenu* menuFile2 = new wxMenu();
	wxMenu* menuFile = new wxMenu();


	wxDECLARE_EVENT_TABLE();


};
