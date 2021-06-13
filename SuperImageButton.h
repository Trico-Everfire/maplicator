#pragma once
#include "wx/wx.h"

enum ButtonType {
	PaintMap,
	PinMap
};

class SuperImageButton : public wxButton
{
	wxImage* b_Image = nullptr;
	ButtonType* b_ButtonType = nullptr;

	SuperImageButton(wxWindow* parent,
		wxWindowID id,
		const wxString& label = wxEmptyString,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxValidator& validator = wxDefaultValidator,
		const wxString& name = wxASCII_STR(wxButtonNameStr), wxImage* image, ButtonType* bt);


	void setImage(wxImage image);
	void setButtonType(ButtonType buttonType);

};

