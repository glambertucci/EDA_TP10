#include "textAdapter.h"
#include <map>
#include <iostream>
using namespace std;

void insertChars(map<char, char> & specialChar);	//Función de redefinicion de caracteres especiales  
void setUpMonths(map <string, const char *>& month);
void setUpNewspaper(map<string, string>& newspaper);
void changeSpecialChar(string & text)
{
	map<char,char>specialChar;
	insertChars(specialChar);		//Cargo los caracteres especiales en mi diccionario

	for (unsigned int i = 0; i < text.size(); i++)
	{
		map<char,char>::iterator pos = specialChar.find((text[i]));	//Busco en mi diccionario
		if (pos != specialChar.end())	//Si lo encuentro, reemplazo por el caracter defincion que puede mostrarse
			text[i] = specialChar.at(text[i]);// (specialChar.find((text[i]))->second);
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
		string final = day + '/' + month.at(mnth) + '/' + year +" - " + hour;
		str = final;
	}
}


void formatTitle(vector<string>& titles, string site)
{
	map<string, string> newspaper;
	setUpNewspaper(newspaper);
	string nspp;
	if (newspaper.count(site) == 1)
		nspp = newspaper.at(site);
	else
		nspp = site;

	for (string& title : titles) {
		title = nspp + ": -" + title + " -";
	}
}

void setUpNewspaper(map<string, string>& newspaper) {
	newspaper["lanacion"] = "La Nacion";
	newspaper["telam"] = "Telam";
	newspaper["clarin"] = "Clarin";
	newspaper["lavoz"] = "La Voz";
}

void setUpMonths(map <string, const char *>& month) {
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
	specialChar['á'] = 'a';
	specialChar['é'] = 'e';
	specialChar['í'] = 'i';
	specialChar['ó'] = 'o';
	specialChar['ú'] = 'u';
	specialChar['ü'] = 'u';
	specialChar['ñ'] = 'n';
	specialChar['Ñ'] = 'N';
	specialChar['Ü'] = 'U';
	//Si se desea agregar algun caracter especial:
	//specialChar[''] = '';
}