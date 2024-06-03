#include <iostream>
#include  "TicketClass.h"

ticket::ticket(int tr, string st1, string st2, string dd, string dt, int ch, int st, int pc)
{
    train = tr;
    station1 = st1;
    station2 = st2;
    dep_day = dd;
    dep_time = dt;
    coach = ch;
    seat = st;
    price = pc;
}

void ticket::writeTicketToFile(ticket t)
{
    ofstream file("tickets.txt", ios::app);
    if (file.is_open())
    {
        file << t;          // ��������� ofstream& operator<<
        file.close();
    }
    else
    {
        cout << "������ �������� �����" << endl;
    }
}

ticket ticket::readTicketFromFile(int i)
{
    ifstream readfile("tickets.txt");
    ticket t;
    string empty;
    if (readfile.is_open())
    {
        for (int count = 0; count < i * 8; ++count)
        {
            getline(readfile, empty);
        }
        readfile >> t;      // ��������� ifstream& operator>>
        readfile.close();
    }
    else
    {
        cout << "������ �������� �����" << endl;
    }
    return t;
}
int ticket::checkamount()
{
    ifstream readfile("tickets.txt");
    int N = 0;
    ticket t;
    string line;
    string empty;
    if (readfile.is_open())
    {
        while (true)
        {
            if (readfile >> t.train >> ws && getline(readfile, t.station1) &&
                getline(readfile, t.station2) && getline(readfile, t.dep_day) &&
                getline(readfile, t.dep_time) && readfile >> t.coach >> t.seat >> t.price)
            {
                N++;
            }
            else
            {
                break;
            }
        }
        readfile.close();
    }
    else {
        cout << "������ �������� �����" << endl;
    }
    return N;
}


void ticket::clearFile() {
    ofstream del;
    del.open("tickets.txt", std::ofstream::out | std::ofstream::trunc);
    del.close();
}

void ticket::TicketAvailability(ticket* alltickets, int* emptyseats, int V)
{
    for (int h = 1; h <= V; h++)
    {
        for (int j = 0; j < h; j++)
        {
            if ((alltickets[h].train == alltickets[j].train) && (alltickets[h].dep_day == alltickets[j].dep_day) && (alltickets[h].coach == alltickets[j].coach))
            {
                if (alltickets[h].seat != alltickets[j].seat)
                {
                    emptyseats[h]--;
                }
            }
        }
    }
}
int ticket::AvaibleSeats(ticket* alltickets, int V, int seatsamount)
{
    for (int h = 0; h < V; h++)
    {
        if (alltickets[h] == alltickets[V]) // ��������� operator ==
        {
            cout << " ����� ��� ������ �� ������ #";
            cout << h << endl;
            h = V;
            return 1;
        }
    }
    return 0;
}
int ticket::inputTickets(ticket* alltickets, int seatsamount, int* emptyseats, int num_tickets)
{
    int V;
    V = num_tickets;
    int q = 0;
    int j = 0;
    for (; j < 1; )
    {
        emptyseats[V] = seatsamount;
        cout << "������� ������ ������ " << V << ":" << endl;
        cout << "������� ����� �����: ";
        cin >> alltickets[V].train;
        cin.clear();
        SetConsoleCP(1251);
        cout << "������� ������� �����������: " << endl;
        cin >> alltickets[V].station1;
        cin.clear();
        cout << "������� ������� ��������: " << endl;
        cin >> alltickets[V].station2;
        cin.clear();
        SetConsoleCP(866);
        cout << "������� ���� �����������: " << endl;
        cin >> alltickets[V].dep_day;
        cin.clear();
        cout << "������� ����� �����������: " << endl;
        cin >> alltickets[V].dep_time;
        cin.clear();
        cout << "������� ����� ������: " << endl;
        cin >> alltickets[V].coach;
        cin.clear();
        TicketAvailability(alltickets, emptyseats, V);
        cout << " emptyseats = ";
        cout << emptyseats[V] << endl;
        if (emptyseats[V] > 0)
        {
            emptyseats[V]--;
            q = 0;
        }
        else
        {
            q = 1;
        }
        if (q == 0)
        {
            cout << "������� ����� �����: " << endl;
            cin >> alltickets[V].seat;
            if (alltickets[V].seat <= 0)
            {
                j = 0;
                cout << " ����� �� ����� ���� ������������� ��� ������ 0 " << endl;
            }
            else
            {
                int v = AvaibleSeats(alltickets, V, seatsamount);
                cout << v << endl;
                if (alltickets[V].seat > seatsamount)
                {
                    cout << " ����� ����� ���� ���������� ���� � ������" << endl;
                    j = 0;
                }
                else
                    if (v == 1)
                    {
                        j = 0;
                    }
                    else
                    {
                        cout << "������� ��������� ������: ";
                        cin >> alltickets[V].price;
                        cin.clear();
                        cout << "����� ����� " << V << " ������" << endl;
                        writeTicketToFile(alltickets[V]);
                        num_tickets++;
                        j++;
                    }
            }
        }
        else
        {
            cout << "����� ����� " << V << " �� ������ ��-�� ������� � ����������� ����" << endl;
            j = 0;
        }
    }
    return num_tickets;
}
void ticket::findMostExpensiveTicket(ticket* alltickets, int N)
{
    int maxPrice = alltickets[0].price;
    int maxPriceIndex = 0;

    for (int i = 1; i < N; i++)
    {
        if (alltickets[i].price > maxPrice)
        {
            maxPrice = alltickets[i].price;
            maxPriceIndex = i;
        }
    }

    cout << "����� ������� �� ���� ��������� �������: " << endl;
    cout << "����� �����: " << alltickets[maxPriceIndex].train << endl;
    cout << "������� �����������: " << alltickets[maxPriceIndex].station1 << endl;
    cout << "������� ��������: " << alltickets[maxPriceIndex].station2 << endl;
    cout << "���� �����������: " << alltickets[maxPriceIndex].dep_day << endl;
    cout << "����� �����������: " << alltickets[maxPriceIndex].dep_time << endl;
    cout << "����� ������: " << alltickets[maxPriceIndex].coach << endl;
    cout << "����� �����: " << alltickets[maxPriceIndex].seat << endl;
    cout << "��������� ������: " << alltickets[maxPriceIndex].price << endl;
}

