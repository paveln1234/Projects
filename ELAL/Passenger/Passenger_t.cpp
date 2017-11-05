#include <sstream>
#include "Passenger_t.h"
#include "Customer_t.h"

Passenger_t::Passenger_t()
{
    m_isBorded = false;
}

Passenger_t::~Passenger_t()
{

}
void Passenger_t::AddTicket(const string& _ticketId)
{
    m_tickets.push_back(_ticketId);
}

bool Passenger_t::RemoveTicket(const string& _ticketId)
{
    for(vector<string>::iterator it = m_tickets.begin(); it != m_tickets.end();it++)
    {
        if(*it == _ticketId)
        {
            m_tickets.erase(it);
            return true;
        }
    }

return false;
}

const string Passenger_t::GetPassengerDitals()
{
    ostringstream str;
    string temp  = "Passenger Id - ";
    str<<m_passengerId;
    temp += str.str();
    temp += " Passenger boarding status : ";
    temp += (m_isBorded)?"Boarded":"Not Boarded";
    temp += "\n";
    temp += m_coustumer->GetCostumerDetails();
    temp += "\n";
    temp += "List Of Tickets : \n";
     for(vector<string>::iterator it = m_tickets.begin(); it != m_tickets.end();it++)
    {
        temp += *it;
        temp += " ,";

    }
return temp;
}

const vector<string> Passenger_t::GetTicketList() const
{
    return m_tickets;


}
