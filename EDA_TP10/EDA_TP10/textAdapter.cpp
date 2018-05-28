#include "textAdapter.h"
#include <map>
#include <iostream>
using namespace std;

typedef pair<char, char> spch;	//Simplifica el metodo de insert para el diccionario
typedef pair<string, const char *> Month;
void insertChars(map<char, char> & specialChar);	//Funci�n de redefinicion de caracteres especiales  
void setUpMonths(map <string, const char *>& month);

void changeSpecialChar(string & text)
{
	map<char,char>specialChar;
	insertChars(specialChar);		//Cargo los caracteres especiales en mi diccionario

	for (unsigned int i = 0; i < text.size(); i++)
	{
		map<char,char>::iterator pos = specialChar.find((text[i]));	//Busco en mi diccionario
		if (pos != specialChar.end())	//Si lo encuentro, reemplazo por el caracter defincion que puede mostrarse
			text[i] = (specialChar.find((text[i]))->second);
	}
}

void formatDate(vector<string>& dates)
{
	map <string, const char *> month;
	setUpMonths(month);

	for (string& str : dates) {
		size_t init = str.find(' ');
		string day = str.substr(init + 1, 2);
		string mnth = str.substr(init + 4, 3);
		string year = str.substr(init + 10, 2);
		string hour = str.substr(init + 13, 5);
		string final = day + '/' + month[mnth] + '/' + year +" - " + hour;
		str = final;
	}


}

void setUpMonths(map <string, const char*> & month) {
	month["Jan"] = "01";
	month["Feb"] = "02";
	month["Mar"] = "03";
	month["Apr"] = "04";
	month["May"] = "05";
	month["Jun"] = "06";
	month["Jul"] = "07";
	month["Aug"] = "08";
	month["Sep"] = "09";
	month["Oct"] = "10";
	month["Nov"] = "11";
	month["Dic"] = "12";
}

//Caracteres especiales
void insertChars( map<char, char> & specialChar)
{	//Si se desea eliminar algun caracter puede comentarse una linea
	specialChar['�'] = 'a';
	specialChar['�'] = 'e';
	specialChar['�'] = 'i';
	specialChar['�'] = 'o';
	specialChar['�'] = 'u';
	specialChar['�'] = 'u';
	specialChar['�'] = 'n';
	specialChar['�'] = 'N';
	specialChar['�'] = 'U';
	//Si se desea agregar algun caracter especial:
	//specialChar[''] = '';
}