#pragma once
#include "GameBoard.h"

// класс "Игра", который управляет игровым процессом
class Game {
private:
    GameBoard* MainBoard; // игровое поле
    char** VisibleBoard;  // видимое поле для отображения
    int NumOfFlags = 0;   // кол-во установленных фла
public:
    // конструктор
    Game(GameBoard* givenBoard) {
        MainBoard = givenBoard;
        int row = MainBoard->GetRow();
        int col = MainBoard->GetCol();
        VisibleBoard = new char* [row];
        for (int i = 0; i < row; ++i) {
            VisibleBoard[i] = new char[col];
        }
        // иниц-ция видимого игрового поля символами '*'
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                VisibleBoard[i][j] = '*';
            }
        }
    }

    int СursorX = 0; // текущая позиция курсора по оси X
    int СursorY = 0; // текущая позиция курсора по оси Y

    // метод для запуска игры
    void RunGame() {
        bool isGameContinues = true; // продолжает ли игрок игру
        bool IsFirstChoice = true;   // является ли текущий выбор первым
        int x = 0, y = 0;
        char userInput;

        while (isGameContinues) {
            system("cls");
            CursorHide(FALSE, 100);

            printBoard();
            cout << "\nBombs (@): " << MainBoard->NumOfBombs;
            cout << "\nFlags (!):" << MainBoard->NumOfBombs - NumOfFlags;
            cout << "\nArrow keys or WSAD - move, F - flag, R - reveal, ESC - return to the main menu.\n";

            // получение ввода игрока
            userInput = _getch();

            if (isGameContinues && userWon()) {
                // отображение сообщения о победе
                system("cls");
                SetColor(black, light_blue);
                cout << " __     ______  _    _  __          _______ _   _ _  " << endl;
                cout << " \\ \\   / / __ \\| |  | | \\ \\        / /_   _| \\ | | | " << endl;
                cout << "  \\ \\_/ / |  | | |  | |  \\ \\  /\\  / /  | | |  \\| | | " << endl;
                cout << "   \\   /| |  | | |  | |   \\ \\/  \\/ /   | | | . ` | | " << endl;
                cout << "    | | | |__| | |__| |    \\  /\\  /   _| |_| |\\  |_| " << endl;
                cout << "    |_|  \\____/ \\____/      \\/  \\/   |_____|_| \\_(_) " << endl;
                cout << endl;
                SetColor(black, white);
                system("pause");
                system("cls");
                return; // завершение раунда, вернуться в основное меню
            }

            switch (userInput) {
            case 'R':
            case 'r': {
                // раскрытие ячейки
                if (IsFirstChoice) {
                    MainBoard->InitBoard(x, y);
                    IsFirstChoice = false;
                    Reveal(x, y);
                }
                else if (MainBoard->Cells[x][y].isBomb) { // если выбрана бомба - конец игры
                    // вывод сообщения о поражении
                    system("cls");
                    VisibleBoard[x][y] = '@';
                    printBoard();
                    SetColor(black, light_red);
                    cout << "\n\n";
                    cout << " __     ______  _    _   _      ____   _____ ______ _  " << endl;
                    cout << " \\ \\   / / __ \\| |  | | | |    / __ \\ / ____|  ____| | " << endl;
                    cout << "  \\ \\_/ / |  | | |  | | | |   | |  | | (___ | |__  | | " << endl;
                    cout << "   \\   /| |  | | |  | | | |   | |  | |\\___ \\|  __| | | " << endl;
                    cout << "    | | | |__| | |__| | | |___| |__| |____) | |____|_| " << endl;
                    cout << "    |_|  \\____/ \\____/  |______\\____/|_____/|______(_) " << endl;
                    cout << endl;
                    SetColor(black, white);
                    system("pause");
                    system("cls");
                    return;
                }
                else {
                    // рекурсивно раскрываем ячейки и их соседей, так как выбранная ячейка без бомбы
                    Reveal(x, y);
                }
                break;
            }
            case 'F':
            case 'f': {
                // получение текущего состояния ячейки
                CellState cur = MainBoard->Cells[x][y].GetCellState();
                // если ячейка скрыта или помечена флагом
                if (cur == HIDDEN || cur == FLAG) {
                    if (VisibleBoard[x][y] != '!') {
                        VisibleBoard[x][y] = '!'; // установка симовла флага
                        MainBoard->Cells[x][y].SetCellState(FLAG); // установка состояния ячейки с флажком
                        NumOfFlags++; // увеличивае счётчика установленных флагов
                    }
                    else { // если символ на видимом поле уже является флагом - снимаем флаг
                        VisibleBoard[x][y] = '*'; // востановление символа
                        MainBoard->Cells[x][y].SetCellState(HIDDEN);
                        NumOfFlags--;
                    }
                }
                break;
            }
            case UP:
            case 'W':
            case 'w': {
                if (x > 0) {
                    x--;
                    СursorX = x;
                    СursorY = y;
                }
                break;
            }
            case DOWN:
            case 'S':
            case 's': {
                if (x < MainBoard->GetRow() - 1) {
                    x++;
                    СursorX = x;
                    СursorY = y;
                }
                break;
            }

            case LEFT:
            case 'A':
            case 'a': {
                if (y > 0) {
                    y--;
                    СursorX = x;
                    СursorY = y;
                }
                break;
            }

            case RIGHT:
            case 'D':
            case 'd': {
                if (y < MainBoard->GetCol() - 1) {
                    y++;
                    СursorX = x;
                    СursorY = y;
                }
                break;
            }
            case ESC: { return; }
            }
        }
    };

    // метод для опредления выигрша игрока
    bool userWon() {
        int row = MainBoard->GetRow();
        int col = MainBoard->GetCol();

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                // если есть хотя бы одна скрытая ячейка без бомбы - игра не выиграна
                if (VisibleBoard[i][j] == '*' && !MainBoard->Cells[i][j].isBomb) { return false; }
            }
        }
        return true;
    }

    // метод для отображения игрового поля
    void printBoard() {
        int row = MainBoard->GetRow();
        int col = MainBoard->GetCol();

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                // изменение цветов в зависимости от состояния и значения ячейки
                if (i == СursorX && j == СursorY) {
                    SetColor(white, yellow);
                }
                else if (VisibleBoard[i][j] == '!') {
                    SetColor(black, green);
                }
                else if (isdigit(VisibleBoard[i][j])) { // изменение цвета цифр
                    SetColor(black, light_purple);
                }
                /*else if (MainBoard->Cells[i][j].isBomb) {
                    SetColor(black, red);
                }*/
                else {
                    SetColor(black, white);
                }

                if (VisibleBoard[i][j] == '@') {
                    SetColor(white, red);
                }

                // вывод содержимого ячейки
                cout << VisibleBoard[i][j] << ' ';

                SetColor(black, white); // восстановление стандартных цветов после вывода символа
            }
            cout << '\n';
        }
    }

    // метод для рекурсивного раскрытия пустых ячеек и их соседей
    void Reveal(int x, int y) {
        // если ячейка уже видима - завершить выполнение
        if (MainBoard->Cells[x][y].GetCellState() == VISIBLE) { return; }

        // устанавление состояния ячейки как видимое и отображение кол-ва бомб вокруг
        MainBoard->Cells[x][y].SetCellState(VISIBLE);
        VisibleBoard[x][y] = MainBoard->Cells[x][y].GetBombsAround() + '0';

        // если вокруг данной ячейки нет бомб, продолжение "раскрытия" ячейки вокруг
        if (MainBoard->Cells[x][y].GetBombsAround() == 0) {
            if (MainBoard->IsValid(x + 1, y)) { Reveal(x + 1, y); }
            if (MainBoard->IsValid(x, y + 1)) { Reveal(x, y + 1); }
            if (MainBoard->IsValid(x - 1, y + 1)) { Reveal(x - 1, y + 1); }
            if (MainBoard->IsValid(x + 1, y + 1)) { Reveal(x + 1, y + 1); }
            if (MainBoard->IsValid(x - 1, y)) { Reveal(x - 1, y); }
            if (MainBoard->IsValid(x, y - 1)) { Reveal(x, y - 1); }
            if (MainBoard->IsValid(x - 1, y - 1)) { Reveal(x - 1, y - 1); }
            if (MainBoard->IsValid(x + 1, y - 1)) { Reveal(x + 1, y - 1); }
        }
    }
};