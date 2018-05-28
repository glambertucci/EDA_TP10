#pragma once
#include <string>
#include <vector>
#include "Utils.h"
using namespace std;
/*La funcion changeSpecialChar modifica los caracteres que no pueden imprimirse en el lcd
Recibe una referencia a string del texto que debe ser modificado
*/

void changeSpecialChar(string & text);

//void formatTitle(string& text, string web);

void formatDate(vector<string>& dates);

void formatTitle(vector<string>& titles, string site);