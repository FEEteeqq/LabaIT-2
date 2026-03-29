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
    
    void CheckFileInFirstProgram() {

        if (_chdir((GetDesktopPath() + "\\Лабараторная по ИТ").c_str()) == 0) /*Проверка на существования папки*/ {
            std::string FirstPath = GetDesktopPath() + "\\Лабараторная по ИТ\\Файлы 1 типа"; // Путь к папке с файлами 1 типа
            std::string SecondPath = GetDesktopPath() + "\\Лабараторная по ИТ\\Файлы 2 типа"; // Путь к папке с файлами 2 типа
            if (_chdir(FirstPath.c_str()) == 0) {
                for (const auto& FilePath : std::filesystem::directory_iterator(FirstPath)) {
                    string FileName = FilePath.path().filename().string();
                    //bool Flag = true;
                    //cout << "1 Первый цикл отработал штатно" << endl;
                    try {
                        filesystem::copy(FirstPath + "\\" + FileName, TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 1 типа" + "\\" + FileName, filesystem::copy_options::overwrite_existing);
                    }
                    catch (filesystem::filesystem_error& e) {
                        std::cerr << "Ошибка: " << e.what() << std::endl;
                    }
                    /*for (const auto& TempFile : std::filesystem::directory_iterator(TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 1 типа")) {
                        string TempName = TempFile.path().filename().string();
                        if (TempName == FileName) {
                            Flag = false;
                            cout << "1 Второй цикл отработал штатно" << endl;
                            break;
                        }
                        cout << "1 Второй цикл отработал штатно" << endl;

                    }
                    if (Flag) {
                        filesystem::copy(FirstPath + "\\" + FileName + ".txt", TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 1 типа" + "\\" + FileName + ".txt", filesystem::copy_options::overwrite_existing);
                    }*/

                }
            }
            if (_chdir(SecondPath.c_str()) == 0) {
                for (const auto& FilePath : std::filesystem::directory_iterator(SecondPath)) {
                    string FileName = FilePath.path().filename().string();
                    //bool Flag = true;
                    //cout << "2 Первый цикл отработал штатно" << endl;

                    try {
                        filesystem::copy(SecondPath + "\\" + FileName, TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 2 типа" + "\\" + FileName, filesystem::copy_options::overwrite_existing);
                    }
                    catch (filesystem::filesystem_error& e) {
                        std::cerr << "Ошибка: " << e.what() << std::endl;
                    }


                    /*for (const auto& TempFile : std::filesystem::directory_iterator(TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 2 типа")) {
                        cout << "2 Второй цикл отработал штатно" << endl;
                        string TempName = TempFile.path().filename().string();
                        if (TempName == FileName) {
                            Flag = false;
                            break;
                        }
                    }
                    if (Flag) {
                        filesystem::copy(SecondPath, TakePathToExeFile() + "\\LabaIT 2\\Входные файлы\\Файлы 2 типа");
                    }*/
                }
            }
            cout << "Файлы успешно обнавленны" << endl;
            cout << "Нажмите любую клавишу для возврата в главное меню...";
            _getch();
        }
        else {
            cout << "Не найдена первая программа" << endl;
            _getch();
        }
    }

    void drawAddFileMenu(int selectedItem) {

        vector<string> menuItems = { "1. Поиск в папке первой программы", "2. Указать название папки с файлами" };

        system("cls");
        cout << "   --- Меню добавление файлов ---  " << endl;
        cout << "Каким способом добавить файл?" << endl;
        for (int i = 0; i < menuItems.size(); ++i) {
            if (i == selectedItem) {
                cout << "->" << menuItems[i] << endl;
            }
            else {
                cout << "    " << menuItems[i] << endl;
            }
        }
    }

    bool AddFileMenu() {

        int selected = 0;
        bool running = true;

        while (running) {
            drawAddFileMenu(selected);

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
                        CheckFileInFirstProgram();
                        return true;
                    }
                    else
                    {
                        return true;
                    }
                    break;
                }
            }
            // Обработка цифровых клавиш '1' - '2' 
            else if (key >= '1' && key <= '2') {
                if (key - '1' == 0) {
                    running = false;
                    CheckFileInFirstProgram();
                    return true;
                }
                else
                {
                    running = false;
                    return true;
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
                    CheckFileInFirstProgram();
                    return true;
                }
                else
                {
                    return true;
                }
            }
        }

    }

    //bool AddOrUpdateFiles() {




    //    return true;
    //}

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
                else { /*return Flag;*/ }
            }
            else { /*return Flag;*/ }

        }
        else { /*return Flag;*/ }
        cout << "Все корневые файлы были успешно созданы/проверенны" << endl;
        CheckFileInFirstProgram();

        return Flag;
    }



    void drawExitMenu(int selectedItem) {

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

    void createFile() {
        system("cls");
        cout << "Файл будет иметь расширение .txt" << endl;
        cout << "Имя файла не должно быть больше 40 символов" << endl;
        cout << "Для возврата в главное меню ничего не вводите и нажмите клавишу Enter" << endl;
        cout << "Введите имя файла: ";
        string NameFile;
        std::getline(std::cin, NameFile);

        //Проверка на пустую строку
        if (NameFile.empty()) {}

        else {
            //Проверка не состоит ли имя файла только из расширения
            if (NameFile == ".txt") {
                cout << "Ошибка! Файл должен содержать не только расширение, необходимо изменить имя файла" << endl;
                cout << "Для возврата в главное меню нажмите ESC, для повторного ввода нажмите любую другую клавишу" << endl;
                int Key;
                Key = _getch();
                if (Key == ESC) {}

                else {
                    createFile();
                }
            }
            else {

                //Проверка есть ли в названии файла расширение, если есть то удаляем его
                if (NameFile.size() > 3 && NameFile.substr(NameFile.size() - 4, 4) == ".txt") {
                    NameFile.erase(NameFile.size() - 4, 4);
                }

                //Проверка размера имени файла
                if (NameFile.size() > 40) {
                    cout << "Ошибка! Файл должен содержать не больше 40 символов, необходимо изменить имя файла" << endl;
                    cout << "Для возврата в главное меню нажмите ESC, для повторного ввода нажмите любую другую клавишу" << endl;
                    int Key;
                    Key = _getch();
                    if (Key == ESC) {}

                    else {
                        createFile();
                    }
                }
                else {

                    //Проверка на существование файла с таким именем
                    ifstream Test(TakePathToExeFile() + "\\" + NameFile + ".txt");
                    if (Test.is_open()) {

                        cout << "Ошибка! Файл с таким именем уже существует, необходимо изменить имя файла" << endl;
                        cout << "Для возврата в главное меню нажмите ESC, для повторного ввода нажмите любую другую клавишу" << endl;
                        int Key;
                        Key = _getch();
                        if (Key == ESC) {}

                        else {
                            createFile();
                        }
                    }

                    //Создание файла в котором будут объеденены записи из выбранных файлов
                    else {
                        ofstream File(TakePathToExeFile() + "\\LabaIT 2\\Выходные файлы\\" + NameFile + ".txt");
                        if (File.is_open()) {

                            cout << "Файл " << NameFile << " успешно создан" << endl;
                            cout << "Нажмите любую клавишу, чтобы вернуться в главное меню...";
                            File.close();
                            _getch();
                        }

                        else {
                            cout << "Ошибка при создании файла" << endl;
                            cout << "Нажмите любую клавишу, чтобы вернуться в главное меню...";
                            _getch();
                        }
                    }

                }
            }
        }
    }