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
    
    void CheckFileInFirstProgram(bool Start) {

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

    void DrawAddFileMenu(int selectedItem) {

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

    bool AddFileMenu() {

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
                else
                {
                    running = AddFiles();
                }
            }

            // Выход на ESC
            else if (key == ESC) {
                running = false;
                return true;
            }

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

    bool AddFiles() {

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

            /*else if (Path.substr(Path.size() - 13, 12) == "Файлы 1 типа") {
                int i = 0;
                if (_chdir((Path).c_str()) == 0) {
                    for (const auto& FilePath : std::filesystem::directory_iterator(Path)) {
                        string FileName = FilePath.path().filename().string();
                        try {
                            filesystem::copy(Path + "\\" + FileName, TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 1 типа" + "\\" + FileName, filesystem::copy_options::overwrite_existing);
                        }
                        catch (filesystem::filesystem_error& e) {
                            std::cerr << "Ошибка: " << e.what() << std::endl;
                        }
                    }
                }
                cout << "Успешно дабавленно " << i << "файлов" << endl;
                cout << "Для выхода в меню добавление файлов нажмите любую клавишу..." << endl;
                _getch();
                return true;
            }
            else if (Path.substr(Path.size() - 13, 12) == "Файлы 2 типа") {
                int i = 0;
                if (_chdir((Path).c_str()) == 0) {
                    for (const auto& FilePath : std::filesystem::directory_iterator(Path)) {
                        string FileName = FilePath.path().filename().string();
                        try {
                            filesystem::copy(Path + "\\" + FileName, TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 2 типа" + "\\" + FileName, filesystem::copy_options::overwrite_existing);
                            i++;
                        }
                        catch (filesystem::filesystem_error& e) {
                            std::cerr << "Ошибка: " << e.what() << std::endl;
                        }
                    }
                }
                cout << "Успешно дабавленно " << i << "файлов" << endl;
                cout << "Для выхода в меню добавление файлов нажмите любую клавишу..." << endl;
                _getch();
                return true;
            }
            else {

            }*/

        }       
        else {
            return true;
        }
    }

    bool Start() {
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



    void drawExitMenu(int selectedItem) {

        vector<string> menuItems = {"1. Нет!", "2.Да!"};

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

    bool CloseProgram() {

        int selected = 0;
        bool running = true;

        while (running) {
            drawExitMenu(selected);

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