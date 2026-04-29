#include "Header.h"

string fileFirstFilePath = "";
string fileSecondFilePath = "";
string fileFirstFileName = "Не выбран";
string fileSecondFileName = "Не выбран";
string fileExitFileName = "Имя файла не задано";


string ExitFileName() { // Функция для написания имени выходного файла
    system("cls");
    cout << "Файл будет иметь расширение .txt" << endl;
    cout << "Имя файла не должно быть больше 40 символов" << endl;
    cout << "Для возврата ничего не вводите и нажмите клавишу Enter" << endl;
    cout << "Введите имя файла: ";
    string NameFile;
    std::getline(std::cin, NameFile);
    // Проверка на пустую строку
    if (NameFile.empty()) {}
    else {
        // Проверка не состоит ли имя файла только из расширения
        if (NameFile == ".txt") {
            system("cls");
            cout << "Ошибка! Файл должен содержать не только расширение, необходимо изменить имя файла" << endl;
            cout << "Для возврата в меню нажмите ESC, для повторного ввода нажмите любую другую клавишу" << endl;
            NameFile.clear();
            int Key;
            Key = _getch();
            if (Key == ESC) {}

            else {
                return ExitFileName();
            }
        }
        // Проверка есть ли в названии файла расширение, если есть то удаляем его
        else if (NameFile.size() > 3 && NameFile.substr(NameFile.size() - 4, 4) == ".txt") {
            NameFile.erase(NameFile.size() - 4, 4);
        }
        // Проверка размера имени файла
        else if (NameFile.size() > 40) {
            system("cls");
            cout << "Ошибка! Файл должен содержать не больше 40 символов, необходимо изменить имя файла" << endl;
            cout << "Для возврата в меню нажмите ESC, для повторного ввода нажмите любую другую клавишу" << endl;
            NameFile.clear();
            int Key;
            Key = _getch();
            if (Key == ESC) {}
            else {
                return ExitFileName();
            }
        }
        // Проверка на запрещённые символы
        else if (NameFile.find_first_of("\\|/:*?<>\"")) {
            system("cls");
            cout << "Ошибка! Файл содержит запрещённые символы, необходимо изменить имя файла" << endl;
            cout << "Для возврата в меню нажмите ESC, для повторного ввода нажмите любую другую клавишу" << endl;
            NameFile.clear();
            int Key;
            Key = _getch();
            if (Key == ESC) {}
            else {
                return ExitFileName();
            }
        }
        else {
            // Проверка на существование файла с таким именем
            ifstream Test(TakePathToExeFile() + "\\LabaIT 2\\Выходные файлы\\" + NameFile + ".txt");
            if (Test.is_open()) {
                system("cls");
                cout << "Файл с таким именем уже существует." << endl << "Для изменения имени файла нажмите ESC" << endl;
                cout << "Для перезаписывания файла нажмите клавишу Enter" << endl;
                bool Runnign = true;
                while (Runnign) {
                    int Key;
                    Key = _getch();
                    if (Key == ESC) {
                        NameFile = ExitFileName();
                        Runnign = false;
                    }
                    else if (Key == ENTER) {
                        Runnign = false;
                    }
                }
            }
        }
    }
    return NameFile;
}

