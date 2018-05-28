#pragma once
#include <string>
#include "LCD\BasicLcd.h"
#include "Utils\CursesClass.h"
#include "marquesina.h"
#include "Network\client.h"
using namespace std;

bool end(string& str);

size_t getFileSize(string& str);

void printPercentage(basicLCD& lcd, float percentage, string webPage, unsigned int speed);

string getXML(basicLCD& lcd, CursesClass& curses, string web);

bool isLaNacion(string str);