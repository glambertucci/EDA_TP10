#pragma once
#include "Network\client.h"
#include <string>
#include "LCD\BasicLcd.h"
#include "Utils\CursesClass.h"
#include "marquesina.h"

using namespace std;

bool end(string& str);

bool getFileSize(string& str, size_t& size);

void printPercentage(basicLCD& lcd, float percentage, string webPage, unsigned int speed);

string getXML(basicLCD& lcd, CursesClass& curses, string web);

bool isLaNacion(string str);

string getSite(string web);


