#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <Windows.h>
#include "Cashier.h"
using namespace std;



int main()
{
    setlocale(LC_ALL, "rus");
    int N = 0, U = 1, i = 0, Z = 0;
    int L = 25, d = 0;
    Cashier spisok(L);
    spisok.readfromfile();
    do
    {
        do
        {
            cout << " Прекратить ввод - 0, ввести билет - 1, удалить билеты - 2 " << endl;
            cin >> U;
            if (U == 1)
            {
                spisok.addTicket();
            }
            else if (U == 2)
            {
                    spisok.deleteticket();
            }
        } while (U != 0);
        cout << "Вывести все билеты - 1, вывести задание - 2" << endl;
        cin >> U;
        switch (U)
        {
        case 1:
            cout << spisok;         // Использую ostream& operator<<
            break;
        case 2:
            spisok.task();
            break;
        default:
            break;
        }

        cout << " Закончить выполнение программы - 2" << endl;
        cin >> U;
    } while (U != 2);
    return 0;
}