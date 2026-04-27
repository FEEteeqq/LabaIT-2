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

const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_RIGHT = 77;
const int KEY_LEFT = 75;
const int ESC = 27;
const int ENTER = 13;

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

void DrawMenu(int selectedItem);
void Work();
void DrawInfoFileMenu(int selectedItem, string Status);
void InfoInFile();
void DrawInfoInConsoleMenu(int selectedItem);
void FindInfo(int element);
void CheckFileInFirstProgram(bool Start);
void DrawAddFileMenu(int selectedItem);
void DrawExitMenu(int selectedItem);
void ChoiseFilesPath();
void DrawChoiseFilesMenu(int selectedItem, string Permission);

bool InfoInConsole();
bool CloseProgram();
bool Start();
bool AddFiles();
bool AddFileMenu();
bool PerformActionWithFile(int itemIndex);
bool PerformAction(int itemIndex);
bool CreateAndWriteFile();
bool CreateFolder(std::string FolderNames);
bool PerformActionChoisesFilesMenu(int itemIndex, string Permission);

string GetDesktopPath();
string TakePathToExeFile();
string ExitFileName();
string ChooseFile(string Path, bool OnlyName);