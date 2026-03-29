#include "Header.h"



void DrawInfoInConsoleMenu(int selectedItem) {
    
    vector<string> menuItems = { "1. Марка ЭВМ", "2. Номер кафедры",
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


vector<FullString> FindInfo(int element) {
    
    system("cls");
    string TemporaryData;
    vector<FullString> Information;

    cout << "Для возврата в меню выбора пункта поиска ничего не вводите и нажмите клавишу Enter" << endl;

    switch (element) {
    case 1 /*Поиск по Марке ЭВМ*/:
        cout << "Введите Марку ЭВМ: ";
        break;
    case 2 /*Поиск по Номеру кафедры*/:
        cout << "Введите номер кафедры: ";
        break;
    case 3 /*Поиск по Заводскому номеру ЭВМ*/:
        cout << "Введите заводской номер ЭВМ: ";
        break;
    case 4 /*Поиск по Количеству терминалов*/:
        cout << "Введите количество терминалов: ";
        break;
    case 5 /*Поиск по Количеству внешних запоминающих устройств*/:
        cout << "Введите количество внешних запоминающих устройств: ";
        break;
    }

    getline(cin, TemporaryData);
    if (TemporaryData.empty()) {} /*Возврат в меню выбора пункта для поиска*/

    else {
        cout << "Перешли к поиску в файлах" << endl;

        std::string FirstPath = TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 1 типа\\"; // Путь к папке с файлами 1 типа
        std::string SecondPath = TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 2 типа\\"; // Путь к папке с файлами 2 типа

        if (FirstPath.c_str() != 0) {

            for (const auto& FilePath : std::filesystem::directory_iterator(FirstPath)) { // Цикл необходимый для получения имён файлов из папки
                string FileName = FilePath.path().filename().string(); // Оставляем от полного пути только имя файла
                ifstream File(FirstPath + FileName); 
                if (File.is_open()) {
                    string Temp;
                    int i = 0;
                    while (getline(File, Temp)) {

                        switch (element) {
                        case 1:
                            cout << "Должна произойти запись по 1.1 условию" << endl;
                            if (Temp.find(TemporaryData) <= 23) {
                                cout << "Должна произойти запись по 1.2 условию" << endl;
                                cout << Temp.substr(0, 23) << endl;
                                cout << Temp.substr(0, 23).find(TemporaryData) << endl;
                                cout << Temp.substr(0, 23).find(TemporaryData) + TemporaryData.size() << endl;
                                cout << Temp.substr(Temp.substr(0, 23).find(TemporaryData), Temp.substr(0, 23).find(TemporaryData) + TemporaryData.size()) << endl;
                                _getch();
                                // КОРОЧЕ ОН БЕРЁТ НЕ 2 ИТЕРАТОРА А ИТЕР НА ПЕРВЫЙ ЭЛ И ДЛИНУ СРЕЗА ЁБАНА
                                if (Temp.substr(Temp.substr(0, 23).find(TemporaryData), Temp.substr(0, 23).find(TemporaryData) + TemporaryData.size()) == TemporaryData) {
                                    cout << "Должна произойти запись по 1.3 условию" << endl;
                                    Information.resize(Information.size() + 1);
                                    Information[i].ComputerLabel = (Temp.substr(0, Temp.find(" ")));
                                    Information[i].NumberClass = (Temp.substr(23, Temp.substr(23, 45).find(" ")));
                                    Information[i].ComputerFubricNumber = (Temp.substr(46));
                                    Information[i].NumbersTerminal = "---";
                                    Information[i].NumbersVneshUstroystv = "---";
                                    
                                    i++;
                                }
                            }
                            break;
                        case 2:
                            cout << "Должна произойти запись по 2.1 условию" << endl;
                            if (Temp.find(TemporaryData) >= 24 && Temp.find(TemporaryData) <= 46) {
                                cout << "Должна произойти запись по 2.2 условию" << endl;
                                if (Temp.substr(Temp.substr(24, 46).find(TemporaryData), Temp.substr(24, 46).find(TemporaryData) + TemporaryData.size() - 1) == TemporaryData) {
                                    cout << "Должна произойти запись по 2.3 условию" << endl;
                                    Information.resize(Information.size() + 1);
                                    Information[i].ComputerLabel = (Temp.substr(0, Temp.find(" ")));
                                    Information[i].NumberClass = (Temp.substr(24, Temp.substr(24, 46).find(" ")));
                                    Information[i].ComputerFubricNumber = (Temp.substr(47));
                                    Information[i].NumbersTerminal = "---";
                                    Information[i].NumbersVneshUstroystv = "---";

                                    i++;
                                }
                            }
                            break;
                        case 3:
                            cout << "Должна произойти запись по 3 условию" << endl;
                            if (Temp.find(TemporaryData) >= 47 && Temp.find(TemporaryData) <= 68) {
                                if (Temp.substr(Temp.substr(47).find(TemporaryData), Temp.substr(47).find(TemporaryData) + TemporaryData.size() - 1) == TemporaryData) {
                                    cout << "Должна произойти запись по 3 условию" << endl;
                                    Information.resize(Information.size() + 1);
                                    Information[i].ComputerLabel = (Temp.substr(0, Temp.find(" ")));
                                    Information[i].NumberClass = (Temp.substr(24, Temp.substr(24, 46).find(" ")));
                                    Information[i].ComputerFubricNumber = (Temp.substr(47));
                                    Information[i].NumbersTerminal = "---";
                                    Information[i].NumbersVneshUstroystv = "---";

                                    i++;
                                }
                            }
                            break;
                        }
                    }
                    File.close();
                }
                else {
                    cout << "Файл не открылся" << endl;

                } // Файл не открылся
            }

            cout << "Найдено совпадений: " << Information.size() << endl;

            if (Information.size() > 2 && !Information[0].ComputerLabel.empty()) {
                bool running = true;
                int Pages = 0;
                //int i = 0;
                while (running) {

                    system("cls");
                    cout << "Найдено " << Information.size() << " совпадений: " << endl;
                    cout << "Марка ЭВМ: " << Information[Pages].ComputerLabel << endl;
                    cout << "Номер кафедры: " << Information[Pages].NumberClass << endl;
                    cout << "Заводской номер ЭВМ: " << Information[Pages].ComputerFubricNumber << endl;
                    cout << "Колличество терминалов: " << Information[Pages].NumbersTerminal << endl;
                    cout << "Колличество внешних запоминающий устройств: " << Information[Pages].NumbersVneshUstroystv << endl;
                    cout << "Страница " << (Pages + 1) << " из " << Information.size() << endl;
                    cout << "Для переключения страниц используйте клавиши стрелочек влево и вправо, для выхода нажмите клавишу ESC" << endl;

                    int key = _getch();

                    // Обработка специальных клавиш (стрелки)
                    if (key == 0 || key == 224) {
                        key = _getch();
                        switch (key) {
                        case KEY_RIGHT:
                            Pages = (Pages + 1) % Information.size(); // Цикличная прокрутка вправо
                            break;
                        case KEY_LEFT:
                            Pages = (Pages - 1 + Information.size()) % Information.size(); // Цикличная прокрутка влево
                            break;
                        }
                    }

                    else if (key == ESC) {
                        running = false;
                    }

                }
            }

            else if ((Information.size() == 1 && !Information[0].ComputerLabel.empty()) || (Information.size() == 2 && Information[1].ComputerLabel.empty())) {
                bool running = true;
                int i = 0;
                while (running) {

                    system("cls");
                    cout << "Марка ЭВМ: " << Information[i].ComputerLabel << endl;
                    cout << "Номер кафедры: " << Information[i].NumberClass << endl;
                    cout << "Заводской номер ЭВМ: " << Information[i].ComputerFubricNumber << endl;
                    cout << "Колличество терминалов: " << Information[i].NumbersTerminal << endl;
                    cout << "Колличество внешних запоминающий устройств: " << Information[i].NumbersVneshUstroystv << endl;
                    cout << "Для выхода нажмите клавишу ESC" << endl;
                    int key = _getch();
                    if (key == ESC) {
                        running = false;
                    }
                }
            }

            else {
                cout << "Совпадений не найдено, для выхода нажмите любую клавишу...";
                _getch();
            }


        }
        else {
            cout << "Папка не найдена" << endl;

        }
    }

    return Information;
}


void InfoInConsole() {

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
                    FindInfo(selected + 1);
                break;
            }
        }
        // Обработка цифровых клавиш '1' - '5' 
        else if (key >= '1' && key <= '5') {
            if (key - '1' == 0) {
                FindInfo(1);
            }
            else if (key - '1' == 1) {
                FindInfo(2);

            }
            else if (key - '1' == 2) {
                FindInfo(3);
            }
            else if (key - '1' == 3) {
                FindInfo(4);
            }
            else if (key - '1' == 4) {
                FindInfo(5);
            }
        }

        // Выход на ESC
        else if (key == ESC) {
            running = false;
        }

        else if (key == ENTER) {
            //running = false;
            if (selected == 0) {
                FindInfo(selected + 1);
            }
            else if (selected == 1) {
                FindInfo(selected + 1);
            }
            else if (selected == 2) {
                FindInfo(selected + 1);
            }
            else if (selected == 3) {
                FindInfo(selected + 1);
            }
            else if (selected == 4) {
                FindInfo(selected + 1);
            }
        }
    }

}
