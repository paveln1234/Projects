#include<algorithm>
#include "SeatManager.h"
#include "Seat_t.h"
SeatManager::SeatManager()
{
    m_capacity = 0;
}

SeatManager::~SeatManager()
{
    m_capacity = 0;
    for(vector<Seat_t*>::iterator it = m_seats.begin();it != m_seats.end();it++)
    {
        delete *it;
    }
    m_seats.clear();
}

void SeatManager::Creaty()
{

}

void SeatManager::initialize(size_t _capacity)
{
    m_capacity = _capacity;
    size_t i = 0;
    for(;i<m_capacity;++i)
    {
        Seat_t* temp = new Seat_t;
        temp->SetNumber(i);
        m_seats.push_back(temp);
    }
}

SeatManager::SeatManagerStatus SeatManager::GetSeatStatus(size_t _seatNumber) const
{
        Seat_t* temp =FindSeat(_seatNumber);
        if(temp)
            return (Seat_t::FREE ==temp->GetStatus())?FREE_SEAT:TAKEN_SEAT;

return BADNUMBER;
}

bool SeatManager::SetSeat(size_t _seatNumber)
{
        Seat_t* temp =FindSeat(_seatNumber);
        if(temp)
        {
            if(Seat_t::FREE ==temp->GetStatus())
            {
                temp->SetStatus(Seat_t::TAKEN);
                return true;
            }
        }
return false;
}

bool SeatManager::SetSeat()
{
    for(vector<Seat_t*>::const_iterator it = m_seats.begin();it != m_seats.end();it++)
    {
        if((*it)->GetStatus() ==Seat_t::FREE)
        {
            (*it)->SetStatus(Seat_t::TAKEN);
            return true;
        }
    }
return false;
}

size_t SeatManager::GetFreeSeat() const
{
    size_t i = 0;
    for(vector<Seat_t*>::const_iterator it = m_seats.begin();it != m_seats.end();it++,++i)
    {
        if((*it)->GetStatus() ==Seat_t::FREE)
        {
            return i;
        }
    }

throw(-1);
}

vector<size_t> SeatManager::GetAllFreeSeats() const
{
    vector<size_t> temp;
    size_t i = 0;
    for(vector<Seat_t*>::const_iterator it = m_seats.begin();it != m_seats.end();it++,++i)
    {
        if((*it)->GetStatus() ==Seat_t::FREE)
        {
            temp.push_back((*it)->GetNumber());
        }
    }
return temp;
}

Seat_t* SeatManager::FindSeat(size_t _number) const
{
    Seat_t* temp =0;
    for(vector<Seat_t*>::const_iterator it = m_seats.begin();it != m_seats.end();it++)
    {
        if((*it)->GetNumber() == _number)
            temp = *it;
    }

return temp;
}
