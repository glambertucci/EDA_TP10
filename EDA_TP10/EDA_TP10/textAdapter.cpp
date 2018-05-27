#include "textAdapter.h"
#include <map>

typedef pair<char, char> spch;	//Simplifica el metodo de insert para el diccionario
void insertChars(map<char, char> & specialChar);	//Función de redefinicion de caracteres especiales  

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

//Caracteres especiales
void insertChars( map<char, char> & specialChar)
{	//Si se desea eliminar algun caracter puede comentarse una linea
	specialChar.insert(spch('á','a'));
	specialChar.insert(spch('é','e'));
	specialChar.insert(spch('í','i'));
	specialChar.insert(spch('ó','o'));
	specialChar.insert(spch('ú','u'));
	specialChar.insert(spch('ü','u'));
	specialChar.insert(spch('ñ','n'));
	specialChar.insert(spch('Ñ','N'));
	specialChar.insert(spch('Ü', 'U'));
	//Si se desea agregar algun caracter especial:
	//specialChar.insert(spch(' ', ' '));
}