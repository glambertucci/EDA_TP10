#include "XMLParser.h"

int getSize(FILE * file);
//void startTag(void * userData, const char * name, const char ** att);
//void endTag(void * userData, const char * name);
//void charData(void *userData, const char * s, int lenght);

void startTag(void * userData, const char * name, const char ** att) {
	UserData * ud = (UserData *)userData;

	if (ud->compareItem(name)) {
		ud->Item = true;
	}
	else if (ud->compareDate(name)) {
		ud->Date = true;
	}
	else if (ud->compareTitle(name)) {
		ud->Title = true;
	}
}
void endTag(void * userData, const char * name) {
	UserData * ud = (UserData *)userData;


	if (ud->compareItem(name)) {
		ud->Item = false;
	}
	else if (ud->compareDate(name)) {
		ud->Date = false;
	}
	else if (ud->compareTitle(name)) {
		ud->Title = false;
	}
}

void charData(void *userData, const char * s, int lenght) {
	static int a = 0;

	UserData * ud = (UserData *)userData;
	if (ud->Item && ud->Title) {
		string temp;
		for (int i = 0; i < lenght; i++)
			temp.push_back(s[i]);
		ud->titulos->push_back(temp);
	}
	if (ud->Item && ud->Date) {
		a++;
		string temp;
		for (int i = 0; i < lenght; i++)
			temp.push_back(s[i]);
		ud->fechas->push_back(temp);
	}
}

int getSize(FILE * file) {
	fseek(file, 0L, SEEK_END);
	int fileSize = ftell(file);
	rewind(file);

	return fileSize;
}

void parseXML(string& file, vector <string>&titulos, vector<string>&fechas, bool laNacion) {
	XML_Parser parser;
	XML_Status status;

	UserData userData(&titulos, &fechas, laNacion);
	parser = XML_ParserCreate(nullptr);

	XML_SetElementHandler(parser, startTag, endTag);
	XML_SetCharacterDataHandler(parser, charData);
	XML_SetUserData(parser, &userData);

	char * buff  = (char *)file.c_str();

	XML_Parse(parser, buff, file.size(), true);

	XML_ParserFree(parser);
}