bool CreateAndWriteFile() /* Функция для создания и заполнение (данными из выбранных файлов) выходного файла */ {
    if ((fileFirstFileName != "Не выбран" || fileSecondFileName != "Не выбран") && fileExitFileName != "Имя файла не задано") {
        vector<FullString> Data;
        if (fileFirstFileName != "Не выбран") {
            std::string FirstPath = TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 1 типа\\"; // Путь к папке с файлами 1 типа
            int i = -1;
            ifstream File(fileFirstFilePath);
            if (File.is_open()) {
                string Temp;
                while (getline(File, Temp)) {

                    if (i > -1 && !Temp.empty()) {
                        Data.resize(Data.size() + 1);
                        Data[i].ComputerLabel = (Temp.substr(0, 22));
                        Data[i].NumberClass = (Temp.substr(23, 21));
                        Data[i].ComputerFubricNumber = (Temp.substr(46));
                        for (int j = Data[i].ComputerFubricNumber.size(); j < 23; j++) {
                            Data[i].ComputerFubricNumber += " ";
                        }
                        Data[i].NumbersTerminal = "---";
                        for (int j = Data[i].NumbersTerminal.size(); j < 25; j++) {
                            Data[i].NumbersTerminal += " ";
                        }
                        Data[i].NumbersVneshUstroystv = "---";
                        for (int j = Data[i].NumbersVneshUstroystv.size(); j < 41; j++) {
                            Data[i].NumbersVneshUstroystv += " ";
                        }
                    }
                    i++;
                }
                File.close();
            }
            else {
                system("cls");
                cout << "Файл '" + fileFirstFileName +"' не открылся" << endl;
                cout << "Для возврата в главное меню нажмите любую клавишу..." << endl;
                _getch();
                return false;
            }
        }
        if (fileSecondFileName != "Не выбран") {
            std::string SecondPath = TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 2 типа\\"; // Путь к папке с файлами 2 типа
            int i = Data.size() - 1;
            int j = Data.size() - 1;
            ifstream File(fileSecondFilePath);
            if (File.is_open()) {
                string Temp;
                while (getline(File, Temp)) {
                    if (!Temp.empty()) {
                        bool Flag = true;
                        for (int i = 0; i < Data.size(); i++) {
                            if (Temp.substr(0, 22) == Data[i].ComputerLabel) {
                                Data[i].NumbersTerminal = Temp.substr(23, 25);
                                Data[i].NumbersVneshUstroystv = Temp.substr(50);
                                for (int j = Data[i].NumbersVneshUstroystv.size(); j < 41; j++) {
                                    Data[i].NumbersVneshUstroystv += " ";
                                }
                                Flag = false;
                            }
                        }
                        if (Flag) {
                            if (i > j) {
                                Data.resize(Data.size() + 1);
                                Data[i].ComputerLabel = Temp.substr(0, 22);
                                Data[i].NumberClass = "---";
                                for (int j = Data[i].NumberClass.size(); j < 21; j++) {
                                    Data[i].NumberClass += " ";
                                }
                                Data[i].ComputerFubricNumber = "---";
                                for (int j = Data[i].ComputerFubricNumber.size(); j < 23; j++) {
                                    Data[i].ComputerFubricNumber += " ";
                                }
                                Data[i].NumbersTerminal = Temp.substr(23, 25);
                                Data[i].NumbersVneshUstroystv = Temp.substr(50);
                                for (int j = Data[i].NumbersVneshUstroystv.size(); j < 41; j++) {
                                    Data[i].NumbersVneshUstroystv += " ";
                                }
                            }
                            i++;
                        }
                    }
                }
                File.close();
            }
            else {
                system("cls");
                cout << "Файл '" + fileSecondFileName + "' не открылся" << endl;
                cout << "Для возврата в главное меню нажмите любую клавишу..." << endl;
                _getch();
                return false;
            }
        }
        ofstream File(TakePathToExeFile() + "\\LabaIT 2\\Выходные файлы\\" + fileExitFileName);
        File << "Марка ЭВМ             Номера кафедры       Заводской номер ЭВМ    Количество терминалов    Количество внешних запоминающих устройств" << endl;
        for (int i = 0; i < Data.size(); i++) {
            File << Data[i].ComputerLabel << Data[i].NumberClass << Data[i].ComputerFubricNumber << Data[i].NumbersTerminal << Data[i].NumbersVneshUstroystv << endl;
        }
        File.close();
        system("cls");
        cout << "Файл '" + fileExitFileName +"' успешно создан и заполнен" << endl;
        cout << "Для возврата в главное меню нажмите любую клавишу..." << endl;
        _getch();
        fileExitFileName = "Имя файла не задано";
        return false;
    }
    else {
        return true;
    }
}

