#ifndef CASHIER_H
#define CASHIER_H

#include "TicketClass.h"

class Cashier
{
private:
    int max_tickets;
    ticket* alltickets;
    int num_tickets;
    int* emptyseats;
    int seatsamount;

public:
    Cashier(unsigned int max_t);
    ~Cashier();
    void addTicket();

    void readfromfile();
    void task();
    void deleteticket();
    void operator+=(const ticket& alltickets);
    void operator-=(const ticket& alltickets);
    friend ostream& operator<<(ostream& stream, const Cashier& acashier); // глобальная
};
#endif