#ifndef RESRVEATIONSYSTEM_H
#define RESRVEATIONSYSTEM_H

#include <string>
#include "UserFlightInterface.h"
class FlightManager;
class Ticket_t;
class PassengerManager_t;
class BookingManager;

class ResrveationSystem
{
    public:
        enum Tier{ECONNOME,BISNESS};
        /** Default constructor */
        ResrveationSystem();

        /** Default destructor */
        virtual ~ResrveationSystem();

        void Create(FlightManager* _flightManager, PassengerManager_t* _passengerManager,BookingManager* _bookingManager);
        /**Reserve First Free Seat On Flight
        * \param size_t _passengerId - Passenger id
        * \param size_t _flightNumber - Flight to reserve seat on it
        * \return true if success , else if no free seat or proveded wrong passenger id or wrong flight
        */
        bool ReserveSeatOnFlight(size_t _passengerId ,size_t _flightNumber);

        /**Reserve First Free Seat On Flight by Teir
        * \param size_t _passengerId - Passenger id
        * \param size_t _flightNumber - Flight to reserve seat on it
        * \param Tier _tier - Tier on the flight;
        * \return true if success , else if no free seat or proveded wrong passenger id or wrong flight
        */
        bool ReserveSeatOnFlight(size_t _passengerId,size_t _flightNumber,Tier _tier );

        /**Reserve Seat On Flight by Seat Number
        * \param size_t _passengerId - Passenger id
        * \param size_t _flightNumber - Flight to reserve seat on it
        * \param const string& _flightNumber - _seatNumber;
        * \return true if success , else if no free seat or proveded wrong passenger id or wrong flight
        */
        bool ReserveSeatOnFlight(size_t _passengerId, size_t _flightNumber,const string& _seatNumber );

        /** the function free seat from flight and destroy the Ticker;
        * \param const string& _passengerId - Passenger id
        * \param const string& _ticketId - ticketid
        * \return bool - if success true,  fail cause NULL ticket.
        */
        const bool FreeSeatFromFligh(size_t _flightNumber, const string& _ticketId);


    private:
        ResrveationSystem(const ResrveationSystem& other);
        ResrveationSystem& operator=(const ResrveationSystem& other);

    private:
        FlightManager* m_flightManager;
        PassengerManager_t* m_passengerManager;
        BookingManager* m_bookingManager;
        static size_t m_counter;

};

#endif // RESRVEATIONSYSTEM_H
