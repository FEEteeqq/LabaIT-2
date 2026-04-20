#include "Header.h"

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
                        else if (Key == ENTER) {
                            Runnign = false;
                        }
                    }
                }
            }
        }
    }
    return NameFile;
}

string ChooseFile(string Path, bool OnlyName) { // Функция выбора файла через проводник
    char path[MAX_PATH];
    for (int i = 0; i < Path.size(); i++) {
        path[i] = Path[i];
    }
    path[Path.size()] = '\0';
    char filename[MAX_PATH];

    OPENFILENAMEA ofn;// Объявление структуры, которая содержит параметры для диалогового окна "Открыть файл"
    ZeroMemory(&filename, sizeof(filename));// Очистка (заполнение нулями) массива filename, чтобы в нем не было "мусора" перед использованием
    ZeroMemory(&ofn, sizeof(ofn));// Очистка структуры ofn — это важно, чтобы все неиспользуемые поля были гарантированно обнулены
    ofn.lStructSize = sizeof(ofn);// Указание размера структуры (Windows использует это для определения версии API)
    ofn.hwndOwner = NULL;// Дескриптор окна-владельца (NULL означает, что у диалога нет родительского окна)
    ofn.lpstrFilter = "Text Files\0*.txt\0"; // Фильтр типов файлов: в списке выбора будут отображаться только текстовые файлы (.txt) формат: "Название\0*.расширение\0"
    ofn.lpstrFile = filename;// Указатель на буфер (массив), в который будет записан путь к выбранному файлу
    ofn.nMaxFile = MAX_PATH;// Максимальный размер буфера под путь к файлу (обычно 260 символов)
    ofn.lpstrTitle = "Выберете необходимый файл";// Заголовок, который будет отображаться в верхней части окна выбора файла
    ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR; // Флаги поведения:
    //OFN_DONTADDTORECENT — не добавлять выбранный файл в список "Недавние документы"
    // OFN_FILEMUSTEXIST — пользователь может выбрать только реально существующий файл
    // OFN_NOCHANGEDIR - возвращает рабочую директорию программы в исходное состояние после закрытия окна
    ofn.lpstrInitialDir = path; // Начальная папка, которая откроется сразу при запуске диалога

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
        case CDERR_DIALOGFAILURE:
            // Окно не смогло создаться
            std::cout << "CDERR_DIALOGFAILURE\n"; break;
        case CDERR_FINDRESFAILURE:
            // Не удалось найти указанный шаблон (ресурс) окна в файле
            std::cout << "CDERR_FINDRESFAILURE\n"; break;
        case CDERR_LOADRESFAILURE:
            // Ресурс найден, но произошла ошибка при его загрузке
            std::cout << "CDERR_LOADRESFAILURE\n"; break;
        case CDERR_LOADSTRFAILURE:
            // Ошибка при попытке загрузить внутреннюю строку из ресурсов системы
            std::cout << "CDERR_LOADSTRFAILURE\n"; break;
        case CDERR_LOCKRESFAILURE:
            // Не удалось заблокировать память для загруженного ресурса
            std::cout << "CDERR_LOCKRESFAILURE\n"; break;
        case CDERR_INITIALIZATION:
            // Общая ошибка при попытке инициализировать диалог
            std::cout << "CDERR_INITIALIZATION\n"; break;
        case CDERR_MEMALLOCFAILURE:
            // Недостаточно памяти для работы диалогового окна
            std::cout << "CDERR_MEMALLOCFAILURE\n"; break;
        case CDERR_MEMLOCKFAILURE:
            // Ошибка при попытке заблокировать память для данных диалога
            std::cout << "CDERR_MEMLOCKFAILURE\n"; break;
        case CDERR_STRUCTSIZE:
            // Неверно указан lStructSize (размер структуры не совпадает с ожидаемым)
            std::cout << "CDERR_STRUCTSIZE\n"; break;
        case CDERR_NOHINSTANCE:
            // Указан флаг использования шаблона, но не передан hInstance приложения
            std::cout << "CDERR_NOHINSTANCE\n"; break;
        case CDERR_NOHOOK:
            // Указан флаг использования Hook-функции, но указатель lpfnHook пуст
            std::cout << "CDERR_NOHOOK\n"; break;
        case CDERR_NOTEMPLATE:
            // Указан флаг кастомного шаблона, но не передан сам шаблон lpTemplateName
            std::cout << "CDERR_NOTEMPLATE\n"; break;
        case FNERR_BUFFERTOOSMALL:
            // Размер буфера lpstrFile слишком мал для выбранного пути (nMaxFile)
            std::cout << "FNERR_BUFFERTOOSMALL\n"; break;
        case FNERR_INVALIDFILENAME:
            // Переданное имя файла содержит недопустимые символы или некорректно
            std::cout << "FNERR_INVALIDFILENAME\n"; break;
        case FNERR_SUBCLASSFAILURE:
            // Не удалось подменить процедуру окна
            std::cout << "FNERR_SUBCLASSFAILURE\n"; break;
        default: std::cout << "Файл не был выбран\n";
            cout << "Для возврата нажмите любую клавишу...";
            _getch();
        }
    }
    return "";
}

bool CreateAndWriteFile(string FirstFile, string SecondFile, string ExitFile) /* Функция для создания и заполнение (данными из выбранных файлов) выходного файла */ {
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
    // Функция отрисовки МЕНЮ ВЫВОДА ДАННЫХ В ФАЙЛ
    vector<string> menuItems = { "1. Файл первого типа: " + FirstFile, "2. Файл второго типа: " + SecondFile, "3. Выходной файл: " + ExitFile, "4. Создать и заполнить файл" + Status };
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

bool PerformActionWithFile(int itemIndex, string& FirstFile, string& SecondFile, string& ExitFile) {
    // Функция обработки выбранного пункта меню вывода данных в файл
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

void InfoInFile() { // Функция обработки клавиш в меню вывода данных в файл
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
                running = PerformActionWithFile(selected, FirstFile, SecondFile, ExitFile);
                break;
            }
        }
        // Обработка цифровых клавиш '1' - '4' 
        else if (key >= '1' && key <= '4') {
            running = PerformActionWithFile(key - '1', FirstFile, SecondFile, ExitFile);
        }
        // Выход на ESC
        else if (key == ESC) {
            running = false;
        }
        // Обработка клавиши Enter
        else if (key == ENTER) {
            running = PerformActionWithFile(selected, FirstFile, SecondFile, ExitFile);
        }
    }
}