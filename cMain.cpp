#include "cMain.h"
#include <iostream>
#include <fstream>
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include "wx/dcclient.h"
#include "wx/dcmemory.h"
#include "wx/dcbuffer.h"

using namespace std;
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_MENU(10002, cMain::OnMenuOpen)
EVT_MENU(10003, cMain::OnMenuSave)
EVT_MENU(10004, cMain::OnMenuExit)
EVT_PAINT(cMain::OnPaint)
wxEND_EVENT_TABLE()


cMain::cMain() : wxFrame(nullptr, wxID_ANY,"Maplicator",wxPoint(10, 10),wxSize(600,800))
{	
	m_MenuBar = new wxMenuBar();
	this->SetMenuBar(m_MenuBar);
	wxInitAllImageHandlers();

	m_ToolBar = this->CreateToolBar(wxTB_VERTICAL, wxID_ANY);
	wxSize size(90, 10);
	m_ToolBar->SetToolBitmapSize(size);
	const int maxBTNS = 8; //this is easier to keep track of the amount of buttons.
	wxButton *btns[maxBTNS];
	btns[0] = new wxButton(m_ToolBar, 10101, "Temperature", wxDefaultPosition, wxDefaultSize, 0);
	btns[1] = new wxButton(m_ToolBar, 10102, "Elevation", wxDefaultPosition, wxDefaultSize, 0);
	btns[2] = new wxButton(m_ToolBar, 10103, "Area Denial", wxDefaultPosition, wxDefaultSize, 0);
	btns[3] = new wxButton(m_ToolBar, 10104, "Town/Settlement", wxDefaultPosition, wxDefaultSize, 0);

	btns[4] = new wxButton(m_ToolBar, 10105, "Area Of Importance", wxDefaultPosition, wxDefaultSize, 0);
	btns[5] = new wxButton(m_ToolBar, 10106, "Enemy Camps", wxDefaultPosition, wxDefaultSize, 0);
	btns[6] = new wxButton(m_ToolBar, 10107, "Dungeons", wxDefaultPosition, wxDefaultSize, 0);
	btns[7] = new wxButton(m_ToolBar, 10108, "Bosses", wxDefaultPosition, wxDefaultSize, 0);


	
	
	int btnWidth = 40;
	for (int i = 0; i < maxBTNS; i++) {
		wxButton* booton = btns[i];
		booton->SetSize(100, btnWidth);
		booton->SetPosition(wxPoint(0, (btnWidth * i)));
		booton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnSelectMapType), nullptr);
		booton->Disable();
		m_ToolBar->AddControl(booton);
		menuFile2->Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(cMain::OnImportClicked), menuFile2);
		menuFile2->Append(10010+i, booton->GetLabelText());
		m_ImageData->insert(make_pair(booton->GetLabelText(), wxBitmap()));

	}
	EnableDisableMenuItems(menuFile2, 10010, maxBTNS, false);
	//menuFile->Append(10001, "New");
	menuFile->Append(10002, "Open");
	menuFile->AppendSubMenu(menuFile2, "import");
	menuFile->Append(10003, "Save");
	menuFile->Append(10004, "Exit");
	m_MenuBar->Append(menuFile, "File");
	

}

void cMain::EnableDisableMenuItems(wxMenu* &menu, int startidentifier, int amnt, bool enable)
{
	for (int id = 0; id < amnt; id++) {
		menu->Enable(startidentifier + id, enable);
		wxColour color = enable ? wxColour(200, 200, 200) : wxColour(0, 0, 0);
		menu->FindItem(startidentifier + id)->SetTextColour(color);
	}
}

cMain::~cMain()
{

}

//void cMain::OnMenuNew(wxCommandEvent& evt)
//{
//	evt.Skip();
//} unused;

void cMain::OnMenuOpen(wxCommandEvent& evt)
{
	wxFileDialog dialogue(m_ToolBar, _("Main Map Image"), "", "", "Image Files files (*.png *.jpg *.tga)|*.png;*.jpg;*.tga", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (dialogue.ShowModal() == wxID_CANCEL)return;
	wxImage image(dialogue.GetPath());
	if (image.IsOk()) {
		m_MainImage = new wxBitmap(image);
		EnableDisableMenuItems(menuFile2, 10010, 8, true);
	} else {
		wxMessageBox(wxT("Warning: Image failed to initialize"), dialogue.GetPath(),SLE_WARNING);
	}
	evt.Skip();
}

void cMain::OnMenuSave(wxCommandEvent& evt)
{
	wxFileDialog
		saveFileDialog(this, _("Save XYZ file"), "", "",
			"Rpg Engine Map FIles files (*.REMF)|*.remf", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	// save the current contents in the file;
	// this can be done with e.g. wxWidgets output streams:
	wxFileOutputStream output_stream(saveFileDialog.GetPath());
	if (!output_stream.IsOk())
	{
		wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
		return;
	}
	output_stream.GetFile()->Write("sans");
	evt.Skip();

}

void cMain::OnMenuExit(wxCommandEvent& evt)
{
	Close();
	evt.Skip();
}

void cMain::OnSelectMapType(wxCommandEvent& evt)
{
}

void cMain::OnImportClicked(wxCommandEvent& evt) 
{
	
	//wxEventType string = evt.GetEventType();
	wxMenu* menu = wxDynamicCast(evt.GetEventObject(), wxMenu);
	wxMenuItem* item = menu->FindChildItem(evt.GetId());
	if (item != nullptr) {
		wxFileDialog dialogue(m_ToolBar, _(item->GetItemLabel()), "", "", "Image Files files (*.png *.jpg *.tga)|*.png;*.jpg;*.tga", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
		if (dialogue.ShowModal() == wxID_CANCEL)return;
		wxImage image(dialogue.GetPath());
		image = image.ConvertToGreyscale();
		(*m_ImageData)[item->GetItemLabel()] = image;
	}
	
	evt.Skip();
	return;
}

void cMain::OnDraw(wxDC& dc)
{
	dc.Clear();
	if (m_MainImage != nullptr) {
		wxBitmap image = *m_MainImage;
		
		dc.DrawBitmap(image, wxPoint(90 + image.GetSize().x, image.GetSize().y));
	}

}

void cMain::OnPaint(wxPaintEvent& evt)
{
	wxBufferedPaintDC dc(this);
	this->PrepareDC(dc);
	this->OnDraw(dc);
}
