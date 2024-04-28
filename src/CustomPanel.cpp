#include "MyLibrary.h"
#include "CustomPanel.h"
#include "vecmat.h"
#include <cstring>
#include <cmath>
#include "exprtk.hpp"


MyCustomPanel::MyCustomPanel(wxWindow* parent) : wxPanel(parent) {
	Bind(wxEVT_PAINT, &MyCustomPanel::OnPaint, this);
}

void MyCustomPanel::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this); 

    dc.Clear();

    dc.SetPen(*wxRED_PEN);
    dc.SetClippingRegion(10, 10, GetSize().x - 20, GetSize().y - 20);
    dc.DrawRectangle(10, 10, GetSize().x - 20, GetSize().y - 20);

    const double step = (x_1 - x_0) / 50;
    const double disX = (x_1 + x_0) / 2, disY = (y_1 + y_0) / 2;

    Matrix M;

    M = GetTranslationMatrix(GetSize().x / 2.0, GetSize().y / 2.0) *
        GetTranslationMatrix(-disX / (x_1 - x_0) * GetSize().x, disY / (y_1 - y_0) * GetSize().y) *
        GetScaleMatrix(GetSize().x - 20, GetSize().y - 20, x_0, x_1, y_0, y_1);

    dc.SetPen(*wxBLACK_PEN);
    DrawLine2d(&dc, M, x_0, 0, x_1, 0);
    DrawLine2d(&dc, M, x_1 - 0.5, -0.5, x_1, 0);
    DrawLine2d(&dc, M, x_1 - 0.5, 0.5, x_1, 0);
    
    DrawLine2d(&dc, M, 0, y_0, 0, y_1);
    DrawLine2d(&dc, M, -0.5, y_1 - 0.5, 0, y_1);
    DrawLine2d(&dc, M, 0.5, y_1 - 0.5, 0, y_1);

    Vector u;

    dc.SetPen(*wxBLUE_PEN);
    for (double x = x_0; x <= x_1 ; x += (x_1 - x_0) / (10*(1.+thumb_pos/10.))) {
        DrawLine2d(&dc, M, x, -0.15, x, 0.15);
        DrawLine2d(&dc, M, -0.15, x, 0.15, x);
        u.Set(x, -0.2);
        u = M * u;
        dc.DrawText(wxString::Format(wxT("%.0f"), x), u.GetX(), u.GetY());
        if (x != 0) {
            u.Set(0.2, x);
            u = M * u;
            dc.DrawText(wxString::Format(wxT("%.0f"), x), u.GetX(), u.GetY());
        }
   }
    
    for (double x = x_0; x <= x_1; x += step) {
        DrawLine2d(&dc, M, x, f(x, funcFormula,y_0), x + step, f(x + step, funcFormula,y_0));
    }

    for (int i = 0; i < 4;i++) {
        if (added_funcFormula[i] != "" ) {
            dc.SetPen(TAB_COLOR[i]);
            for (double x = x_0; x <= x_1; x += step) {
                DrawLine2d(&dc, M, x, f(x, added_funcFormula[i], y_0), x + step, f(x + step, added_funcFormula[i], y_0));
            }
        }
    }

    dc.SetPen(*wxGREEN_PEN);

    if (drawPointLine) {
        double y = 0, x = 0;

        if (yASK >= 0) {
            while (y < yASK) {
                DrawLine2d(&dc, M, xASK, y, xASK, y + yASK / 10);
                y += yASK / 10 * 2;
            }
        }
        else {
            while (y > yASK) {
                DrawLine2d(&dc, M, xASK, y - 0.05, xASK, y + yASK / 10);
                y += yASK / 10 * 2;
            }
        }
        if (xASK >= 0) {
            while (x < xASK) {
                DrawLine2d(&dc, M, x, yASK, x + yASK / 10, yASK);
                x += yASK / 10 * 2;
            }
        }
        else {
            while (x > xASK) {
                DrawLine2d(&dc, M, x, yASK, x + yASK / 10, yASK);
                x += yASK / 10 * 2;
            }
        }

        u.Set(xASK, yASK);
        u = M * u;

        dc.DrawCircle(u.GetX(), u.GetY(), 5);
    }  

    xASK = f(xASK, funcFormula, y_0);

}

BEGIN_EVENT_TABLE(MyCustomPanel, wxPanel)
EVT_PAINT(MyCustomPanel::OnPaint)
END_EVENT_TABLE()

void DrawLine2d(wxPaintDC* dc, Matrix M, double x_1, double y_1, double x2, double y2)
{
    Vector u, v;

    u.Set(x_1, y_1);
    v.Set(x2, y2);

    u = M * u;
    v = M * v;

    dc->DrawLine(u.GetX(), u.GetY(), v.GetX(), v.GetY());
}



