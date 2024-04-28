#pragma once

#include <wx/wx.h>
#include "exprtk.hpp"

#define WXSUPPRESS_SIZER_FLAGS_CHECK

extern std::string funcFormula;
extern std::vector<std::string> added_funcFormula;
extern double x_0, x_1, y_0, y_1, xASK, yASK;
extern double thumb_pos;
extern bool drawPointLine;
extern int TAB_ID[4];

typedef exprtk::symbol_table<double> symbol_table_t;
typedef exprtk::expression<double> expression_t;
typedef exprtk::parser<double> parser_t;

extern double f(double x, std::string expression, double y);