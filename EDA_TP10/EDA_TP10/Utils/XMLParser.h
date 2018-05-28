#pragma once
#include <string>
#include <vector>
#include <expat.h>

using namespace std;

typedef struct UserData
{
	UserData(vector <string>& titulos, vector <string>&fechas,bool LaNacion = false) {
		if (LaNacion) {
			item = "entry";
			date = "update";
		}
		this->titulos = &titulos;
		this->fechas = &fechas;
	}

	bool compareItem(const char * arr) {
		return !item.compare(arr);
	}

	bool compareDate(const char * arr) {
		return !date.compare(arr);
	}

	bool compareTitle(const char * arr) {
		return !title.compare(arr);
	}

	bool Item = false;
	bool Date = false;
	bool Title = false;
	vector <string>* titulos, * fechas;

private:
	string item = "item";
	string date = "pubDate";
	string title = "title";
};

void parseXML(string& file, vector <string>&titulos, vector<string>&fechas, bool laNacion);