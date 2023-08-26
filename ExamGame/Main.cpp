#include "Menu.h"
using namespace std;
#define RAND(Min,Max)  (rand()%((Max)-(Min)+1)+(Min))
struct LC { LC() { system("chcp 1251 > nul"); srand(time(0)); }~LC() { cin.get(); cin.get(); } } _;

int main()
{
    // иниц-ция консольного окна
    SetConsoleSize(110, 50);
    Menu menu; // создание объекта
    menu.LoadStatistics(); // загрузка статистики
    menu.showMainMenu(); // вызывается метод для вывода меню
}