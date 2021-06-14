#include "SuperImageButton.h"
#include <wx/rawbmp.h>


SuperImageButton::SuperImageButton(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator, const wxString& name, ButtonType btnType, wxImage* image) : wxButton(parent,id,label,pos,size,style,validator,name)
{
	b_Image = image;
	b_ButtonType = &btnType;
}

SuperImageButton::~SuperImageButton()
{
//	if (b_Image == nullptr) {
//		float value = *b_ButtonType == ButtonType::PaintMap ? 255 / 2 : 0;
//		wxBitmap map = *CreateValuedBitmap(value, 200, 200);
	//	wxImage imagee = map.ConvertToImage();
	//	b_Image = &imagee;
//	}
}

void SuperImageButton::setImage(wxImage* image)
{
	b_Image = image;
}

void SuperImageButton::setDefaultImage(wxSize size) {
	if (b_Image == nullptr) {
		float value;
		if (*b_ButtonType == ButtonType::PaintMap) value = 255 / 2;else value = 0;
		wxBitmap map = *CreateValuedBitmap(value, size.x, size.y);
		wxImage* imagee = new wxImage(map.ConvertToImage());
		imagee->SetRGB(wxRect(0, 0, size.x, size.y), 0, 0, 255);
		// map.ConvertToImage();
		b_Image = imagee;
	}
}

void SuperImageButton::setButtonType(ButtonType* buttonType)
{
	b_ButtonType = buttonType;
}

typedef wxAlphaPixelData PixelData;
wxBitmap* SuperImageButton::CreateValuedBitmap(float value,int w, int h)
{
	wxBitmap* bitmap = new wxBitmap(w, h, 32);
	if (!bitmap->Ok()) {
		delete bitmap;
		return nullptr;
	}

	PixelData bmdata(*bitmap);
	if (bmdata == NULL) {
		wxLogDebug(wxT("getBitmap() failed"));
		delete bitmap;
		return nullptr;
	}

	PixelData::Iterator dst(bmdata);

	for (int y = 0; y < h; y++) {
		dst.MoveTo(bmdata, 0, y);
		for (int x = 0; x < w; x++) {
			// wxBitmap contains rgb values pre-multiplied with alpha
			dst.Red() = value;
			dst.Green() = value;
			dst.Blue() = value;
			dst.Alpha() = 255;
			dst++;
		}
	}
	return bitmap;
}
