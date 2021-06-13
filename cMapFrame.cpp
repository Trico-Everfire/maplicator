#include "cMapFrame.h"

wxBEGIN_EVENT_TABLE(cMapFrame, wxMDIChildFrame)
EVT_SLIDER(20001, cMapFrame::OnZoomChange)
wxEND_EVENT_TABLE()

cMapFrame::cMapFrame(wxMDIParentFrame* parent, wxString sName) : wxMDIChildFrame(parent,wxID_ANY,sName)
{
	m_Canvas = new cCanvas(this);

	m_StatusBar = this->CreateStatusBar(2, wxSTB_DEFAULT_STYLE, wxID_ANY);
	m_ZoomSlider = new wxSlider(m_StatusBar, 20001, 1, 1, 1080);
}

cMapFrame::~cMapFrame()
{
}

void cMapFrame::OnZoomChange(wxCommandEvent& evt)
{
	m_StatusBar->SetStatusText(wxString("Zoom: ") << m_ZoomSlider->GetValue(), 1);
	m_Canvas->setPixelSize(m_ZoomSlider->GetValue());
	evt.Skip();
}
