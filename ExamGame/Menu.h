#pragma once

#include <iostream>
#include <string>
#include "Game.h"

// перечисление дл€ уровней сложности
enum Difficulty {
    BEGINNER = 1,
    INTERMEDIATE,
    ADVANCED
};

//  ласс "ћеню"
class Menu {
private:
    int currentOption;
    int wins;
    int losses;
    int totalGames;

public:
    // конструктор по умолчанию
    Menu() : currentOption(1), wins(0), losses(0), totalGames(0) {}

    // метод д€л вывода заголовка игры
    void printGameTitle() {
        SetColor(black, white);
        cout << "====================================================================================" << endl;
        cout << "  __  __ _____ _   _ ______  _______          ________ ______ _____  ______ _____   " << endl;
        cout << " |  \\/  |_   _| \\ | |  ____|/ ____\\ \\        / /  ____|  ____|  __ \\|  ____|  __ \\  " << endl;
        cout << " | \\  / | | | |  \\| | |__  | (___  \\ \\  /\\  / /| |__  | |__  | |__) | |__  | |__) | " << endl;
        cout << " | |\\/| | | | | . ` |  __|  \\___ \\  \\ \\/  \\/ / |  __| |  __| |  ___/|  __| |  _  /  " << endl;
        cout << " | |  | |_| |_| |\\  | |____ ____) |  \\  /\\  /  | |____| |____| |    | |____| | \\ \\  " << endl;
        cout << " |_|  |_|_____|_| \\_|______|_____/    \\/  \\/   |______|______|_|    |______|_|  \\_\\ " << endl;
        cout << "====================================================================================" << endl;
    }

    // метод дл€ вывода опций меню
    void printMenuOptions() {
        for (int i = 1; i <= 4; ++i) {
            if (i == currentOption) {
                SetColor(white, yellow);
            }
            else {
                SetColor(black, white);
            }

            switch (i) {
            case 1: cout << "1. Play" << endl; break;
            case 2: cout << "2. Statistics" << endl; break;
            case 3: cout << "3. About Game" << endl; break;
            case 4: cout << "4. Exit" << endl; break;
            }

            SetColor(black, white);
        }
    }

    // обработка нажати€ клавиши
    void handleKeyPress(int key) {
        switch (key) {
        case UP: case 'W': case 'w':
            if (currentOption > 1) {
                --currentOption;
            }
            break;
        case DOWN: case 'S': case 's':
            if (currentOption < 4) {
                ++currentOption;
            }
            break;
        }
    }

    // обработка выбора опции меню
    void handleOptionSelection() {
        switch (currentOption) {
        case 1:
            ShowGameMenu();
            break;
        case 2:
            ShowStatisticsMenu();
            break;
        case 3:
            ShowAboutGame();
            break;
        case 4:
            exit(0); // выход из программы
        }
    }

    void showMainMenu() {
        while (true) {
            system("cls");
            printGameTitle();
            printMenuOptions();

            int key = _getch();
            handleKeyPress(key);

            if (key == ENTER) {
                handleOptionSelection();
            }
        }
    }

    // метод дл€ отображени€ главного меню
    void ShowGameMenu() {
        int choice = 1;  // начальное значение выбора
        char userInput;
        do {
            system("cls");
            printGameTitle();
            // установить цвет дл€ выбранной опции
            for (int i = 1; i <= 3; ++i) {
                if (i == choice) {
                    SetColor(white, yellow);
                    cout << i << ". ";
                }
                else {
                    SetColor(black, white);
                    cout << i << ". ";
                }

                switch (i) {
                case 1:
                    cout << "Beginner - 9x9 (10 mines/81 squares)\n";
                    break;
                case 2:
                    cout << "Intermediate - 16x16 (40 mines/256 squares)\n";
                    break;
                case 3:
                    cout << "Expert - 24x24 (99 mines/576 squares)\n";
                    break;
                }
            }

            // восстановление стандартный цвет
            SetColor(black, white);

            // получение пользовательский ввод
            userInput = _getch();

            // ќбработка клавиш WSAD и стрелок вверх/вниз
            switch (userInput) {
            case 'w':
            case 'W':
            case UP:
                if (choice > 1) {
                    choice--;
                }
                break;
            case 's':
            case 'S':
            case DOWN:
                if (choice < 3) {
                    choice++;
                }
                break;
            case ENTER:
                // обработка выбора уровн€
                int xRow, yCol, numOfBombs;
                switch (choice) {
                case 1: {
                    xRow = yCol = 9;
                    numOfBombs = 10;
                    break;
                }
                case 2: {
                    xRow = yCol = 16;
                    numOfBombs = 40;
                    break;
                }
                case 3: {
                    xRow = yCol = 24;
                    numOfBombs = 99;
                    break;
                }
                }

                // иниц-ци€ игры с выбранным уровнем
                GameBoard mainBoard(xRow, yCol, numOfBombs);
                Game game(&mainBoard); // запуск игры
                game.RunGame();

                // обновление статистики в зависимости от результата игры
                if (game.userWon()) { wins++; }
                else { losses++; }
                totalGames++;
                break;
            }
        } while (userInput != ENTER);

    }

    // метод дл€ сохранени€ статистики в файл
    void SaveStatistics()
    {
        ofstream fout("Statistics.txt");
        if (fout.is_open()) {
            fout << wins << '\n';
            fout << losses << '\n';
            fout << totalGames << '\n';
            fout.close();
        }
    }

    // метод дл€ загрузки статистики из файла
    void LoadStatistics() {
        ifstream fin("Statistics.txt");
        if (fin.is_open()) {
            fin >> wins >> losses >> totalGames;
            fin.close();
        }   
    }

    // метод показа статистики
    void ShowStatisticsMenu() {
        system("cls");
        cout << "\tYOUR RECORDS:" << endl;
        cout << "Total Games Played: " << totalGames << endl;
        cout << "Wins:\t" << wins << endl;
        cout << "Losses:\t" << losses << endl;
        SaveStatistics();
        system("pause");
        system("cls");
    }

    // метод об игре
    void ShowAboutGame() {
        system("cls");

        cout << "\tDESCRIPTION:"
            << "\nMinesweeper is a single-player puzzle game. The player is presented with a game board of squares (cell),"
            << "\nsome of which contain hidden mines.The goal is to clear the board without detonating any mines,"
            << "\nusing clues about the number of neighboring mines in each square.It's a game of logic and strategy,"
            << "\nand can be quite challenging!" << endl << endl;
        cout << "\tGAMEPLAY:"
            << "\n(1)\tUse the arrow keys or WSAD keys to move on the gameboard;"
            << "\n(2)\tUse the R key to open a cell;"
            << "\n(3)\tUse the F key to mark the mine." << endl << endl;
        system("pause"); system("cls");
        return;
    }
};