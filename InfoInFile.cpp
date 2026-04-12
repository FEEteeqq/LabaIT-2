#include "Header.h"

string ExitFileName() {
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
        else {
            // Проверка есть ли в названии файла расширение, если есть то удаляем его
            if (NameFile.size() > 3 && NameFile.substr(NameFile.size() - 4, 4) == ".txt") {
                NameFile.erase(NameFile.size() - 4, 4);
            }
            // Проверка размера имени файла
            if (NameFile.size() > 40) {
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
                        else if (Key == ENTER){
                            Runnign = false;
                        }
                    }
                }
            }
        }
    }
    return NameFile;
}

string ChooseFile(string Path, bool OnlyName) {
    // При выборе входных файлов необходимо проверять не пустые ли они (есть ли хотя-бы одна строчка после заголовка) и в случае если они пустые сообщить об этом пользователю и предложить ему
    // на выбор: 1) Обновить входящие файлы (и сразу же проверить пустой ли теперь файл) 2) Выбрать другой файл 3) Вернуться в меню создания и записи выходного файла и скинуть выбранный файл
    char path[MAX_PATH];
    for (int i = 0; i < Path.size(); i++) {
        path[i] = Path[i];
    }
    path[Path.size()] = '\0';
    char filename[MAX_PATH];
    OPENFILENAMEA ofn;
    ZeroMemory(&filename, sizeof(filename));
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Text Files\0*.txt\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = "Выберете необходимый файл";
    ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
    ofn.lpstrInitialDir = path; // Указать путь папки с файлами
    if (GetOpenFileNameA(&ofn)) {
        string FileName = filename;
        if (OnlyName) {
            return FileName.substr(FileName.find_last_of("/\\") + 1);
        }
        else {
            return FileName;
        }
    }
    else {
        system("cls");
        //Обработка ошибок и закрытия проводника без выбранного файла
        switch (CommDlgExtendedError()) {
        case CDERR_DIALOGFAILURE: std::cout << "CDERR_DIALOGFAILURE\n";   break;
        case CDERR_FINDRESFAILURE: std::cout << "CDERR_FINDRESFAILURE\n";  break;
        case CDERR_INITIALIZATION: std::cout << "CDERR_INITIALIZATION\n";  break;
        case CDERR_LOADRESFAILURE: std::cout << "CDERR_LOADRESFAILURE\n";  break;
        case CDERR_LOADSTRFAILURE: std::cout << "CDERR_LOADSTRFAILURE\n";  break;
        case CDERR_LOCKRESFAILURE: std::cout << "CDERR_LOCKRESFAILURE\n";  break;
        case CDERR_MEMALLOCFAILURE: std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
        case CDERR_MEMLOCKFAILURE: std::cout << "CDERR_MEMLOCKFAILURE\n";  break;
        case CDERR_NOHINSTANCE: std::cout << "CDERR_NOHINSTANCE\n";     break;
        case CDERR_NOHOOK: std::cout << "CDERR_NOHOOK\n";          break;
        case CDERR_NOTEMPLATE: std::cout << "CDERR_NOTEMPLATE\n";      break;
        case CDERR_STRUCTSIZE: std::cout << "CDERR_STRUCTSIZE\n";      break;
        case FNERR_BUFFERTOOSMALL: std::cout << "FNERR_BUFFERTOOSMALL\n";  break;
        case FNERR_INVALIDFILENAME: std::cout << "FNERR_INVALIDFILENAME\n"; break;
        case FNERR_SUBCLASSFAILURE: std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
        default: std::cout << "Файл не был выбран\n";
            cout << "Для возврата нажмите любую клавишу...";
            _getch();
        }
    }
    return "";
}

