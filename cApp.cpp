#include "cApp.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{
}

cApp::~cApp()
{
}

bool cApp::OnInit()
{

	m_frame1 = new cMain();
	m_frame1->SetIcon(wxIcon(wxIconLocation("./icon/Tarmsworth.ico")));
	m_frame1->Show();
	return true;
}
