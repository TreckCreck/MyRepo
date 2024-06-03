#ifndef TICKET_H
#define TICKET_H

#include <locale>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;
class ticket
{
private:
    int train;
    string station1;
    string station2;
    string dep_day;
    string dep_time;
    int coach;
    int seat;
    int price;
public:
    ticket() : train(0), station1(""), station2(""), dep_day(""), dep_time(""), coach(0), seat(0), price(0) {};
    ticket(int, string, string, string, string, int, int, int);
    void writeTicketToFile(ticket t);
    ticket readTicketFromFile(int i);
    int checkamount();
    void clearFile();
    void TicketAvailability(ticket* alltickets, int* emptyseats, int i);
    int AvaibleSeats(ticket* alltickets, int i, int seatsamount);
    int inputTickets(ticket* alltickets, int seatsamount, int* emptyseats, int num_tickets);
    void findMostExpensiveTicket(ticket* alltickets, int N);
    int countAvailableSeats(ticket* alltickets, int N, int coachNumber, int trainNumber, string depday);
    int deleteticket(int num_tickets, ticket* alltickets);
    bool operator ==(ticket another);
    friend ostream& operator<<(ostream& stream, const ticket& aticket);
    friend istream& operator>>(istream& stream, ticket& aticket);
    friend ofstream& operator<<(ofstream& stream, const ticket& aticket);
    friend ifstream& operator>>(ifstream& stream, ticket& aticket);
};
#endif