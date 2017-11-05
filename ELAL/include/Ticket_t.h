#ifndef TICKET_T_H
#define TICKET_T_H
#include <string>

using namespace std;
class Ticket_t
{
    public:
        /** Default constructor */
        Ticket_t();
        /** Default destructor */
        virtual ~Ticket_t();
        virtual void SetPassengerId(size_t _passengerId){m_passengerId = _passengerId;}
        virtual size_t GetPassengerId()const {return m_passengerId;}
        virtual void SetFlightNumber(size_t _flightNumber){m_flightNumber = _flightNumber;}
        virtual size_t GetFlightNumber()const {return m_flightNumber;}
        virtual void SetPrise(size_t _prise) {m_prise = _prise;}
        virtual size_t GetPrise()const {return m_prise;}
        virtual void SetId(const string& _id) {m_ticketId = _id;}
        virtual const string& GetId()const {return m_ticketId;}
        virtual void SetSeat(const string& _seatNumber) {m_seatNumber= _seatNumber;}
        virtual const string& GetSeat(){return m_seatNumber;}
        virtual void Print()const;
        virtual const string GetStringDitails();
    private:
        Ticket_t(const Ticket_t& other);
        Ticket_t& operator=(const Ticket_t& other);

    private:
        size_t m_passengerId;
        size_t m_flightNumber;
        size_t m_prise;
        string m_seatNumber;
        string m_ticketId;

};

#endif // TICKET_T_H
