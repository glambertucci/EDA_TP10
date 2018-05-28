#include "marquesina.h"
#include <vector>
#include <iostream>
#include "Utils/Timer.h" 
using namespace std;

#define SCREENSIZE 16
#define CLEANCHAR ' '

void showText(basicLCD & lcd, string & text, unsigned int speed)
{
	string screen;
	unsigned int count;
	for (int i = 0; i < SCREENSIZE; i++)
		screen[i] = CLEANCHAR;

	for (int i = 0; i < text.size(); i++)
	{
		count = SCREENSIZE;
		while (count > 0)
		{
			screen[count] = text[i];
			lcd << screen;
			wait(1/speed);
			count--;
		}
	}
}