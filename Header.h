#pragma once

#include <string>
#include <fstream>
#include <windows.h>
#include <vector>
#include <iostream>
#include <conio.h>

using namespace std;


void drawMenu(int selectedItem);
bool performAction(int itemIndex);
bool CloseProgram();
void Work();
void createNewFile();
string TakePathToExeFile();