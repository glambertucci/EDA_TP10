#include "Network/client.h"
#include "LCD/Hitachi/hitachilcd.h"
#include "LCD/Allegro/allegrolcd.h"
#include "textAdapter.h"
#include "Utils.h"
#include "Utils/XMLParser.h"

// FALTA:
//		- Solucionar el tema de los caracteres raros

int main(int argc, char ** argv)
{

	if (argc > 2)
	{
		cout << ">> Input error: to many arguments." << endl;
		cout << ">> Only needed the host for parse.-" << endl;
		return -1;
	}

	if (argc < 2)
	{
		cout << ">> Input error: no host entered" << endl;
		cout << ">> Please enter host as parameter.-" << endl;
		return -1;
	}
	//hitachilcd lcdA;
	allegrolcd lcdA(1.3,2.3);
	CursesClass curses;
	string file = getXML(lcdA, curses, argv[1]);
	basicLCD* lcd = &lcdA;
	lcd->lcdClear();

	if (file.size() != 0) {
		file = file.substr(file.find("<rss"));

		vector <string> titulos, fechas;
		parseXML(file, titulos, fechas, isLaNacion(argv[1]));

		for (string& str : titulos)
			changeSpecialChar(str);

		formatDate(fechas);
		formatTitle(titulos, getSite(argv[1]));

		unsigned int speed = 505, index = 0;
		bool leave = false;
		unsigned int count = 0;

		do {
			cursorPosition cur2 = { 1,1 };
			lcd->lcdSetCursorPosition(cur2);
			lcd->lcdClearToEOL();

			showText(*lcd, titulos[index], speed, count);//*lcd << titulos[index]; //
			//lcd->lcdMoveCursorDown();
			cursorPosition cur = { 2,1 };
			lcd->lcdSetCursorPosition(cur);
			

			*lcd << fechas[index];
			//lcd->lcdMoveCursorUp();

			switch (getch()) { 
			case 'q':leave = true;											// Sale del programa
				break;
			case '+':speed -= (speed - 10 <= 0 ? 0 : 10);
									// Incremento la velocidad
				break;
			case '-':speed += (speed + 10 >= 100 ? 0 : 10);					// Decremento la velocidad
				break;
			case 'a': index = (index == 0 ? titulos.size() : index - 1);	// Muestro el titulo anterior
				break;
			case 's': index = (index < titulos.size() ? index + 1 : 0);		// Muestro el titulo proximo
				break;
			case 'r':														// Muestro de vuelta el titulo
				count = 0;
				break;
			}


		} while (!leave);
	}

	return 0;

}
