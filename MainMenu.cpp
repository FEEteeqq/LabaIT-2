#include "Header.h"



void drawMenu(int selectedItem) {

    vector<string> menuItems = { "1. Вывод данных в консоль", "2. Вывод данных в файл", "3. Обновить списки с файлами", "4. Завершить работу программы" };

    system("cls");
    cout << "------ ГЛАВНОЕ МЕНЮ ------" << endl;
    for (int i = 0; i < menuItems.size(); ++i) {
        if (i == selectedItem) {
            cout << "->" << menuItems[i] << endl;
        }
        else {
            cout << "    " << menuItems[i] << endl;
        }
    }
}

    bool performAction(int itemIndex) {
    system("cls");

    switch (itemIndex) {
    case 0: 
        InfoInConsole();
        return true;
        break;
    case 1: 
        createFile();
        return true;
        break;
    case 2:
        return AddFileMenu();
        return true;
        break;
    case 3:
        return CloseProgram();
        break;
    }
    


    
    
}

void Work() {
    bool running = Start();
    system("cls");
    int selected = 0;

    while (running) {
        drawMenu(selected);

        int key = _getch();

        // Обработка специальных клавиш (стрелки)
        if (key == 0 || key == 224) {
            key = _getch();
            switch (key) {
            case KEY_UP:
                selected = (selected - 1 + 4) % 4; // Цикличная прокрутка вверх
                break;
            case KEY_DOWN:
                selected = (selected + 1) % 4;     // Цикличная прокрутка вниз
                break;
            case KEY_RIGHT:
                running = performAction(selected);
                break;
            }
        }
        // Обработка цифровых клавиш '1' - '4' 
        else if (key >= '1' && key <= '4') {
            if (key - '1' == 3) {
                running = CloseProgram();
            }
            else {
                performAction(key - '1');
            }
        }
        // Выход на ESC
        else if (key == ESC) {
            running = CloseProgram();
        }

        else if (key == ENTER) {
            running = performAction(selected);
        }
    }

}