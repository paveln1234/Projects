#ifndef PASSENGERMANAGER_T_H
#define PASSENGERMANAGER_T_H
#include <map>
#include <string>
#include <vector>

#include "Passenger_t.h"
using namespace std;

class Customer_t;
class PassengerManager_t
{
    public:
        /** Default constructor */
        PassengerManager_t();
        /** Default destructor */
        virtual ~PassengerManager_t();

        const bool AddPassenger(const Customer_t* _costumer);
        const bool RemovePassenger(size_t _passengerId);
        const bool UpdatePassenger(const Customer_t* _costumer, size_t _passengerId);
        const bool AddTicketToPassenger(size_t _passengerId, const string& _ticketId);
        const bool RemoveTicketFromPassenger(size_t _passengerId, const string& _ticketId);
        const bool BordedPassenger(size_t _passengerId, bool _status);
        const bool IsBorded(size_t _passengerId, bool _status)const;
        const Customer_t* GetCustomer(size_t _passengerId)const;
        const vector<string> GetPasengerTiket(size_t _passengerId)const;
        const string GetPassengerData(size_t _passengerId)const;
        void bookPassenger(size_t PsaasengerID, bool _Isboard);
        void PrintAllPasengers()const;



    private:
        PassengerManager_t(const PassengerManager_t& other);
        PassengerManager_t& operator=(const PassengerManager_t& other);

    private:
        map<size_t, Passenger_t*>  m_passengers;
        static size_t m_counter;
};

#endif // PASSENGERMANAGER_T_H
