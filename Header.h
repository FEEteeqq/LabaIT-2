#pragma once

#include <string>
#include <fstream>
#include <windows.h>
#include <vector>
#include <iostream>
#include <conio.h>
#include <direct.h>
#include <filesystem>
#include <shlobj.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define ESC 27
#define ENTER 13

using namespace std;

struct FullString {
    string ComputerLabel[21];
    string NumberClass[14];
    string ComputerFubricNumber[21];
    string NumbersTerminal[3];
    string NumbersVneshUstroystv[3];
};

void drawMenu(int selectedItem);
bool performAction(int itemIndex);
bool CloseProgram();
void Work();
void createFile();
void InfoInConsole();
bool Start();
void DrawInfoInConsoleMenu(int selectedItem);
void CheckFileInFirstProgram();
void InfoInConsole();
vector<FullString> FindInfo(int element, string Info);
bool CreateFolder(std::string FolderNames);
string GetDesktopPath();
string TakePathToExeFile();