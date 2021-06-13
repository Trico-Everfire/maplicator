#include "cCanvas.h"

#include "wx/dcclient.h"
#include "wx/dcmemory.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(cCanvas, wxHVScrolledWindow)
EVT_PAINT(cCanvas::OnPaint)
wxEND_EVENT_TABLE()

cCanvas::cCanvas(wxWindow* parent) : wxHVScrolledWindow(parent,wxID_ANY)
{
    SetRowColumnCount(1080, 1080);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

cCanvas::~cCanvas()
{
}

void cCanvas::setPixelSize(int n)
{
    m_pixelSize = n;
    wxVarHScrollHelper::RefreshAll();
    wxVarVScrollHelper::RefreshAll();
    Refresh();
}



wxCoord cCanvas::OnGetRowHeight(size_t row) const
{
    return wxCoord(m_pixelSize);
}

wxCoord cCanvas::OnGetColumnWidth(size_t col) const
{
    return wxCoord(m_pixelSize);
}

void cCanvas::OnDraw(wxDC& dc)
{
    dc.Clear();
    wxBrush brush = dc.GetBrush();
    wxPen pen = dc.GetPen();

    wxPosition s = GetVisibleBegin();
    wxPosition e = GetVisibleEnd();

    pen.SetStyle(wxPENSTYLE_LONG_DASH);
    pen.SetColour(wxColour(200, 200, 200));
    dc.SetPen(pen);
/*
            for (int y = s.GetRow(); y < e.GetRow(); y++) 
                for (int x = s.GetCol(); x < e.GetCol(); x++) {
                    dc.SetBrush(brush);
                    dc.DrawRectangle(x*m_pixelSize, y*m_pixelSize, m_pixelSize, m_pixelSize);
                }
  */ 

}

void cCanvas::OnPaint(wxPaintEvent& evt)
{
    wxBufferedPaintDC dc(this);
    this->PrepareDC(dc);
    this->OnDraw(dc);
}
