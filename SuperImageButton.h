#pragma once
#include "wx/wx.h"

enum ButtonType {
	PaintMap,
	PinMap
};

class SuperImageButton : public wxButton
{
public:
	SuperImageButton(wxWindow* parent,
		wxWindowID id,
		const wxString& label = wxEmptyString,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxValidator& validator = wxDefaultValidator,
		const wxString& name = wxASCII_STR(wxButtonNameStr), ButtonType btnType = ButtonType::PaintMap, wxImage* image = nullptr);
	~SuperImageButton();
public:
	wxImage* b_Image = nullptr;
	ButtonType* b_ButtonType = nullptr;
	void setImage(wxImage* image);
	void setButtonType(ButtonType* buttonType);
	wxBitmap* CreateValuedBitmap(float value, int w, int h);
	void setDefaultImage(wxSize size);

};
