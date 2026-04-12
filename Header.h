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
    string FirstFileName;
    string SecondFileName;
    string ComputerLabel;
    string NumberClass;
    string ComputerFubricNumber;
    string NumbersTerminal;
    string NumbersVneshUstroystv;
};

void drawMenu(int selectedItem);
void Work();
void DrawInfoFileMenu(int selectedItem, string FirstFile, string SecondFile, string ExitFile, string Status);
void InfoInFile();
void DrawInfoInConsoleMenu(int selectedItem);
void FindInfo(int element);
void InfoInConsole();
void CheckFileInFirstProgram(bool Start);
void DrawAddFileMenu(int selectedItem);
void drawExitMenu(int selectedItem);

bool CloseProgram();
bool Start();
bool AddFiles();
bool AddFileMenu();
bool performActionWithFile(int itemIndex, string& FirstFile, string& SecondFile, string& ExitFile);
bool performAction(int itemIndex);
bool CreateAndWriteFile(string FirstFile, string SecondFile, string ExitFile);
bool CreateFolder(std::string FolderNames);

string GetDesktopPath();
string TakePathToExeFile();
string ExitFileName();
string ChooseFile(string Path, bool OnlyName);
