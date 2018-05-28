#include "Utils.h"

enum class WebFormat
{
	FULL, MID , SHORT
};

bool end(string& str) {
	bool retValue = false;
	if (str.find("</rss>") != string::npos)
		retValue = true;

	return retValue;
}

bool getFileSize(string& str, size_t& size) {
	bool retValue;
	size_t place = str.find("Content-Length: ");
	if (place == string::npos)
		retValue = true;
	else {
		retValue = false;
		string num = str.c_str() + place + strlen("Content-Length: ");
		num = num.substr(0, num.find('\r'));
		size = atoi(num.c_str());
		string garbage = num.substr(0, num.find("<rss"));
		size += garbage.size();
	}

	return retValue;
}

void printPercentage(basicLCD & lcd, float percentage, string webPage, unsigned int speed)
{
	cursorPosition cs = lcd.lcdGetCursorPosition();
	
	if (cs.row == 2) 
		lcd.lcdMoveCursorUp();
	lcd.lcdClearToEOL();
	lcd << webPage;//showText(lcd, webPage, speed);
	lcd.lcdMoveCursorDown();
	lcd << to_string((int)percentage) << "%";
	lcd.lcdMoveCursorUp();
}

string getXML(basicLCD & lcd, CursesClass & curses, string web)
{
	client client;
	string tempWeb;

	if (web.find("//") == string::npos)
		tempWeb = web;
	else
		tempWeb = web.substr(web.find("//") + 2);

	string host = tempWeb.substr(0, tempWeb.find_first_of('/'));
	string instrGet = "GET " + tempWeb.substr(tempWeb.find_first_of('/')) + " HTTP/1.1" + "\r\n";
	string instrHost = "Host: " + host + "\r\n";
	string instrBlank = "\r\n";
	string auxString = "";

	client.startConnection(host.c_str());

	if (client.success()) {
		client.send_message(instrGet.c_str(), instrGet.size());
		client.send_message(instrHost.c_str(), instrHost.size());
		client.send_message(instrBlank.c_str(), instrBlank.size());

		bool getSize = true;
		bool leave = false;
		size_t len = 0;
		size_t totalSize;
		int speed = 55;


		do {
			auxString += client.receiveMessage();
			len = auxString.size();
			if (getSize) {
				getSize = getFileSize(auxString,totalSize);
			}else
				printPercentage(lcd, 100 * len / (float)totalSize, host,speed );

			switch (getch()) {
			case ERR: break;
			case 'q':
				leave = true;
				curses.clearDisplay();
				curses << "Download Interrupted.\n";
				auxString = "";
				break;
			case '+':
				speed += (speed + 10 >= 100 ? 0 : 10);
				break;
			case '-':
				speed -= (speed - 10 <= 0 ? 0 : 10);
				break;

			}

		} while (!leave && !end(auxString));
	}
	else
		curses << "Error: Client was never initialized";

	auxString = auxString.substr(0, auxString.find_last_of('>') + 1);
	return auxString;
}

bool isLaNacion(string str)
{
	return (str.find("lanacion") != string::npos);
}

string getSite(string web)
{
	// Me fijo que tipo de pagina es (si tiene http, www o nada)
	WebFormat format;
	string retValue;
	if (web.find("//") != string::npos)
		format = WebFormat::FULL;
	else {
		string www = web.substr(0, web.find_first_of('.'));

		if (www.size() <= 3)				// Estoy asumiendo que todas las paginas tienen mas de 3 letras en su nombre, que para el caso de los diarios, es valido
			format = WebFormat::MID;
		else
			format = WebFormat::SHORT;
	}
	string temp;
	switch (format) {
	case WebFormat::FULL:
	case WebFormat::MID:
		temp = web.substr(web.find_first_of('.') + 1);
		retValue = temp.substr(0, temp.find_first_of('.'));
		break;
	case WebFormat::SHORT:
		retValue = web.substr(0, web.find_first_of('.'));
		break;
	}

	return retValue;
}
