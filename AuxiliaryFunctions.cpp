#include "Header.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define ESC 27
#define ENTER 13

    string TakePathToExeFile() {
    char buffer[MAX_PATH];
    // NULL означает, что мы хотим получить путь текущего процесса
    DWORD length = GetModuleFileNameA(NULL, buffer, MAX_PATH);

    if (length != 0) {
        std::string exePath(buffer);
        std::string dir = exePath.substr(0, exePath.find_last_of("\\/"));

        return dir;
    }

    else {
        std::cout << "Ошибка при получении пути!" << std::endl;
        cout << "Для возврата в главное меню нажмите любую клавишу..." << std::endl;
        _getch();
        return "";
    }
}


    void drawMenuExitMenu(int selectedItem) {

        vector<string> menuItems = {"1. Нет!", "2.Да!"};

        system("cls");

        cout << "Вы точно хотите завершить работу программы?" << endl;
        for (int i = 0; i < menuItems.size(); ++i) {
            if (i == selectedItem) {
                cout << "->" << menuItems[i] << endl;
            }
            else {
                cout << "    " << menuItems[i] << endl;
            }
        }
    }

    bool CloseProgram() {

        int selected = 0;
        bool running = true;

        while (running) {
            drawMenuExitMenu(selected);

            int key = _getch();

            // Обработка специальных клавиш (стрелки)
            if (key == 0 || key == 224) {
                key = _getch();
                switch (key) {
                case KEY_UP:
                    selected = (selected - 1 + 2) % 2; // Цикличная прокрутка вверх
                    break;
                case KEY_DOWN:
                    selected = (selected + 1) % 2;     // Цикличная прокрутка вниз
                    break;
                case KEY_RIGHT:
                    running = false;
                    if (selected == 0) {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                    break;
                }
            }
            // Обработка цифровых клавиш '1' - '2' 
            else if (key >= '1' && key <= '2') {
                if (key - '1' == 0) {
                    running = false;
                    return true;
                }
                else
                {
                    running = false;
                    return false;
                }
                break;
            }

            // Выход на ESC
            else if (key == ESC) {
                running = false;
                return true;
            }

            else if (key == ENTER) {
                running = false;
                if (selected == 0) {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

    }

    void createFile() {
        system("cls");
        cout << "Введите имя файла: ";
        string NameFile;
        cin >> NameFile;

        //Проверка на существование файла с таким именем
        ifstream Test(TakePathToExeFile() + "\\" + NameFile + ".txt");
        if (Test.is_open()) {

            cout << "Ошибка! Файл с таким именем уже существует, необходимо изменить имя файла" << endl;


        }
        
        else {
            ofstream File(TakePathToExeFile() + "\\" + NameFile + ".txt");
            if (File.is_open()) {

                cout << "Файл " << NameFile << " успешно создан" << endl;
                cout << "Нажмите любую клавишу, чтобы вернуться в главное меню...";
                _getch();
            }

            else {
                cout << "Ошибка при создании файла" << endl;
                cout << "Нажмите любую клавишу, чтобы вернуться в главное меню...";
                _getch();
            }
        }

        
    }