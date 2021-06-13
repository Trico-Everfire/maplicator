#pragma once
#include "wx/wx.h"
#include "wx/vscroll.h"

class cCanvas : public wxHVScrolledWindow
{
public:
	cCanvas(wxWindow *parent);
	~cCanvas();

private:
	int m_pixelSize = 1080;
public:
	void setPixelSize(int n);

private:
	virtual wxCoord OnGetRowHeight(size_t row) const;
	virtual wxCoord OnGetColumnWidth(size_t col) const;

	void OnDraw(wxDC& dc);
	void OnPaint(wxPaintEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

