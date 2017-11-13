#include <iostream>
#include <sstream>

#include "Ticket_t.h"

Ticket_t::Ticket_t()
{
    //ctor
}

Ticket_t::~Ticket_t()
{
    //dtor
}
void Ticket_t::Print() const
{
        cout << "Ticket Number : " << m_ticketId ;
        cout << "Flight Number : " << m_flightNumber << "\n";
        cout << "Passenger Id : " <<  m_passengerId;
        cout << "Seat number : " << m_seatNumber ;
        cout << "Ticket prise : " << m_prise <<endl;

}

const string Ticket_t::GetStringDitails()
{
    string FlightDitails;
    stringstream sTicket,sFlightnum,sPrise;
    sTicket << m_ticketId;
    sFlightnum << m_flightNumber;
    sPrise << m_prise;

    FlightDitails = "Ticket Number : " ;
    FlightDitails += sTicket.str();
    FlightDitails += " Flight Number : ";
    FlightDitails += sFlightnum.str();
    FlightDitails += " \n";
    FlightDitails += "Seat number : ";
    FlightDitails += m_seatNumber;
    FlightDitails += "Ticket prise : ";
    FlightDitails += sPrise.str();
    FlightDitails += " \n";

return FlightDitails;
}

