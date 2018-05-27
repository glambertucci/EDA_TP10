#include "Utils.h"

bool end(string& str) {
	bool retValue = false;
	if (str.find("</rss>") != string::npos)
		retValue = true;


	return retValue;

}

size_t getFileSize(string& str) {

	size_t place = str.find("Content-Length: ");
	string num = str.c_str() + place + strlen("Content-Length: ");
	num = num.substr(0, num.find('\r'));

	return atoi(num.c_str());

}

void printPercentage(basicLCD & lcd, float percentage, string webPage)
{
	cursorPosition cs = lcd.lcdGetCursorPosition();
	if (cs.row == 2) 
		lcd.lcdMoveCursorUp();
	//showText(&lcd,)
	lcd.lcdMoveCursorDown();
	lcd << to_string((int)percentage) << "%";
}

string getXML(basicLCD & lcd, CursesClass & curses, string web)
{
	client client;
	string host = web.substr(0, '/');
	string instrGet = "GET " + web.substr('/') + "HTTP/1.1" + "\r\n";
	string instrHost = "Host: " + host + "\r\n";
	string instrBlank = "\r\n";
	client.startConnection(host.c_str());

	client.send_message(instrGet.c_str(), instrGet.size());
	client.send_message(instrHost.c_str(), instrHost.size());
	client.send_message(instrBlank.c_str(), instrBlank.size());

	bool getSize = true;
	bool leave = false;
	size_t len = 0;
	size_t totalSize;
	string auxString = "";

	do {
		auxString += client.receiveMessage();
		len = auxString.size();
		if (getSize) {
			getSize = false;
			totalSize = getFileSize(auxString);
		}
		printPercentage(lcd, 100 * len / (float)totalSize, host);

		if (curses.getSingleLoweredCharInRange(0, MAXCHAR, 5, 0, "Error: What The Fuck") == 'q') {
			leave = true;
			curses.clearDisplay();
			curses << "Download Interrupted.\n";
			auxString = "";
		}

	} while (!leave && !end(auxString));

	return auxString;
}
