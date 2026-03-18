#include "Header.h"

struct FullString {

    string ComputerLabel[21];
    string NumberClass[14];
    string ComputerFubricNumber[21];
    string NumbersTerminal[3];
    string NumbersVneshUstroystv[3];

};

void DrawInfoInConsoleMenu(int selectedItem) {

    vector<string> menuItems = { "1. Марка ЭВМ (рекомендуемый вариант)", "2. Номер кафедры",
        "3. Заводской номер ЭВМ", "4. Количество терминалов", "5. Количество внешних запоминающих устройств"};

    system("cls");
    cout << "   --- Меню выбора поля для поиска информации ---    " << endl;
    cout << "По какому полю будет поиск информации?" << endl;
    for (int i = 0; i < menuItems.size(); ++i) {
        if (i == selectedItem) {
            cout << "->" << menuItems[i] << endl;
        }
        else {
            cout << "    " << menuItems[i] << endl;
        }
    }
}


vector<FullString> FindInfo(int element, string Info) {

    vector<FullString> Information;
    FullString TemporaryInformation;
    string FirstPath = TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 1 типа\\";
    string SecondPath = TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 2 типа\\";

    switch (element) { 
    case 0 /*Поиск по Марке ЭВМ*/:
        break;
    case 1 /*Поиск по Номеру кафедры*/:
        break;
    case 2 /*Поиск по Заводскому номеру ЭВМ*/:
        break;
    case 3 /*Поиск по Количеству терминалов*/:
        break;
    case 4 /*Поиск по Количеству внешних запоминающих устройств*/:
        break;
    }

}


void InfoInConsole () {

    int selected = 0;
    bool running = true;

    while (running) {
        DrawInfoInConsoleMenu(selected);

        int key = _getch();

        // Обработка специальных клавиш (стрелки)
        if (key == 0 || key == 224) {
            key = _getch();
            switch (key) {
            case KEY_UP:
                selected = (selected - 1 + 5) % 5; // Цикличная прокрутка вверх
                break;
            case KEY_DOWN:
                selected = (selected + 1) % 5;     // Цикличная прокрутка вниз
                break;
            case KEY_RIGHT:
                running = false;
                if (selected == 0) {
                    
                }
                else
                {
                    
                }
                break;
            }
        }
        // Обработка цифровых клавиш '1' - '5' 
        else if (key >= '1' && key <= '5') {
            if (key - '1' == 0) {
                system("cls");
                cout << "Поиск по Марке ЭВМ..." << endl;
                _getch();
            }
            else if (key - '1' == 1) {
                system("cls");
                cout << "Поиск по Номеру кафедры..." << endl;
                _getch();
            }
            else if (key - '1' == 2) {
                system("cls");
                cout << "Поиск по Заводскому номеру ЭВМ..." << endl;
                _getch();
            }
            else if (key - '1' == 3) {
                system("cls");
                cout << "Поиск по Количеству терминалов..." << endl;
                _getch();
            }
            else if (key - '1' == 4) {
                system("cls");
                cout << "Поиск по Количеству внешних запоминающих устройств..." << endl;
                _getch();
            }
            break;
        }

        // Выход на ESC
        else if (key == ESC) {
            running = false;
        }

        else if (key == ENTER) {
            running = false;
            if (selected == 0) {
                system("cls");
                cout << "Поиск по Марке ЭВМ..." << endl;
                _getch();
            }
            else if (selected == 1) {
                system("cls");
                cout << "Поиск по Номеру кафедры..." << endl;
                _getch();
            }
            else if (selected == 2) {
                system("cls");
                cout << "Поиск по Заводскому номеру ЭВМ..." << endl;
                _getch();
            }
            else if (selected == 3) {
                system("cls");
                cout << "Поиск по Количеству терминалов..." << endl;
                _getch();
            }
            else if (selected == 4) {
                system("cls");
                cout << "Поиск по Количеству внешних запоминающих устройств..." << endl;
                _getch();
            }
        }
    }

}
