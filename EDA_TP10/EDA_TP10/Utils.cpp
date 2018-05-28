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

void printPercentage(basicLCD & lcd, float percentage, string webPage, unsigned int speed)
{
	cursorPosition cs = lcd.lcdGetCursorPosition();
	if (cs.row == 2) 
		lcd.lcdMoveCursorUp();
	lcd << webPage;//showText(lcd, webPage, speed);
	lcd.lcdMoveCursorDown();
	lcd << to_string((int)percentage) << "%";
}

string getXML(basicLCD & lcd, CursesClass & curses, string web)
{
	client client;
	string host = web.substr(0, web.find_first_of('/'));
	string instrGet = "GET " + web.substr(web.find_first_of('/')) + " HTTP/1.1" + "\r\n";
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
				getSize = false;
				totalSize = getFileSize(auxString);
			}
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


	return auxString;
}

bool isLaNacion(string str)
{
	return (str.find("lanacion") != string::npos);
}
