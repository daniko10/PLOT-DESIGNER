#include "MyLibrary.h"
#include "MyFrame.h"
#include "exprtk.hpp"

MyFrame::MyFrame(const std::string& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1270, 800)) {
	_customPanel = new MyCustomPanel(this);

	_imagePanel = new wxPanel(this);
	_imagePanel->SetBackgroundColour(*wxWHITE);
	_imagePanel->SetSize(_customPanel->GetClientSize());

	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	_sizer = new wxBoxSizer(wxVERTICAL);
	_sizer_funcs = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* sizerX = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizerXX = new wxBoxSizer(wxHORIZONTAL);

	_func_str = new wxStaticText(this, ID_func_str, "f(x):", wxDefaultPosition, wxSize(80, 20), wxTE_CENTER);
	_func_str->SetFont(wxFont(wxFontInfo(12).Slant(wxFONTSTYLE_SLANT)));

	_func = new wxTextCtrl(this, ID_func, "", wxDefaultPosition, wxSize(70, 30), wxTE_CENTER );
	_func->SetFont(wxFont(wxFontInfo(12).Slant(wxFONTSTYLE_ITALIC)));

	_sizer_funcs->Add(_func_str, 0, wxALIGN_CENTER_HORIZONTAL, 5);
	_sizer_funcs->Add(_func, 1, wxEXPAND | wxALL, 10);

	_reset = new wxButton(this, ID_reset, "Reset", wxDefaultPosition, wxSize(50,30), wxBU_EXACTFIT);
	
	_resize_str = new wxStaticText(this, ID_func_str, "Resize your plot", wxDefaultPosition, wxSize(90, 20), wxTE_CENTER);
	_resize_str->SetFont(wxFont(wxFontInfo(10).Slant(wxFONTSTYLE_SLANT)));

	_resize_scroll = new wxScrollBar(this, ID_zero_places_scroll,wxDefaultPosition, wxSize(200,20));
	_resize_scroll->SetScrollbar(0, 0.1, 20, 1);

	_coordinates = new wxStaticText(this, ID_func_str, "Get 'y' coordinate of any Point(f(x)):", wxDefaultPosition, wxSize(90, 20), wxTE_CENTER);
	_coordinates->SetFont(wxFont(wxFontInfo(10).Slant(wxFONTSTYLE_SLANT)));

	_x_y = new wxTextCtrl(this, ID_x_y, "", wxDefaultPosition, wxSize(50, 20), wxTE_CENTER);
	_y_x = new wxTextCtrl(this, ID_y_x, "", wxDefaultPosition, wxSize(50, 20), wxTE_CENTER | wxTE_READONLY);
	_your_x = new wxStaticText(this, ID_func_str, "x = ", wxDefaultPosition, wxSize(30, 20), wxTE_CENTER);
	_your_y = new wxStaticText(this, ID_func_str, "y = ", wxDefaultPosition, wxSize(30, 20), wxTE_CENTER);

	_add_func = new wxButton(this, ID_add_func, "Add function", wxDefaultPosition, wxSize(80, 30), wxBU_EXACTFIT);
	_del_func = new wxButton(this, ID_add_func, "Delete function", wxDefaultPosition, wxSize(90, 30), wxBU_EXACTFIT);

	sizerX->Add(_your_x, 0, wxEXPAND | wxALL, 5);
	sizerX->Add(_x_y, 0, wxEXPAND | wxALL, 5);
	sizerX->Add(_your_y, 0, wxEXPAND | wxALL, 5);
	sizerX->Add(_y_x, 0, wxEXPAND | wxALL, 5);
	sizerXX->Add(_add_func, 0, wxEXPAND | wxALL, 5);
	sizerXX->Add(_del_func, 0, wxEXPAND | wxALL, 5);

	_sizer->Add(_sizer_funcs, 0, wxEXPAND | wxALL, 5);
	_sizer->Add(_reset, 0, wxALIGN_CENTER_HORIZONTAL , 15);
	_sizer->Add(_resize_str, 0, wxEXPAND | wxALL, 5);
	_sizer->Add(_resize_scroll, 0, wxALIGN_CENTER_HORIZONTAL, 5);
	_sizer->Add(_coordinates, 0, wxEXPAND | wxALL, 10);
	_sizer->Add(sizerX,0, wxALIGN_CENTER_HORIZONTAL,5);
	_sizer->Add(sizerXX, 0, wxALIGN_CENTER_HORIZONTAL, 5);

	mainSizer->Add(_customPanel, 7, wxEXPAND | wxALL, 5);
	mainSizer->Add(_sizer, 3, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	SetSizer(mainSizer);
	SetMinSize(wxSize(800, 600));
	SetMaxSize(wxSize(1280, 720));
	Centre();
	Show(true);

	_func->Bind(wxEVT_TEXT, &MyFrame::OnTextChange, this);
	_reset->Bind(wxEVT_BUTTON, &MyFrame::OnReset, this);
	_resize_scroll->Bind(wxEVT_SCROLL_THUMBTRACK, &MyFrame::OnScroll, this);
	_x_y->Bind(wxEVT_TEXT, &MyFrame::OnGetValue, this);
	_add_func->Bind(wxEVT_BUTTON, &MyFrame::OnClickAdd, this);
	_del_func->Bind(wxEVT_BUTTON, &MyFrame::OnClickDelete, this);
}


BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_SIZE(MyFrame::OnSize)
END_EVENT_TABLE()

void MyFrame::OnSize(wxSizeEvent& event) {
	_customPanel->Refresh();
	event.Skip();
}

void MyFrame::OnTextChange(wxCommandEvent& event) {
	wxTextCtrl* textCtrl = dynamic_cast<wxTextCtrl*>(event.GetEventObject());
	wxString s = textCtrl->GetValue();
	
	funcFormula = s.GetData();
	drawPointLine = false;
	
	_customPanel->Refresh();
}

void MyFrame::OnReset(wxCommandEvent& event) {
	funcFormula = "";
	_func->SetValue(wxString(funcFormula));
	
	for (int i = 0; i < 4; i++)
		added_funcFormula[i] = "";
	drawPointLine = false;

	_customPanel->Refresh();
}

void MyFrame::OnScroll(wxScrollEvent& event) {
	thumb_pos = _resize_scroll->GetThumbPosition();

	x_0 = -10 - thumb_pos;
	x_1 = 10 + thumb_pos;
	y_0 = -10 - thumb_pos;
	y_1 = 10 + thumb_pos;
	drawPointLine = false;

	_customPanel->Refresh();
}

void MyFrame::OnGetValue(wxCommandEvent& event) {
	wxTextCtrl* textCtrl = dynamic_cast<wxTextCtrl*>(event.GetEventObject());

	xASK = atof(textCtrl->GetValue());
	yASK = f(xASK, funcFormula, y_0);

	if (yASK == RAND_MAX) {
		_y_x->SetValue("Error");
		drawPointLine = false;
	}
	else {
		_y_x->SetValue(std::to_string(yASK));
		drawPointLine = true;
		_customPanel->Refresh();
	}
	
}

void MyFrame::OnClickAdd(wxCommandEvent& event) {
	int indx = _added_funcs.size();
	wxTextCtrl* t = nullptr;

	if (indx < 4) {
		_added_funcs.push_back(new wxTextCtrl(this, indx, "", wxDefaultPosition, wxSize(50, 30), wxTE_CENTER));
		
		t = _added_funcs[indx];
		t->SetFont(wxFont(wxFontInfo(12).Slant(wxFONTSTYLE_ITALIC)));

		switch (indx) {
		case 0: {
			t->Bind(wxEVT_TEXT, &MyFrame::OnGetValueVec0, this);
		}
			  break;
		case 1: {
			t->Bind(wxEVT_TEXT, &MyFrame::OnGetValueVec1, this);
		}
			  break;
		case 2: {
			t->Bind(wxEVT_TEXT, &MyFrame::OnGetValueVec2, this);
		}
			  break;
		case 3: {
			t->Bind(wxEVT_TEXT, &MyFrame::OnGetValueVec3, this);
		}
			  break;
		
		}
		
		_sizer_funcs->Add(t, 1, wxEXPAND | wxALL, 10);
		Layout();
	}
}

void MyFrame::OnClickDelete(wxCommandEvent& event) {
	int indx = _added_funcs.size();

	if (indx > 0) {
		wxTextCtrl* last_added_text_ctrl = _added_funcs.back();
		_added_funcs.pop_back();
		added_funcFormula[indx] = "";
		last_added_text_ctrl->Destroy();
		
		Layout();
		_customPanel->Refresh();
	}
}

void MyFrame::OnGetValueVec0(wxCommandEvent& event) {
	wxTextCtrl* textCtrl = dynamic_cast<wxTextCtrl*>(event.GetEventObject());
	added_funcFormula[0] = textCtrl->GetValue();
	
	drawPointLine = false;
	_customPanel->Refresh();
}

void MyFrame::OnGetValueVec1(wxCommandEvent& event) {
	wxTextCtrl* textCtrl = dynamic_cast<wxTextCtrl*>(event.GetEventObject());
	added_funcFormula[1] = textCtrl->GetValue();
	
	drawPointLine = false;
	_customPanel->Refresh();
}

void MyFrame::OnGetValueVec2(wxCommandEvent& event) {
	wxTextCtrl* textCtrl = dynamic_cast<wxTextCtrl*>(event.GetEventObject());
	added_funcFormula[2] = textCtrl->GetValue();
	
	drawPointLine = false;
	_customPanel->Refresh();
}

void MyFrame::OnGetValueVec3(wxCommandEvent& event) {
	wxTextCtrl* textCtrl = dynamic_cast<wxTextCtrl*>(event.GetEventObject());
	added_funcFormula[3] = textCtrl->GetValue();
	
	drawPointLine = false;
	_customPanel->Refresh();
}