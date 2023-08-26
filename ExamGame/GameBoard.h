#pragma once

#include "Win10.h"
#include "Cell.h"

// класс "»гровое поле"
class GameBoard {
private:
    int Row; int Col; // строки и столбцы
public:
    int NumOfBombs;   // общее кол-во бомб на поле
    Cell** Cells;     // двумерный массив указателей, представл€ет собой €чейки игрового пол€

    // конструктор
    GameBoard(int xRow, int yCol, int bomb) {
        this->Row = xRow;
        this->Col = yCol;
        this->NumOfBombs = bomb;

        // выделение пам€ти дл€ двумерного массива €чеек
        Cells = new Cell * [Row];
        for (int i = 0; i < Col; ++i) {
            Cells[i] = new Cell[Col];
        }

        // установка координат и кол-во бомб дл€ каждой €чейки
        for (int i = 0; i < Row; ++i) {
            for (int j = 0; j < Col; ++j) {
                Cells[i][j].Init(i, j);
                Cells[i][j].SetBombsAround(0);
            }
        }
    }

    // геттеры-сеттеры
    int GetRow() const { return Row; }
    int GetCol() const { return Col; }

    // метод дл€ г-ции случайных координат дл€ размещени€ бомб на игровом поле.
    void SetBombs(int firstX, int firstY) {
        // переменные firstX и firstY гарантируют, что первый выбор не €вл€етс€ бомбой;
        // г-ци€ случайных координат дл€ размещени€ бомб
        for (int i = 0; i < NumOfBombs; ++i) {
            int x = rand() % Row;
            int y = rand() % Col;

            // если координаты уже содержат бомбу
            if (Cells[x][y].isBomb) {
                // возващаетс€ к предыдущей итерации цикла и выбрать новые случайные координаты
                i--;
                continue;
            }
            // первый ход игрока не €вл€етс€ миной
            if (x == firstX && y == firstY) {
                i--;
                continue;
            }

            // размещение бомбы в €чейке
            Cells[x][y].isBomb = true;
        }
    }

    // метод провер€ет, что заданные координаты наход€тс€ в пределах игрового пол€.
    bool IsValid(int x, int y) {
        return x >= 0 && x < GetRow() && y >= 0 && y < GetCol();
    }

    // метод перебирает каждую €чейку на игровом поле и дл€ каждой из них подсчитывает количество бомб вокруг
    void CountBombsAround() {
        int count;

        int row = GetRow();
        int col = GetCol();

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {

                count = 0;

                // проверка на наличие бомб вокруг текущей €чейки поразным направлени€м;
                // если €чейка содержит бомбу в однойм из направлений, count инкрементируетс€
                if (IsValid(i + 1, j))
                    if (Cells[i + 1][j].isBomb)
                        count++;

                if (IsValid(i, j + 1))
                    if (Cells[i][j + 1].isBomb)
                        count++;

                if (IsValid(i - 1, j + 1))
                    if (Cells[i - 1][j + 1].isBomb)
                        count++;

                if (IsValid(i + 1, j + 1))
                    if (Cells[i + 1][j + 1].isBomb)
                        count++;

                if (IsValid(i - 1, j))
                    if (Cells[i - 1][j].isBomb)
                        count++;

                if (IsValid(i, j - 1))
                    if (Cells[i][j - 1].isBomb)
                        count++;

                if (IsValid(i - 1, j - 1))
                    if (Cells[i - 1][j - 1].isBomb)
                        count++;

                if (IsValid(i + 1, j - 1))
                    if (Cells[i + 1][j - 1].isBomb)
                        count++;

                // устанавливаетс€ кол-во бомб вокруг текущей €чейки
                Cells[i][j].SetBombsAround(count);
            }
        }
    }

    // метод€ дл€ иниц-ции игрового пол€
    void InitBoard(int firstX, int firstY) {
        SetBombs(firstX, firstY); // размещение мин на игровом поле
        CountBombsAround();       // посчитать кол-во бомб вокруг каждой €чейки
    }
};