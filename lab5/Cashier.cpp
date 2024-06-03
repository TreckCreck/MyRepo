#include "Cashier.h"

Cashier::Cashier(unsigned int max_t)
{
    seatsamount = 5;
    max_tickets = max_t;
    alltickets = new ticket[max_tickets];
    emptyseats = new int[max_tickets];
    num_tickets = alltickets[0].checkamount();
    cout << "\n ������ ����������� ������ Cashier:";
    cout << "\n �������� �������� - " << max_tickets;
    cout << "\n ��������� ������� -" << num_tickets;
    cout << endl;
}
Cashier::~Cashier()
{
    cout << "\n������ ���������� ������ Cashier:";
    delete[] emptyseats;
    delete[] alltickets;
    max_tickets = 0;
    num_tickets = 0;
    cout << " ���������� ������ �����������" << endl;
}
void Cashier::addTicket()
{
    ticket d;
    if (num_tickets < max_tickets)
    {
        num_tickets = d.inputTickets(alltickets, seatsamount, emptyseats, num_tickets);
    }
    else
    {
        cout << "��������� ������ ���������� �������" << endl;
    }
}

void Cashier::readfromfile()
{
    cout << " �������� ������ �� �����" << endl;
    for (int i = 0; i < num_tickets; i++)
        alltickets[i] = alltickets[i].readTicketFromFile(i);
}

void Cashier::task()
{
    ticket d;
    cout << "=================================================================================" << endl;
    cout << " ������� ";
    cout << num_tickets;
    cout << " ������� " << endl;
    cout << "=================================================================================" << endl;
    d.findMostExpensiveTicket(alltickets, num_tickets);
    cout << "=================================================================================" << endl;
    int coachNumber;
    int trainNumber;
    cout << "������� ����� �����, ����� ������ ���������� ��������� ����: ";
    cin >> trainNumber;
    cout << " ������� ���� �����: ";
    string depday;
    cin >> depday;
    cout << "������� ����� ������, ����� ������ ���������� ��������� ����: ";
    cin >> coachNumber;
    int availableSeats = d.countAvailableSeats(alltickets, num_tickets, coachNumber, trainNumber, depday);
    if ((seatsamount - availableSeats) < 0)
        availableSeats = seatsamount;
    cout << "���������� ��������� ���� � ��������� ������: " << seatsamount - availableSeats << endl;
}

void Cashier::deleteticket()
{
    ticket d;
    int A = num_tickets;
    num_tickets = d.deleteticket(num_tickets, alltickets);
    if (A != num_tickets)
    {
        d.clearFile();
        for (int i = 0; i < num_tickets; i++)
        {
            d.writeTicketToFile(alltickets[i]);
        }
    }
}

void Cashier::operator+=(const ticket& t)
{
    if (num_tickets < max_tickets)
    {
        alltickets[num_tickets] = t;
        num_tickets++;
    }
    else
    {
        cout << "��������� ������ ���������� �������" << endl;
    }
}

void Cashier::operator-=(const ticket& t)
{
    int U = 0;
    for (int h = 0; h <= num_tickets; h++)
    {
        if (alltickets[h] == t)
        {
            cout << "\n ����� ������ " << endl;
            U = 1;
        }
        else
            if (U != 1 && h == num_tickets)
            {
                cout << " ����� ������ �������" << endl;
                U = 0;
            }
        if (U == 1)
            alltickets[h] = alltickets[h + 1];
    }
    num_tickets--;
}

ostream& operator<<(ostream& stream, const Cashier& spisok)
{
    stream << " \n ��� ������:\n";
    for (int i = 0; i < spisok.num_tickets; i++)
    {
        stream << " ================= ����� # " << i + 1 << " =================\n";
        stream << spisok.alltickets[i] << endl;
    }
    return stream;
}
