#include <sstream>
#include "BookingManager.h"
#include "Ticket_t.h"


BookingManager::BookingManager()
{
    //ctor
}

BookingManager::~BookingManager()
{
    //dtor
}

bool BookingManager::AddTicket(const Ticket_t* _newTicket)
{
    map<string,Ticket_t*>::iterator it= m_tikets.find(_newTicket->GetId());
    if(it == m_tikets.end())
    {
        m_tikets[_newTicket->GetId()] =const_cast<Ticket_t*>(_newTicket);
        return true;
    }

return false;
}

bool BookingManager::RemoveTicket(const string& _ticketNumber)
{
    map<string,Ticket_t*>::iterator it= m_tikets.find(_ticketNumber);
    if(it != m_tikets.end())
    {
        m_tikets.erase(it);
        return true;
    }

return false;
}

const Ticket_t* BookingManager::GetTicket(const string& _ticketNumber) const
{
    map<string,Ticket_t*>::const_iterator it= m_tikets.find(_ticketNumber);
    if(it != m_tikets.end())
    {
        return it->second;
    }

return NULL;
}

bool BookingManager::UpdateTicket(const Ticket_t* _Ticket)
{
    map<string,Ticket_t*>::iterator it= m_tikets.find(_Ticket->GetId());
    if(it != m_tikets.end())
    {
        m_tikets[_Ticket->GetId()] =const_cast<Ticket_t*>(_Ticket);
        return true;
    }

return false;
}
void BookingManager::PrintAllTickets()
{
    for(map<string, Ticket_t*>::iterator it =m_tikets.begin(); it != m_tikets.end();it++)
    {
        it->second->Print();
    }

}

void BookingManager::PrintAllTickets(size_t _flightNumber)
{
    for(map<string, Ticket_t*>::iterator it =m_tikets.begin(); it != m_tikets.end();it++)
    {
        if(_flightNumber == it->second->GetFlightNumber())
        {
            it->second->Print();
        }
    }
}
