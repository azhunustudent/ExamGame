#pragma once

#include <iostream>
#include "Win10.h"
using namespace std;

// ���������� ��������� ������ (�������; �������; �������� ������),
// ��� ����� ������������ ���������� ������ �� ������� ����.
enum CellState {
    HIDDEN,  // �������
    VISIBLE, // �������
    FLAG     // � �������
};

// ����� "������ �������� ����"
class Cell {
private:
    int* X; int* Y;   // ��������� �� ���������� X � Y; ����� �������������� ��� �������� ���������
    int* BombsAround; // ���-�� ���� ������ ������
    CellState* CStat; // ���������/������ ������
public:
    bool isBomb = false;    // ��������� �������� �� ������ ������

    // ������������ � �����������
    Cell() { // ����������� �� ���������
        BombsAround = new int;
        *BombsAround = 0; // ����-��� � 0
        CStat = new CellState(HIDDEN); // ����-��� ��������� HIDDEN, �� ���� �������
    }
    Cell(int x, int y, CellState status) { // ����������� � �����������
        // �������� ������������ ������ ��� x, y, status, 
        // � �������� �������� � ���������� ������� ������
        this->X = new int(x);
        this->Y = new int(y);
        this->CStat = new CellState(status);
    }
    ~Cell() { // ���������� ��� ������������ ������
        delete (this->X);
        delete (this->Y);
        delete (this->CStat);
        delete (BombsAround);
    }

    // �������-�������
    int GetX() const { return *X; }
    int GetY() const { return *Y; }
    void SetX(int val) { *this->X = val; }
    void SetY(int val) { *this->Y = val; }

    //  ������� ����� ������ ��� ������ ������
    void Init(int valX, int valY) {
        this->X = new int(valX);
        this->Y = new int(valY);
    }
    // �������� ������������ ������, �� ������� ��� ��������� x � y
    void SetXY(int valX, int valY) {
        *X = valX;
        *Y = valY;
    }

    // ����������/���������/��������� ���-�� ���������� ����
    void IncBombsAround() { ++(*BombsAround); }
    int GetBombsAround()   const { return *BombsAround; }
    void SetBombsAround(int val) { *BombsAround = val; }

    // ��������� ������� ��� ����������� ������
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

    // ������-������ ��� ��������� ������
    CellState GetCellState()   const { return *CStat; }
    void SetCellState(CellState val) { *Cell::CStat = val; }
};