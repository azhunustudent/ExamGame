#pragma once

#include "Win10.h"
#include "Cell.h"

// ����� "������� ����"
class GameBoard {
private:
    int Row; int Col; // ������ � �������
public:
    int NumOfBombs;   // ����� ���-�� ���� �� ����
    Cell** Cells;     // ��������� ������ ����������, ������������ ����� ������ �������� ����

    // �����������
    GameBoard(int xRow, int yCol, int bomb) {
        this->Row = xRow;
        this->Col = yCol;
        this->NumOfBombs = bomb;

        // ��������� ������ ��� ���������� ������� �����
        Cells = new Cell * [Row];
        for (int i = 0; i < Col; ++i) {
            Cells[i] = new Cell[Col];
        }

        // ��������� ��������� � ���-�� ���� ��� ������ ������
        for (int i = 0; i < Row; ++i) {
            for (int j = 0; j < Col; ++j) {
                Cells[i][j].Init(i, j);
                Cells[i][j].SetBombsAround(0);
            }
        }
    }

    // �������-�������
    int GetRow() const { return Row; }
    int GetCol() const { return Col; }

    // ����� ��� �-��� ��������� ��������� ��� ���������� ���� �� ������� ����.
    void SetBombs(int firstX, int firstY) {
        // ���������� firstX � firstY �����������, ��� ������ ����� �� �������� ������;
        // �-��� ��������� ��������� ��� ���������� ����
        for (int i = 0; i < NumOfBombs; ++i) {
            int x = rand() % Row;
            int y = rand() % Col;

            // ���� ���������� ��� �������� �����
            if (Cells[x][y].isBomb) {
                // ����������� � ���������� �������� ����� � ������� ����� ��������� ����������
                i--;
                continue;
            }
            // ������ ��� ������ �� �������� �����
            if (x == firstX && y == firstY) {
                i--;
                continue;
            }

            // ���������� ����� � ������
            Cells[x][y].isBomb = true;
        }
    }

    // ����� ���������, ��� �������� ���������� ��������� � �������� �������� ����.
    bool IsValid(int x, int y) {
        return x >= 0 && x < GetRow() && y >= 0 && y < GetCol();
    }

    // ����� ���������� ������ ������ �� ������� ���� � ��� ������ �� ��� ������������ ���������� ���� ������
    void CountBombsAround() {
        int count;

        int row = GetRow();
        int col = GetCol();

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {

                count = 0;

                // �������� �� ������� ���� ������ ������� ������ �������� ������������;
                // ���� ������ �������� ����� � ������ �� �����������, count ����������������
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

                // ��������������� ���-�� ���� ������ ������� ������
                Cells[i][j].SetBombsAround(count);
            }
        }
    }

    // ������ ��� ����-��� �������� ����
    void InitBoard(int firstX, int firstY) {
        SetBombs(firstX, firstY); // ���������� ��� �� ������� ����
        CountBombsAround();       // ��������� ���-�� ���� ������ ������ ������
    }
};