int ticket::countAvailableSeats(ticket* alltickets, int N, int coachNumber, int trainNumber, string depday)
{
    int unavailableSeats = 0;
    int unAvailableseats[5];
    string unAvailableseats2[5];
    for (int d = 0; d < 5; d++)
    {
        unAvailableseats[d] = d + 1;
    }

    for (int i = 0; i < N; i++)
    {
        if (alltickets[i].coach == coachNumber && alltickets[i].train == trainNumber && alltickets[i].dep_day == depday)
        {
            unavailableSeats++;
            for (int d = 0; d < 5; d++)
            {
                if (unAvailableseats[d] == alltickets[i].seat)
                {
                    unAvailableseats2[d] = "+";
                }
            }
        }
    }
    cout << " ������ ��������� ����: ";
    for (int d = 0; d < 5; d++)
    {

        if (unAvailableseats2[d] != "+")
        {
            cout << unAvailableseats[d];
            if (d != 4)
                cout << ", ";
        }
    }
    cout << endl;
    return unavailableSeats;
}

int ticket::deleteticket(int num_tickets, ticket* alltickets)
{
    int U = 0, V = num_tickets;
    ticket compare;
    do
    {
        do
        {
            U = 0;
            cout << " ������� ������ ������, ������ ������ �������\n ";
            cout << " ����� �����: ";
            cin >> compare.train;
            cout << "\n ���� �����������: ";
            cin >> compare.dep_day;
            cout << "\n ����� ������: ";
            cin >> compare.coach;
            cout << "\n ����� �����: ";
            cin >> compare.seat;
            for (int h = 0; h <= num_tickets; h++)
            {
                if (alltickets[h] == compare)   // ��������� operator ==
                {
                    cout << "\n ����� ������ " << endl;
                    U = 1;
                    V--;
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
        } while (U != 1);
        cout << " ���������� �������� ������� - 0, ��������� � ���� - 1" << endl;
        cin >> U;
    } while (U != 1);
    return V;
}
bool ticket::operator ==(ticket another)
{
    if (train != another.train) return false;
    if (dep_day != another.dep_day) return false;
    if (coach != another.coach) return false;
    if (seat != another.seat) return false;
    return true;
}
ostream& operator<<(ostream& stream, const ticket& t)
{
    stream << " ����� ������: " << t.train << endl;
    stream << " ������� �����������: " << t.station1 << endl;
    stream << " ������� ��������: " << t.station2 << endl;
    stream << " ���� �����������: " << t.dep_day << endl;
    stream << " ����� �����������: " << t.dep_time << endl;
    stream << " ����� ������: " << t.coach << endl;
    stream << " ����� �����: " << t.seat << endl;
    stream << " ����: " << t.price << endl;
    return stream;
}
istream& operator>>(istream& stream, ticket& t)
{
    stream >> t.train;
    stream.ignore();
    getline(stream, t.station1);
    getline(stream, t.station2);
    getline(stream, t.dep_day);
    getline(stream, t.dep_time);
    stream >> t.coach >> t.seat >> t.price;
    return stream;
}
ofstream& operator<<(ofstream& stream, const ticket& t)
{
    stream << t.train << endl;
    stream << t.station1 << endl;
    stream << t.station2 << endl;
    stream << t.dep_day << endl;
    stream << t.dep_time << endl;
    stream << t.coach << endl;
    stream << t.seat << endl;
    stream << t.price << endl;
    return stream;
}
ifstream& operator>>(ifstream& stream, ticket& t)
{
    stream >> t.train;
    stream.ignore();
    getline(stream, t.station1);
    getline(stream, t.station2);
    getline(stream, t.dep_day);
    getline(stream, t.dep_time);
    stream >> t.coach >> t.seat >> t.price;
    return stream;
}