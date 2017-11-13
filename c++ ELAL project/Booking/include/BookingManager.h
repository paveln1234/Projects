#ifndef BOOKINGMANAGER_H
#define BOOKINGMANAGER_H
#include <map>
#include <string>
using namespace std;
class Ticket_t;
class BookingManager
{
    public:

        /** Default constructor */
        BookingManager();
        /** Default destructor */
        virtual ~BookingManager();
        bool AddTicket(const Ticket_t* _newTicket);
        bool RemoveTicket(const string& _ticketNumber);
        const Ticket_t* GetTicket(const string& _ticketNumber)const;
        bool UpdateTicket(const Ticket_t* _Ticket);


    private:
        BookingManager(const BookingManager& other);
        BookingManager& operator=(const BookingManager& other);

    private:
        map<string,Ticket_t*> m_tikets;
};

#endif // BOOKINGMANAGER_H
