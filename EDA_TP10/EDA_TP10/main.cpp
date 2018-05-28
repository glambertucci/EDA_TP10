
#include "LCD/Hitachi/hitachilcd.h"
#include "LCD/Allegro/allegrolcd.h"
#include "textAdapter.h"
#include "Utils.h"
#include "Utils/XMLParser.h"
void cortar(string &data, string &ans);


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
	//hitachilcd lcdk;
	allegrolcd lcdA(1.3,2.3);
	CursesClass curses;
	string file = getXML(lcdA, curses, argv[1]);
	basicLCD* lcd = &lcdA;

	cursorPosition cursor = lcd->lcdGetCursorPosition();
	if (cursor.row == 2)
		lcd->lcdMoveCursorUp();

	if (file.size() != 0) {
		vector <string> titulos, fechas;
		parseXML(file, titulos, fechas, isLaNacion(argv[1]));

		for (string& str : titulos)
			changeSpecialChar(str);

		// Falta formatear a los titulos y a la fecha

		unsigned int speed = 45, index = 0;
		bool leave = false;

		do {
			switch (curses.getSingleLoweredCharInRange(0, 255, 5, 0, "Nope")) {
			case 'q':leave = true;											// Sale del programa
				break;
			case '+':speed += (speed + 10 >= 100 ? 0 : 10);					// Incremento la velocidad
				break;
			case '-':speed -= (speed - 10 <= 0 ? 0 : 10);					// Decremento la velocidad
				break;
			case 'a': index = (index == 0 ? titulos.size() : index - 1);	// Muestro el titulo anterior
				break;
			case 's': index = (index == titulos.size() ? 0 : index + 1);	// Muestro el titulo proximo
				break;
			case 'r':														// Muestro de vuelta el titulo
				break;
			}

			lcd->lcdClear();

			showText(*lcd, titulos[index], speed);
			lcd->lcdMoveCursorDown();

			*lcd << fechas[index];
			lcd->lcdMoveCursorUp();
		} while (!leave);
	}

	return 0;

}
