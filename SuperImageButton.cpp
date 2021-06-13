#include "SuperImageButton.h"


class SuperImageButton : wxButton
{
	SuperImageButton(wxWindow* parent,
		wxWindowID id,
		const wxString& label = wxEmptyString,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxValidator& validator = wxDefaultValidator,
		const wxString& name = wxASCII_STR(wxButtonNameStr), wxImage* image, ButtonType* bt) : wxButton(parent,id,label,pos,size,style,validator,name) 
	{
		b_Image = image;
		b_ButtonType = bt;
	}
};
