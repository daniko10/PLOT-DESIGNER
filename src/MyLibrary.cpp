#include "MyLibrary.h"
#include "exprtk.hpp"

std::string funcFormula = "";
std::vector<std::string> added_funcFormula = { "","","","","" };

double  x_0 = -10, x_1 = 10, y_0 = -10, y_1 = 10, xASK = 0, yASK = 0;
double thumb_pos = 0;
bool drawPointLine = false;
int TAB_ID[4] = { 1,2,3,4 };

double f(double x, std::string expression, double y) {
    symbol_table_t symbol_table;
    symbol_table.add_variable("x", x);

    expression_t expression_obj;
    expression_obj.register_symbol_table(symbol_table);

    parser_t parser;
    if (!parser.compile(expression, expression_obj)) {
        return RAND_MAX; // Zwróć wartość domyślną w przypadku błędu
    }

    return expression_obj.value();
}