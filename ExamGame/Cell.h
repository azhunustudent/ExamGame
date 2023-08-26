#pragma once

#include <iostream>
#include "Win10.h"
using namespace std;

// определ€ет состо€ни€ €чейки (скрыта€; видима€; помечена флагом),
// как будет отображатьс€ содержимое €чейки на игровом поле.
enum CellState {
    HIDDEN,  // скрыта€
    VISIBLE, // видима€
    FLAG     // с флажком
};

// класс "ячейка игрового пол€"
class Cell {
private:
    int* X; int* Y;   // указатели на координаты X и Y; будет использоватьс€ дл€ хранени€ координат
    int* BombsAround; // кол-во бомб вокруг €чейки
    CellState* CStat; // состо€ние/статус €чейки
public:
    bool isBomb = false;    // указывает €вл€етс€ ли €чейка бомбой

    // конструкторы и деструкторы
    Cell() { // конструктор по умолчанию
        BombsAround = new int;
        *BombsAround = 0; // иниц-тс€ с 0
        CStat = new CellState(HIDDEN); // иниц-тс€ значением HIDDEN, то есть скрыта€
    }
    Cell(int x, int y, CellState status) { // конструктор с параметрами
        // выдел€ет динамическую пам€ть дл€ x, y, status, 
        // и копирует значени€ в выделенные области пам€ти
        this->X = new int(x);
        this->Y = new int(y);
        this->CStat = new CellState(status);
    }
    ~Cell() { // деструктор дл€ освобождени€ пам€ти
        delete (this->X);
        delete (this->Y);
        delete (this->CStat);
        delete (BombsAround);
    }

    // геттеры-сеттеры
    int GetX() const { return *X; }
    int GetY() const { return *Y; }
    void SetX(int val) { *this->X = val; }
    void SetY(int val) { *this->Y = val; }

    //  создает новую пам€ть при каждом вызове
    void Init(int valX, int valY) {
        this->X = new int(valX);
        this->Y = new int(valY);
    }
    // измен€ет существующую пам€ть, на которую уже указывают x и y
    void SetXY(int valX, int valY) {
        *X = valX;
        *Y = valY;
    }

    // увеличение/получение/установка кол-во окружающих бомб
    void IncBombsAround() { ++(*BombsAround); }
    int GetBombsAround()   const { return *BombsAround; }
    void SetBombsAround(int val) { *BombsAround = val; }

    // получение символа дл€ отображени€ €чейки
    char getAsChar() {
        int bombs = GetBombsAround();
        switch (*(this->CStat)) {
        case HIDDEN:
            return '*';
        case VISIBLE:
            if (bombs == 0)
                return '.';
        case FLAG:
            return '!';
        }
    }

    // геттер-сеттер дл€ состо€ни€ €чейки
    CellState GetCellState()   const { return *CStat; }
    void SetCellState(CellState val) { *Cell::CStat = val; }
};