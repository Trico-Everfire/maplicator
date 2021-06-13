#pragma once
#include "wx/wx.h"
#include "cCanvas.h"

class cMapFrame : public wxMDIChildFrame
{
public:
	cMapFrame(wxMDIParentFrame* parent, wxString sName);
	~cMapFrame();

private:
	cCanvas* m_Canvas = nullptr;
	wxStatusBar* m_StatusBar = nullptr;
	wxSlider* m_ZoomSlider = nullptr;

	void OnZoomChange(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