void DrawInfoFileMenu(int selectedItem, string Status) {
    // Функция отрисовки МЕНЮ ВЫВОДА ДАННЫХ В ФАЙЛ
    vector<string> menuItems = { "1. Файл первого типа: " + fileFirstFileName, "2. Файл второго типа: " + fileSecondFileName, "3. Выходной файл: " + fileExitFileName, "4. Создать и заполнить файл" + Status };
    system("cls");
    cout << "   ---- МЕНЮ ВЫВОДА ДАННЫХ В ФАЙЛ ----" << endl << endl;
    cout << "Необходимо выбрать хотя-бы один файл и обязательно задать имя выходного файла" << endl << endl;
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

bool PerformActionWithFile(int itemIndex) {
    // Функция обработки выбранного пункта меню вывода данных в файл
    system("cls");
    switch (itemIndex) {
    case 0:
        fileFirstFilePath = ChooseFile(TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 1 типа", false);
        if (fileFirstFilePath.empty()) {
            fileFirstFileName = "Не выбран";
        }
        else {
            ifstream File(fileFirstFilePath);
            string Temp;
            int i = 0;
            while (getline(File, Temp)) {
                if (i == 0) {
                    if (Temp != "Марка ЭВМ              Номера кафедры         Заводской номер ЭВМ") {
                        system("cls");
                        cout << "Выбранный файл не является файлом первого типа, необходимо выбрать другой файл" << endl;
                        cout << "Для продолжения нажмите любую клавишу..." << endl;
                        _getch();
                        File.close();
                        fileFirstFilePath = "";
                        fileFirstFileName = "Не выбран";
                        break;
                    }
                }
                if (!Temp.empty()) {
                    i++;
                }
                else {
                    system("cls");
                    cout << "Выбранный файл пустой, необходимо выбрать другой файл" << endl;
                    cout << "Для продолжения нажмите любую клавишу..." << endl;
                    _getch();
                    File.close();
                    fileFirstFilePath = "";
                    fileFirstFileName = "Не выбран";
                    break;
                }
                if (i > 1) {
                    fileFirstFileName = fileFirstFilePath.substr(fileFirstFilePath.find_last_of("/\\") + 1);
                    File.close();
                    break;
                }
            }
        }
        return true;
        break;
    case 1:
        fileSecondFilePath = ChooseFile(TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 2 типа", false);
        if (fileSecondFilePath.empty()) {
            fileSecondFileName = "Не выбран";
        }
        else {
            ifstream File(fileSecondFilePath);
            string Temp;
            int i = 0;
            while (getline(File, Temp)) {
                if (i == 0) {
                    if (Temp != "Марка ЭВМ              Количество терминалов      Количество внешних запоминающих устройств") {
                        system("cls");
                        cout << "Выбранный файл не является файлом второго типа, необходимо выбрать другой файл" << endl;
                        cout << "Для продолжения нажмите любую клавишу..." << endl;
                        _getch();
                        File.close();
                        fileSecondFilePath = "";
                        fileSecondFileName = "Не выбран";
                        break;
                    }
                }
                if (!Temp.empty()) {
                    i++;
                }
                else {
                    system("cls");
                    cout << "Выбранный файл пустой, необходимо выбрать другой файл" << endl;
                    cout << "Для продолжения нажмите любую клавишу..." << endl;
                    _getch();
                    File.close();
                    fileSecondFilePath = "";
                    fileSecondFileName = "Не выбран";
                    break;
                }
                if (i > 1) {
                    fileSecondFileName = fileSecondFilePath.substr(fileSecondFilePath.find_last_of("/\\") + 1);
                    File.close();
                    break;
                }
            }
        }
        return true;
        break;
    case 2:
        fileExitFileName = ExitFileName();
        if (fileExitFileName.empty()) {
            fileExitFileName = "Имя файла не задано";
        }
        else {
            fileExitFileName += ".txt";
        }
        return true;
        break;
    case 3:
        return CreateAndWriteFile();
        break;
    }
}

void InfoInFile() { // Функция обработки клавиш в меню вывода данных в файл
    system("cls");
    int selected = 0;
    bool running = true;
    string Status = " (Недоступно)";
    while (running) {
        if ((fileFirstFileName != "Не выбран" || fileSecondFileName != "Не выбран") && fileExitFileName != "Имя файла не задано") {
            Status = " ( Доступно )";
        }
        else {
            Status = " ( Недоступно )";
        }
        DrawInfoFileMenu(selected, Status);
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
                running = PerformActionWithFile(selected);
                break;
            }
        }
        // Обработка цифровых клавиш '1' - '4' 
        else if (key >= '1' && key <= '4') {
            running = PerformActionWithFile(key - '1');
        }
        // Выход на ESC
        else if (key == ESC) {
            running = false;
        }
        // Обработка клавиши Enter
        else if (key == ENTER) {
            running = PerformActionWithFile(selected);
        }
    }
}