bool CreateAndWriteFile(string FirstFile, string SecondFile, string ExitFile) /* Функция для создания и заполнение(данными из выбранных файлов) выходного файла */  {
    if ((FirstFile != "Не выбран" || SecondFile != "Не выбран") && ExitFile != "Название не задано") {
        vector<FullString> Data;
        if (FirstFile != "Не выбран") {
            std::string FirstPath = TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 1 типа\\"; // Путь к папке с файлами 1 типа
            int i = -1;
            ifstream File(FirstPath + FirstFile);
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
                cout << "Файл не открылся" << endl;
                cout << "Для возврата в главное меню нажмите любую клавишу..." << endl;
                _getch();
                return false;
            }
        }
        if (SecondFile != "Не выбран") {
            std::string SecondPath = TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 2 типа\\"; // Путь к папке с файлами 2 типа
            int i = Data.size() - 1;
            int j = Data.size() - 1;
            ifstream File(SecondPath + SecondFile);
            if (File.is_open()) {
                string Temp;
                while (getline(File, Temp)) {
                    bool Flag = true;
                    for (int i = 0; i < Data.size(); i++) {
                        if (!Temp.empty() && Temp.substr(0, 22) == Data[i].ComputerLabel) {
                            Data[i].NumbersTerminal = Temp.substr(23, 25);
                            Data[i].NumbersVneshUstroystv = Temp.substr(50);
                            for (int j = Data[i].NumbersVneshUstroystv.size(); j < 41; j++) {
                                Data[i].NumbersVneshUstroystv += " ";
                            }
                            Flag = false;
                        }
                    }
                    if (Flag && !Temp.empty()) {
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
                File.close();
            }
            else {
                system("cls");
                cout << "Файл не открылся" << endl;
                cout << "Для возврата в главное меню нажмите любую клавишу..." << endl;
                _getch();
                return false;
            }
        }
        ofstream File(TakePathToExeFile() + "\\LabaIT 2\\Выходные файлы\\" + ExitFile);
        File << "Марка ЭВМ             Номера кафедры       Заводской номер ЭВМ    Количество терминалов    Количество внешних запоминающих устройств" << endl;
        for (int i = 0; i < Data.size(); i++) {
            File << Data[i].ComputerLabel << Data[i].NumberClass << Data[i].ComputerFubricNumber << Data[i].NumbersTerminal << Data[i].NumbersVneshUstroystv << endl;
        }
        File.close();
        system("cls");
        cout << "Файл успешно создан и заполнен" << endl;
        cout << "Для возврата в главное меню нажмите любую клавишу..." << endl;
        _getch();
        return false;
    }
    else {
        return true;
    }
}

void DrawInfoFileMenu(int selectedItem, string FirstFile, string SecondFile, string ExitFile, string Status) {
    vector<string> menuItems = { "1. Файл первого типа: " + FirstFile, "2. Файл второго типа: " + SecondFile, "3. Выходной файл: " + ExitFile, "4. Создать и заполнить файл" + Status};
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

bool performActionWithFile(int itemIndex, string& FirstFile, string& SecondFile, string& ExitFile) {
    system("cls");
    switch (itemIndex) {
    case 0:
        FirstFile = ChooseFile(TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 1 типа", true);
        if (FirstFile.empty()) {
            FirstFile = "Не выбран";
        }
        return true;
        break;
    case 1:
        SecondFile = ChooseFile(TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 2 типа", true);
        if (SecondFile.empty()) {
            SecondFile = "Не выбран";
        }
        return true;
        break;
    case 2:
        ExitFile = ExitFileName();
        if (ExitFile.empty()) {
            ExitFile = "Название не задано";
        }
        else {
            ExitFile += ".txt";
        }
        return true;
        break;
    case 3:
        return CreateAndWriteFile(FirstFile, SecondFile, ExitFile);
        break;
    }
}

void InfoInFile() {
    system("cls");
    int selected = 0;
    bool running = true;
    string FirstFile = "Не выбран";
    string SecondFile = "Не выбран";
    string ExitFile = "Название не задано";
    string Status = " (Недоступно)";
    while (running) {
        if ((FirstFile != "Не выбран" || SecondFile != "Не выбран") && ExitFile != "Название не задано") {
            Status = " ( Доступно )";
        }
        else {
            Status = " ( Недоступно )";
        }
        DrawInfoFileMenu(selected, FirstFile, SecondFile, ExitFile, Status);
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
                running = performActionWithFile(selected, FirstFile, SecondFile, ExitFile);
                break;
            }
        }
        // Обработка цифровых клавиш '1' - '4' 
        else if (key >= '1' && key <= '4') {
            running = performActionWithFile(key - '1', FirstFile, SecondFile, ExitFile);
        }
        // Выход на ESC
        else if (key == ESC) {
            running = false;
        }
        // Обработка клавиши Enter
        else if (key == ENTER) {
            running = performActionWithFile(selected, FirstFile, SecondFile, ExitFile);
        }
    }
}