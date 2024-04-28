#pragma once
#include "MyLibrary.h"
#include "vecmat.h"

class MyCustomPanel : public wxPanel {
public:
	MyCustomPanel(wxWindow* parent);
	void OnPaint(wxPaintEvent& event);

private:
	
	DECLARE_EVENT_TABLE()
};

const wxColour TAB_COLOR[4] = {
	wxColour(255, 0, 0),
	wxColour(0, 128, 128),
	wxColour(0, 0, 0),
	wxColour(128, 128, 0)
};

void DrawLine2d(wxPaintDC* dc, Matrix M, double x_1, double y_1, double x2, double y2);
