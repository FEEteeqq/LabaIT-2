#include "Header.h"

void DrawInfoInConsoleMenu(int selectedItem) { // Функция отрисовки МЕНЮ ВЫБОРА ПОЛЯ ДЛЯ ПОИСКА ИНФОРМАЦИИ
    vector<string> menuItems = { "1. Марка ЭВМ", "2. Номер кафедры",
        "3. Заводской номер ЭВМ", "4. Количество терминалов", "5. Количество внешних запоминающих устройств"};
    system("cls");
    cout << "   ---- МЕНЮ ВЫБОРА ПОЛЯ ДЛЯ ПОИСКА ИНФОРМАЦИИ ----    " << endl << endl;
    cout << "По какому полю будет поиск информации?" << endl;
    for (int i = 0; i < menuItems.size(); ++i) {
        if (i == selectedItem) {
            cout << "-> " << menuItems[i] << endl;
        }
        else {
            cout << "    " << menuItems[i] << endl;
        }
    }
    cout << endl << "Для возврата в главное меню нажмите клавишу ESC" << endl;
}

void FindInfo(int element) { // Функция нахождения информации для вывода в консоль
    system("cls");
    string TemporaryData;
    vector<FullString> Information;
    cout << "Для возврата в меню выбора пункта поиска ничего не вводите и нажмите клавишу Enter" << endl;
    
    switch (element) {
    case 1 /*Поиск по Марке ЭВМ*/:
        cout << "Поиск происходит с учётом регистра и по частичному совпадению" << endl << endl;
        cout << "Введите Марку ЭВМ: ";
        break;
    case 2 /*Поиск по Номеру кафедры*/:
        cout << "Поиск происходит с учётом регистра и по полному совпадению" << endl << endl;
        cout << "Введите номер кафедры: ";
        break;
    case 3 /*Поиск по Заводскому номеру ЭВМ*/:
        cout << "Поиск происходит с учётом регистра и по частичному совпадению" << endl << endl;
        cout << "Введите заводской номер ЭВМ: ";
        break;
    case 4 /*Поиск по Количеству терминалов*/:
        cout << "Поиск происходит с учётом регистра и по полному совпадению" << endl << endl;
        cout << "Введите количество терминалов: ";
        break;
    case 5 /*Поиск по Количеству внешних запоминающих устройств*/:
        cout << "Поиск происходит с учётом регистра и по полному совпадению" << endl << endl;
        cout << "Введите количество внешних запоминающих устройств: ";
        break;
    }

    getline(cin, TemporaryData);
    if (TemporaryData.empty()) {} /*Возврат в меню выбора пункта для поиска*/
    else {
        if (element < 4) {
            std::string FirstPath = TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 1 типа\\"; // Путь к папке с файлами 1 типа
            std::string SecondPath = TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 2 типа\\"; // Путь к папке с файлами 2 типа
            int i = 0;
            for (const auto& FilePath : std::filesystem::directory_iterator(FirstPath)) { // Цикл необходимый для получения имён файлов из папки
                string FileName = FilePath.path().filename().string(); // Оставляем от полного пути только имя файла
                ifstream File(FirstPath + FileName);
                if (File.is_open()) {
                    string Temp;
                    while (getline(File, Temp)) {
                        switch (element) {
                        case 1: // Поиск по марке ЭВМ 1 тип файла
                            if (!Temp.empty() && Temp.find(TemporaryData) < 23) {
                                if (Temp.substr(Temp.substr(0, 23).find(TemporaryData), TemporaryData.size()) == TemporaryData) {
                                    Information.resize(Information.size() + 1);
                                    Information[i].FirstFileName = FileName;
                                    Information[i].SecondFileName = "---";
                                    Information[i].ComputerLabel = (Temp.substr(0, Temp.find(" ")));
                                    Information[i].NumberClass = (Temp.substr(23, Temp.substr(23, 23).find(" ")));
                                    Information[i].ComputerFubricNumber = (Temp.substr(46));
                                    Information[i].NumbersTerminal = "---";
                                    Information[i].NumbersVneshUstroystv = "---";
                                    i++;
                                }
                            }
                            break;
                        case 2: // Поиск по номеру кафедры
                            if (!Temp.empty() && Temp.substr(23).find(TemporaryData) < 23) {
                                if (Temp.substr(23, Temp.substr(23, 14).find(" ")) == TemporaryData) {
                                    Information.resize(Information.size() + 1);
                                    Information[i].FirstFileName = FileName;
                                    Information[i].SecondFileName = "---";
                                    Information[i].ComputerLabel = (Temp.substr(0, Temp.find(" ")));
                                    Information[i].NumberClass = (Temp.substr(23, Temp.substr(23, 23).find(" ")));
                                    Information[i].ComputerFubricNumber = (Temp.substr(46));
                                    Information[i].NumbersTerminal = "---";
                                    Information[i].NumbersVneshUstroystv = "---";
                                    i++;
                                }
                            }
                            break;
                        case 3: // Поиск по заводскому номеру ЭВМ
                            if (!Temp.empty() && (Temp.substr(46).find(TemporaryData) + 46) >= 46 && (Temp.substr(46).find(TemporaryData) + 46) < 66) {
                                if (Temp.substr(Temp.substr(46).find(TemporaryData) + 46, TemporaryData.size()) == TemporaryData) {
                                    Information.resize(Information.size() + 1);
                                    Information[i].FirstFileName = FileName;
                                    Information[i].SecondFileName = "---";
                                    Information[i].ComputerLabel = (Temp.substr(0, Temp.find(" ")));
                                    Information[i].NumberClass = (Temp.substr(23, Temp.substr(23, 23).find(" ")));
                                    Information[i].ComputerFubricNumber = (Temp.substr(46));
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
                    cout << "Для продолжения нажсите любую клавишу" << endl;
                    _getch();
                }
            }
            for (const auto& FilePath : std::filesystem::directory_iterator(SecondPath)) {
                string FileName = FilePath.path().filename().string(); // Оставляем от полного пути только имя файла
                ifstream File(SecondPath + FileName);
                if (File.is_open()) {
                    string Temp;
                    while (getline(File, Temp)) {
                        bool Flag = true;
                        for (int i = 0; i < Information.size(); i++) { // Если находим совпадение по марке ЭВМ до заполняем пустые поля
                            if (!Temp.empty() && Temp.substr(0, Temp.find(" ")) == Information[i].ComputerLabel) {
                                Information[i].SecondFileName = FileName;
                                Information[i].NumbersTerminal = Temp.substr(23, Temp.substr(23).find(" "));
                                Information[i].NumbersVneshUstroystv = Temp.substr(50);
                                Flag = false;
                            }
                        }
                        if (element == 1 && Flag) { // Поиск по марке ЭВМ 2 тип файла
                            if (!Temp.empty() && Temp.find(TemporaryData) < 23) {
                                int i = Information.size();
                                Information.resize(Information.size() + 1);
                                Information[i].SecondFileName = FileName;
                                Information[i].FirstFileName = "---";
                                Information[i].ComputerLabel = Temp.substr(0, Temp.find(" "));
                                Information[i].NumberClass = "---";
                                Information[i].ComputerFubricNumber = "---";
                                Information[i].NumbersTerminal = Temp.substr(23, Temp.substr(23).find(" "));
                                Information[i].NumbersVneshUstroystv = Temp.substr(50);
                            }
                        }
                    }
                }
                else {
                    cout << "Файл не открылся" << endl;
                    cout << "Для продолжения нажсите любую клавишу" << endl;
                    _getch();
                }
            }
        }
        else if (element > 3) {
            std::string FirstPath = TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 1 типа\\"; // Путь к папке с файлами 1 типа
            std::string SecondPath = TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 2 типа\\"; // Путь к папке с файлами 2 типа
            int i = 0;
            for (const auto& FilePath : std::filesystem::directory_iterator(SecondPath)) { // Цикл необходимый для получения имён файлов из папки
                string FileName = FilePath.path().filename().string(); // Оставляем от полного пути только имя файла
                ifstream File(SecondPath + FileName);
                if (File.is_open()) {
                    string Temp;
                    while (getline(File, Temp)) {
                        switch (element) {
                        case 4: // Поиск по количеству терминалов
                            if (!Temp.empty() && Temp.substr(23).find(TemporaryData) <= 26) {
                                if (Temp.substr(23, Temp.substr(23, 3).find(" ")) == TemporaryData) {
                                    Information.resize(Information.size() + 1);
                                    Information[i].FirstFileName = "---";
                                    Information[i].SecondFileName = FileName;
                                    Information[i].ComputerLabel = (Temp.substr(0, Temp.find(" ")));
                                    Information[i].NumberClass = "---";
                                    Information[i].ComputerFubricNumber = "---";
                                    Information[i].NumbersTerminal = (Temp.substr(23, Temp.substr(23, 26).find(" ")));
                                    Information[i].NumbersVneshUstroystv = (Temp.substr(50));
                                    i++;
                                }
                            }
                            break;
                        case 5: // Поиск по количеству внешних запоминающий устройств 
                            if (!Temp.empty() && Temp.substr(50).find(TemporaryData) + 50 <= 53) {
                                if (Temp.substr(50, Temp.substr(50, 3).find(" ")) == TemporaryData) {
                                    Information.resize(Information.size() + 1);
                                    Information[i].FirstFileName = "---";
                                    Information[i].SecondFileName = FileName;
                                    Information[i].ComputerLabel = (Temp.substr(0, Temp.find(" ")));
                                    Information[i].NumberClass = "---";
                                    Information[i].ComputerFubricNumber = "---";
                                    Information[i].NumbersTerminal = (Temp.substr(23, Temp.substr(23, 26).find(" ")));
                                    Information[i].NumbersVneshUstroystv = (Temp.substr(50));
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
                    cout << "Для продолжения нажсите любую клавишу" << endl;
                    _getch();
                }
            }
            for (const auto& FilePath : std::filesystem::directory_iterator(FirstPath)) {
                string FileName = FilePath.path().filename().string(); // Оставляем от полного пути только имя файла
                ifstream File(FirstPath + FileName);
                if (File.is_open()) {
                    string Temp;
                    while (getline(File, Temp)) {
                        for (int i = 0; i < Information.size(); i++) {
                            if (!Temp.empty() && Temp.substr(0, Temp.find(" ")) == Information[i].ComputerLabel) {
                                Information[i].FirstFileName = FileName;
                                Information[i].NumberClass = Temp.substr(23, Temp.substr(23).find(" "));
                                Information[i].ComputerFubricNumber = Temp.substr(46);
                            }
                        }
                    }
                }
                else {
                    cout << "Файл не открылся" << endl;
                    cout << "Для продолжения нажсите любую клавишу" << endl;
                    _getch();
                }
            }
        }
        if (Information.size() > 1 && !Information[1].ComputerLabel.empty()) {
            bool running = true;
            int Pages = 0;
            while (running) {
                system("cls");
                cout << "Найдено совпадений: " << Information.size() << endl << endl;
                cout << "Файл 1 типа: " << Information[Pages].FirstFileName << endl;
                cout << "Файл 2 типа: " << Information[Pages].SecondFileName << endl << endl;
                cout << "Марка ЭВМ: " << Information[Pages].ComputerLabel << endl;
                cout << "Номер кафедры: " << Information[Pages].NumberClass << endl;
                cout << "Заводской номер ЭВМ: " << Information[Pages].ComputerFubricNumber << endl;
                cout << "Колличество терминалов: " << Information[Pages].NumbersTerminal << endl;
                cout << "Колличество внешних запоминающий устройств: " << Information[Pages].NumbersVneshUstroystv << endl << endl;
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
                cout << "Файл 1 типа: " << Information[i].FirstFileName << endl;
                cout << "Файл 2 типа: " << Information[i].SecondFileName << endl << endl;
                cout << "Марка ЭВМ: " << Information[i].ComputerLabel << endl;
                cout << "Номер кафедры: " << Information[i].NumberClass << endl;
                cout << "Заводской номер ЭВМ: " << Information[i].ComputerFubricNumber << endl;
                cout << "Колличество терминалов: " << Information[i].NumbersTerminal << endl;
                cout << "Колличество внешних запоминающий устройств: " << Information[i].NumbersVneshUstroystv << endl << endl;
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
}

void InfoInConsole() { // Функция обработки нажатия клавиш в меню
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
        // Обработка клавиши Enter
        else if (key == ENTER) {
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
