#include <sstream>
#include "FlightManager.h"
#include "ResrveationSystem.h"
#include "FullFlightInterface.h"
#include "UserFlightInterface.h"
#include "Ticket_t.h"
#include "FlightManager.h"
#include "BookingManager.h"
#include "PassengerManager_t.h"
size_t ResrveationSystem:: m_counter=0;

ResrveationSystem::ResrveationSystem()
{

}

ResrveationSystem::~ResrveationSystem()
{
    //dtor
}
void ResrveationSystem::Create(FlightManager* _flightManager, PassengerManager_t* _passengerManager,BookingManager*_bookingManager)
{
    m_flightManager =const_cast<FlightManager*>( _flightManager);
    m_passengerManager = _passengerManager;
    m_bookingManager = _bookingManager;
}


bool ResrveationSystem::ReserveSeatOnFlight(size_t _passengerId,size_t _flightNumber)
{
    UserFlightInterface* flight = const_cast<FullFlightInterface*>(m_flightManager->GetFlight(_flightNumber));
    if(flight)
    {
        Ticket_t* newTicket = new Ticket_t;
        try
        {
            newTicket->SetSeat(flight->SetSeat());
        }catch(int i)
        {
            return false;
        }
        newTicket->SetFlightNumber(_flightNumber);
        newTicket->SetPassengerId(_passengerId);

        ostringstream str;
        str<<m_counter;
        string ticketId = "PK";
        ticketId +=  str.str();
        newTicket->SetId(ticketId);

        if(m_passengerManager->AddTicketToPassenger(_passengerId, ticketId))
        {
            m_bookingManager->AddTicket(newTicket);
            ++m_counter;
            return true;
        }
        else
        {
            delete newTicket;
            return false;
        }
    }
return false;
}

bool ResrveationSystem::ReserveSeatOnFlight(size_t _passengerId,size_t _flightNumber,ResrveationSystem::Tier _tier)
{
    UserFlightInterface* flight = const_cast<FullFlightInterface*>(m_flightManager->GetFlight(_flightNumber));
    if(flight)
    {
        Ticket_t* newTicket = new Ticket_t;
        try
        {
            (BISNESS == _tier)?newTicket->SetSeat(flight->SetSeat(UserFlightInterface::BISNESS))
                                                :newTicket->SetSeat(flight->SetSeat(UserFlightInterface::ECONNOME)) ;
        }catch(int i)
        {
            return false;
        }
        newTicket->SetFlightNumber(_flightNumber);
        newTicket->SetPassengerId(_passengerId);

        ostringstream str;
        str<<m_counter;
        string ticketId = "PK";
        ticketId +=  str.str();
        newTicket->SetId(ticketId);
        if(m_passengerManager->AddTicketToPassenger(_passengerId, ticketId))
        {
            m_bookingManager->AddTicket(newTicket);
            ++m_counter;
            return true;
        }
        else
        {
            delete newTicket;
            return false;
        }
    }

return false;
}


bool ResrveationSystem::ReserveSeatOnFlight(size_t _passengerId,size_t _flightNumber, const string& _seatNumber)
{
    UserFlightInterface* flight = const_cast<FullFlightInterface*>(m_flightManager->GetFlight(_flightNumber));
    if(flight && flight->SetSeat(_seatNumber))
    {
        Ticket_t* newTicket = new Ticket_t;
        newTicket->SetSeat(_seatNumber);
        newTicket->SetFlightNumber(_flightNumber);
        newTicket->SetPassengerId(_passengerId);
        ostringstream str;
        str<<m_counter;
        string ticketId = "PK";
        ticketId +=  str.str();
        newTicket->SetId(ticketId);
        if(m_passengerManager->AddTicketToPassenger(_passengerId, ticketId))
        {
            m_bookingManager->AddTicket(newTicket);
            ++m_counter;
            return true;
        }
        else
        {
            delete newTicket;
            return false;
        }
    }

return false;
}

const bool ResrveationSystem::FreeSeatFromFligh(size_t _flightNumber,const string& _ticketId)
{
    UserFlightInterface* flight = const_cast<FullFlightInterface*>(m_flightManager->GetFlight(_flightNumber));
    if(flight)
    {
       if(flight->RealesSeat(_ticketId))
       {
          return m_passengerManager->RemoveTicketFromPassenger(m_bookingManager->GetTicket(_ticketId)->GetPassengerId(),_ticketId);

       }
    }

return false;
}

