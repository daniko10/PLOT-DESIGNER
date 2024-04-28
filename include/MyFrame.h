#pragma once

#include "MyLibrary.h"
#include "CustomPanel.h"

class MyFrame : public wxFrame {
public:
	MyFrame(const std::string& title);
	void OnSize(wxSizeEvent& event);
	void OnTextChange(wxCommandEvent& event);
	void OnReset(wxCommandEvent& event);
	void OnScroll(wxScrollEvent& event);
	void OnGetValue(wxCommandEvent& event);
	void OnGetValueVec0(wxCommandEvent& event);
	void OnGetValueVec1(wxCommandEvent& event);
	void OnGetValueVec2(wxCommandEvent& event);
	void OnGetValueVec3(wxCommandEvent& event);
	void OnClickAdd(wxCommandEvent& event);
	void OnClickDelete(wxCommandEvent& event);
private:
	MyCustomPanel* _customPanel;
	wxPanel* _imagePanel;

	wxTextCtrl* _func;
	wxTextCtrl* _x_y;
	wxTextCtrl* _y_x;
	std::vector<wxTextCtrl*> _added_funcs;
	wxButton* _reset;
	wxButton* _add_func;
	wxButton* _del_func;
	wxStaticText* _func_str;
	wxStaticText* _resize_str;
	wxStaticText* _coordinates;
	wxStaticText* _your_x;
	wxStaticText* _your_y;
	wxScrollBar* _resize_scroll;
	wxSizer* _sizer;
	wxSizer* _sizer_funcs;
	
	enum {
		ID_func = 1,
		ID_reset = 2,
		ID_func_str = 3,
		ID_zero_places_str = 4,
		ID_zero_places_scroll = 5,
		ID_x_y = 6,
		ID_y_x = 7,
		ID_add_func = 8,
		ID_del_func = 9
	};

	DECLARE_EVENT_TABLE()
};