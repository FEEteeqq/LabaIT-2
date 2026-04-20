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
void FindInfo(int element, string FirstFile, string SecondFile);
void CheckFileInFirstProgram(bool Start);
void DrawAddFileMenu(int selectedItem);
void DrawExitMenu(int selectedItem);
void ChoiseFilesPath();
void DrawChoiseFilesMenu(int selectedItem, string FirstFilePath, string SecondFilePath, string Permission);

bool InfoInConsole(string FirstFile, string SecondFile);
bool CloseProgram();
bool Start();
bool AddFiles();
bool AddFileMenu();
bool PerformActionWithFile(int itemIndex, string& FirstFile, string& SecondFile, string& ExitFile);
bool PerformAction(int itemIndex);
bool CreateAndWriteFile(string FirstFile, string SecondFile, string ExitFile);
bool CreateFolder(std::string FolderNames);
bool PerformActionChoisesFilesMenu(int itemIndex, string& FirstFile, string& SecondFile, string Permission);

string GetDesktopPath();
string TakePathToExeFile();