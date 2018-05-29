#include "marquesina.h"
#include <vector>
#include <iostream>
#include "Utils/Timer.h" 
using namespace std;

#define SCREENSIZE 16
#define CLEANCHAR ' '

void showText(basicLCD & lcd, string & text, unsigned int speed, unsigned int & count)
{
	string screen = "               " + text;
	

	if (count < text.size()) {
		string temp = screen.substr(count, count + 16);
		lcd << temp;
		count++;
		wait(speed);
	}

	//for (unsigned int i = 0; i < (text.size() + 1); i++)
	//{
	//	screen[SCREENSIZE - 1] = text[i];
	//	lcd << screen;
	//	wait(speed);

	//	for (int j = 0; j < (SCREENSIZE - 1); j++)
	//		screen[j] = screen[j + 1];
	//}
}