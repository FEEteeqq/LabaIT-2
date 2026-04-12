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
#define KEY_LEFT 75
#define ESC 27
#define ENTER 13

using namespace std;

struct FullString {
    string FileName;
    string ComputerLabel;
    string NumberClass;
    string ComputerFubricNumber;
    string NumbersTerminal;
    string NumbersVneshUstroystv;
};

void drawMenu(int selectedItem);
bool performAction(int itemIndex);
bool performActionWithFile(int itemIndex, string& FirstFile, string& SecondFile, string& ExitFile);
bool CloseProgram();
void Work();
void InfoInFile();
bool AddFileMenu();
bool AddFiles();
string ExitFileName();
string ChooseFile(string Path, bool OnlyName);
void InfoInConsole();
bool Start();
void DrawInfoInConsoleMenu(int selectedItem);
void CheckFileInFirstProgram(bool Start);
void InfoInConsole();
vector<FullString> FindInfo(int element);
bool CreateFolder(std::string FolderNames);
string GetDesktopPath();
string TakePathToExeFile();