#pragma once
#include <string>
#include "LCD/BasicLcd.h"
using namespace std;

void showText(basicLCD & lcd, string & text, int speed, unsigned int & count);
