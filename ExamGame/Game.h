#pragma once
#include "GameBoard.h"

// ����� "����", ������� ��������� ������� ���������
class Game {
private:
    GameBoard* MainBoard; // ������� ����
    char** VisibleBoard;  // ������� ���� ��� �����������
    int NumOfFlags = 0;   // ���-�� ������������� ���
public:
    // �����������
    Game(GameBoard* givenBoard) {
        MainBoard = givenBoard;
        int row = MainBoard->GetRow();
        int col = MainBoard->GetCol();
        VisibleBoard = new char* [row];
        for (int i = 0; i < row; ++i) {
            VisibleBoard[i] = new char[col];
        }
        // ����-��� �������� �������� ���� ��������� '*'
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                VisibleBoard[i][j] = '*';
            }
        }
    }

    int �ursorX = 0; // ������� ������� ������� �� ��� X
    int �ursorY = 0; // ������� ������� ������� �� ��� Y

    // ����� ��� ������� ����
    void RunGame() {
        bool isGameContinues = true; // ���������� �� ����� ����
        bool IsFirstChoice = true;   // �������� �� ������� ����� ������
        int x = 0, y = 0;
        char userInput;

        while (isGameContinues) {
            system("cls");
            CursorHide(FALSE, 100);

            printBoard();
            cout << "\nBombs (@): " << MainBoard->NumOfBombs;
            cout << "\nFlags (!):" << MainBoard->NumOfBombs - NumOfFlags;
            cout << "\nArrow keys or WSAD - move, F - flag, R - reveal, ESC - return to the main menu.\n";

            // ��������� ����� ������
            userInput = _getch();

            if (isGameContinues && userWon()) {
                // ����������� ��������� � ������
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
                return; // ���������� ������, ��������� � �������� ����
            }

            switch (userInput) {
            case 'R':
            case 'r': {
                // ��������� ������
                if (IsFirstChoice) {
                    MainBoard->InitBoard(x, y);
                    IsFirstChoice = false;
                    Reveal(x, y);
                }
                else if (MainBoard->Cells[x][y].isBomb) { // ���� ������� ����� - ����� ����
                    // ����� ��������� � ���������
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
                    // ���������� ���������� ������ � �� �������, ��� ��� ��������� ������ ��� �����
                    Reveal(x, y);
                }
                break;
            }
            case 'F':
            case 'f': {
                // ��������� �������� ��������� ������
                CellState cur = MainBoard->Cells[x][y].GetCellState();
                // ���� ������ ������ ��� �������� ������
                if (cur == HIDDEN || cur == FLAG) {
                    if (VisibleBoard[x][y] != '!') {
                        VisibleBoard[x][y] = '!'; // ��������� ������� �����
                        MainBoard->Cells[x][y].SetCellState(FLAG); // ��������� ��������� ������ � �������
                        NumOfFlags++; // ���������� �������� ������������� ������
                    }
                    else { // ���� ������ �� ������� ���� ��� �������� ������ - ������� ����
                        VisibleBoard[x][y] = '*'; // ������������� �������
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
                    �ursorX = x;
                    �ursorY = y;
                }
                break;
            }
            case DOWN:
            case 'S':
            case 's': {
                if (x < MainBoard->GetRow() - 1) {
                    x++;
                    �ursorX = x;
                    �ursorY = y;
                }
                break;
            }

            case LEFT:
            case 'A':
            case 'a': {
                if (y > 0) {
                    y--;
                    �ursorX = x;
                    �ursorY = y;
                }
                break;
            }

            case RIGHT:
            case 'D':
            case 'd': {
                if (y < MainBoard->GetCol() - 1) {
                    y++;
                    �ursorX = x;
                    �ursorY = y;
                }
                break;
            }
            case ESC: { return; }
            }
        }
    };

    // ����� ��� ���������� ������� ������
    bool userWon() {
        int row = MainBoard->GetRow();
        int col = MainBoard->GetCol();

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                // ���� ���� ���� �� ���� ������� ������ ��� ����� - ���� �� ��������
                if (VisibleBoard[i][j] == '*' && !MainBoard->Cells[i][j].isBomb) { return false; }
            }
        }
        return true;
    }

    // ����� ��� ����������� �������� ����
    void printBoard() {
        int row = MainBoard->GetRow();
        int col = MainBoard->GetCol();

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                // ��������� ������ � ����������� �� ��������� � �������� ������
                if (i == �ursorX && j == �ursorY) {
                    SetColor(white, yellow);
                }
                else if (VisibleBoard[i][j] == '!') {
                    SetColor(black, green);
                }
                else if (isdigit(VisibleBoard[i][j])) { // ��������� ����� ����
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

                // ����� ����������� ������
                cout << VisibleBoard[i][j] << ' ';

                SetColor(black, white); // �������������� ����������� ������ ����� ������ �������
            }
            cout << '\n';
        }
    }

    // ����� ��� ������������ ��������� ������ ����� � �� �������
    void Reveal(int x, int y) {
        // ���� ������ ��� ������ - ��������� ����������
        if (MainBoard->Cells[x][y].GetCellState() == VISIBLE) { return; }

        // ������������ ��������� ������ ��� ������� � ����������� ���-�� ���� ������
        MainBoard->Cells[x][y].SetCellState(VISIBLE);
        VisibleBoard[x][y] = MainBoard->Cells[x][y].GetBombsAround() + '0';

        // ���� ������ ������ ������ ��� ����, ����������� "���������" ������ ������
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