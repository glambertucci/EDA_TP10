#include "textAdapter.h"
#include <map>

typedef pair<char, char> spch;	//Simplifica el metodo de insert para el diccionario
void insertChars(map<char, char> & specialChar);	//Funci�n de redefinicion de caracteres especiales  

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
	specialChar.insert(spch('�','a'));
	specialChar.insert(spch('�','e'));
	specialChar.insert(spch('�','i'));
	specialChar.insert(spch('�','o'));
	specialChar.insert(spch('�','u'));
	specialChar.insert(spch('�','u'));
	specialChar.insert(spch('�','n'));
	specialChar.insert(spch('�','N'));
	specialChar.insert(spch('�', 'U'));
	//Si se desea agregar algun caracter especial:
	//specialChar.insert(spch(' ', ' '));
}