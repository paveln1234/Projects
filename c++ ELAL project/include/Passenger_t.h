#ifndef PASSENGER_T_H
#define PASSENGER_T_H
#include <string>
#include <vector>
class Customer_t;
class Ticket_t;
using namespace std;

class Passenger_t
{
    public:
        /** Default constructor */
        Passenger_t();
        /** Default destructor */
        virtual ~Passenger_t();

        /** set Passenger id
        * \param size_t - _passengerId
        */
        void SetPassengerId(size_t _passengerId){m_passengerId = _passengerId;}

        /** Get Passenger Id
        * \return size_t - passenger id
        */

        size_t GetPassengerId()const {return m_passengerId;}

        /** Add Ticket to Passenger
        * \param const string& _ticketId
        */
        virtual void AddTicket(const string& _ticketId);

        /** Remove Ticket to Passenger
        * \param const string& _ticketId
        * \return bool - true if success , fail if wrong ticket id given
        */
        virtual bool RemoveTicket(const string& _ticketId);

        /** Set Customer for passenger
        * \param const Customer_t* _customer - Costumer to set
        */
        virtual void SetCustomer(const Customer_t* _customer) {m_coustumer = _customer;}

        /** Get Customer from Passenger
        * \return const Customer_t* _customer - Costumer to set1
        */
        virtual const Customer_t* GetCustomer() const {return m_coustumer;}

        /** Get Passenger Ditals
        * \return const string whit passengers ditals
        */
        virtual const string GetPassengerDitals();

        /** Set Borded Passenger  after Passenger make Check In
        * \param bool _status - Passenger new status
        */
        void SetBorded(bool _status) {m_isBorded = _status;}

        /** Get Passenger borded status
        * \return  bool
        */
        const bool IsBorded()const {return m_isBorded;}

        /** Get Passenger tickets list
        * \return const vector<string> whit passengers tikets
        */
        virtual const vector<string> GetTicketList()const;


    private:
        Customer_t const* m_coustumer;
        vector<string> m_tickets;
        bool m_isBorded;
        size_t m_passengerId;
};

#endif // PASSENGER_T_H
