#include "Header.h"

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

string GetDesktopPath() { // Функция для получения пути до рабочего стола
    char path[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, path))) {
        return std::string(path);
    }
    return ""; // Возвращаем пустую строку в случае ошибки
}

bool CreateFolder(std::string FolderNames) { // Функция создания новой папки
    if (_chdir((TakePathToExeFile() + "\\LabaIT 2" + "\\" + FolderNames).c_str()) != 0) /*Проверка на существования папки*/ {
        std::string desktopPath = TakePathToExeFile();
        std::string fullPath = desktopPath + "\\LabaIT 2" + "\\" + FolderNames; // Формируем полный путь
        // Используем _mkdir из <direct.h> для создания папки
        if (_mkdir(fullPath.c_str()) == 0) {
            return true;
        }
        else {
            return false;
        }
    }
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

void CheckFileInFirstProgram(bool Start) {
    // Функция проверки существования папки первой программы 
    // и в случае её существования происходит копирование файлов в новую программу

    std::string FirstPath = GetDesktopPath() + "\\Лабараторная по ИТ\\Файлы 1 типа"; // Путь к папке с файлами 1 типа
    std::string SecondPath = GetDesktopPath() + "\\Лабараторная по ИТ\\Файлы 2 типа"; // Путь к папке с файлами 2 типа

    if (_chdir((GetDesktopPath() + "\\Лабараторная по ИТ").c_str()) == 0) /*Проверка на существования папки*/ {
        if (_chdir((FirstPath).c_str()) == 0) {
            for (const auto& FilePath : std::filesystem::directory_iterator(FirstPath)) {
                string FileName = FilePath.path().filename().string();
                ifstream File(FirstPath + "\\" + FileName);
                string Temp;
                bool Flag = false;
                int i = 0;
                while (getline(File, Temp)) {
                    if (i == 0) {
                        if (Temp != "Марка ЭВМ              Номера кафедры         Заводской номер ЭВМ") {
                            break;
                        }
                    }
                    if (!Temp.empty()) {
                        i++;
                    }
                    else {
                        File.close();
                        break;
                    }
                    if (i > 1) {
                        Flag = true;
                        File.close();
                        break;
                    }
                }
                if (Flag) {
                    try {
                        filesystem::copy(FirstPath + "\\" + FileName, TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 1 типа" + "\\" + FileName, filesystem::copy_options::overwrite_existing);
                    }
                    catch (filesystem::filesystem_error& e) {
                        std::cerr << "Ошибка: " << e.what() << std::endl;
                    }
                }
            }
        }
        if (_chdir((SecondPath).c_str()) == 0) {
            for (const auto& FilePath : std::filesystem::directory_iterator(SecondPath)) {
                string FileName = FilePath.path().filename().string();

                ifstream File(SecondPath + "\\" + FileName);
                string Temp;
                bool Flag = false;
                int i = 0;
                while (getline(File, Temp)) {
                    if (i == 0) {
                        if (Temp != "Марка ЭВМ              Количество терминалов      Количество внешних запоминающих устройств") {
                            break;
                        }
                    }
                    if (!Temp.empty()) {
                        i++;
                    }
                    else {
                        File.close();
                        break;
                    }
                    if (i > 1) {
                        Flag = true;
                        File.close();
                        break;
                    }
                }
                if (Flag) {
                    try {
                        filesystem::copy(SecondPath + "\\" + FileName, TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 2 типа" + "\\" + FileName, filesystem::copy_options::overwrite_existing);
                    }
                    catch (filesystem::filesystem_error& e) {
                        std::cerr << "Ошибка: " << e.what() << std::endl;
                    }
                }
            }
        }
    }
    else {
        if (!Start) {
            Start = true;
            system("cls");
            cout << "Не найдена папка первой программы" << endl;
            cout << "Для возврата в главное меню нажмите любую клавишу..." << endl;
            _getch();
        }
        else {
            system("cls");
            cout << "Не найдена папка первой программы" << endl;
            cout << "Для перехода в главное меню нажмите любую клавишу..." << endl;
            _getch();
        }
    }
    if (!Start) {
        system("cls");
        cout << "Файлы успешно обновленны" << endl;
        cout << "Нажмите любую клавишу для возврата в главное меню...";
        _getch();
    }
}

void DrawAddFileMenu(int selectedItem) { // Функция отрисовки МЕНЮ ДОБАВЛЕНИЯ ФАЙЛОВ
    vector<string> menuItems = { "1. Поиск в папке первой программы", "2. Выбрать файл" };
    system("cls");
    cout << "   ---- МЕНЮ ДОБАВЛЕНИЯ ФАЙЛОВ ----  " << endl << endl;
    cout << "Каким способом добавить файл?" << endl << endl;
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

bool AddFileMenu() { // Фунция обработки клавиш в меню добавления файлов
    int selected = 0;
    bool running = true;
    while (running) {
        DrawAddFileMenu(selected);
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
                if (selected == 0) {
                    CheckFileInFirstProgram(false);
                    return true;
                }
                else
                {
                    running = AddFiles();
                }
                break;
            }
        }
        // Обработка цифровых клавиш '1' - '2' 
        else if (key >= '1' && key <= '2') {
            if (key - '1' == 0) {
                CheckFileInFirstProgram(false);
                return true;
            }
            else {
                running = AddFiles();
            }
        }
        // Выход на ESC
        else if (key == ESC) {
            running = false;
            return true;
        }
        // Обработка клавиши Enter
        else if (key == ENTER) {
            if (selected == 0) {
                CheckFileInFirstProgram(false);
                return true;
            }
            else
            {
                running = AddFiles();
            }
        }
    }
    return true;
}

bool AddFiles() { // Функция добавления файлов
    string Path = ChooseFile(GetDesktopPath(), false);
    if (!Path.empty()) {
        if (Path.substr(Path.size() - 4) == ".txt") {
            ifstream File(Path);
            string Temp, FirstString;
            bool Flag = false;
            int i = 0;
            while (getline(File, Temp)) {
                if (i == 0) {
                    FirstString = Temp;
                }
                if (!Temp.empty()) {
                    i++;
                }
                else {
                    File.close();
                    break;
                }
                if (i > 1) {
                    Flag = true;
                    File.close();
                    break;
                }
            }
            if (Flag) {
                if (FirstString == "Марка ЭВМ              Номера кафедры         Заводской номер ЭВМ") {
                    string FileName = Path.substr(Path.find_last_of("/\\") + 1);
                    try {
                        filesystem::copy(Path, TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 1 типа" + "\\" + FileName, filesystem::copy_options::overwrite_existing);
                        system("cls");
                        cout << "Файл '" << FileName << "' 1 типа успешно добавлен" << endl;
                        cout << "Для выхода в меню добавление файлов нажмите любую клавишу..." << endl;
                        _getch();
                    }
                    catch (filesystem::filesystem_error& e) {
                        std::cerr << "Ошибка: " << e.what() << std::endl;
                    }
                    File.close();
                }
                else if (FirstString == "Марка ЭВМ              Количество терминалов      Количество внешних запоминающих устройств") {
                    string FileName = Path.substr(Path.find_last_of("/\\") + 1);
                    try {
                        filesystem::copy(Path, TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 2 типа" + "\\" + FileName, filesystem::copy_options::overwrite_existing);
                        system("cls");
                        cout << "Файл '" << FileName << "' 2 типа успешно добавлен" << endl;
                        cout << "Для выхода в меню добавление файлов нажмите любую клавишу..." << endl;
                        _getch();
                    }
                    catch (filesystem::filesystem_error& e) {
                        system("cls");
                        std::cerr << "Ошибка: " << e.what() << std::endl;
                        cout << "Для продолжения нажмите любую клавишу...";
                        _getch();
                    }
                    File.close();
                }
                else {
                    system("cls");
                    cout << "Выбранный файл не подходит для работы с данной программой" << endl;
                    cout << "Для возврата в меню добавления файлов нажмите любую клавишу..." << endl;
                    _getch();
                    File.close();
                }
            }
            else {
                system("cls");
                cout << "Файл пуст" << endl;
                cout << "Для возврата в меню добавления файлов нажмите любую клавишу..." << endl;
                _getch();
            }
            return true;
        }
    }
    else {
        return true;
    }
}

bool Start() { // Функция создания и проверки целостности коренных файлов
    bool Flag = true;
    if (_chdir((TakePathToExeFile() + "\\LabaIT 2").c_str()) != 0) /*Проверка на существования папки*/ {
        if (_mkdir((TakePathToExeFile() + "\\LabaIT 2").c_str()) == 0) {
        }
        else {
            return false;
        }
    }
    Flag = CreateFolder("Входные файлы");
    if (Flag == true) {
        Flag = CreateFolder("Входные файлы\\Файлы 1 типа");
        if (Flag == true) {
            Flag = CreateFolder("Входные файлы\\Файлы 2 типа");
            if (Flag == true) {
                Flag = CreateFolder("Выходные файлы");
            }
            else {}
        }
        else {}
    }
    else {}
    CheckFileInFirstProgram(true);
    return Flag;
}

void DrawExitMenu(int selectedItem) { // Функция отрисовки меню завершения работы программы
    vector<string> menuItems = { "1. Нет!", "2. Да!" };
    system("cls");
    cout << "Вы точно хотите завершить работу программы?" << endl;
    for (int i = 0; i < menuItems.size(); ++i) {
        if (i == selectedItem) {
            cout << "-> " << menuItems[i] << endl;
        }
        else {
            cout << "    " << menuItems[i] << endl;
        }
    }
}

bool CloseProgram() { // Обработка клавиш в меню завершения работы программы
    int selected = 0;
    bool running = true;
    while (running) {
        DrawExitMenu(selected);
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
        // Обработка клавиши Enter
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