#include "Tier_t.h"
#include <string>
#include <sstream>
#include "Seat_t.h"
Tier_t::Tier_t()
{

}

Tier_t::~Tier_t()
{
    for(map<string,Seat_t*>::const_iterator it = m_seats.begin();it!=m_seats.end();it++)
    {
       delete it->second;
    }
    m_seats.clear();
}

void Tier_t::Create()
{
    m_capacity = 0;
    m_prise = 0;
    m_passangers =0;

}

void Tier_t::initialize(const string& _name,size_t _capacity, size_t _prise)
{
    m_capacity = _capacity;
    m_prise = _prise;
    m_name = _name;
    m_passangers = 0;
    size_t i=0;
    for(;i<m_capacity;++i)
    {
        Seat_t* temp = new Seat_t;
        temp->SetNumber(i);
        m_seats[GetSeatNumber(i)] = temp;
    }
}


Tier_t::SeatTeirStatus Tier_t::GetSeatStatus(const string& _seatNumber) const
{
    map<string,Seat_t*>::const_iterator pos = m_seats.find(_seatNumber);
    if(pos!=m_seats.end())
    {
        return((pos->second)->GetStatus()==Seat_t::TAKEN)?TAKEN_SEAT:FREE_SEAT;
    }

return BAD_NUMBER;
}

bool Tier_t::SetSeat(const string& _seatNumber)
{

    if(m_capacity == m_passangers)
        return false;

    Tier_t::SeatTeirStatus seatStatus= GetSeatStatus(_seatNumber);
    if(TAKEN_SEAT == seatStatus || BAD_NUMBER == seatStatus)
        return false;

    (m_seats[_seatNumber])->SetStatus(Seat_t::TAKEN);
    ++m_passangers;

return true;
}

const string Tier_t::SetSeat()
{
    if(m_capacity == m_passangers)
        throw (-1);
     string str= GetFreeSeat();
    m_seats[str]->SetStatus(Seat_t::TAKEN);
    ++m_passangers;
return str;
}


const string& Tier_t::GetFreeSeat() const
{
    for(map<string,Seat_t*>::const_iterator it = m_seats.begin();it!=m_seats.end();it++)
    {
        if(it->second->GetStatus()==Seat_t::FREE)
            return it->first;
    }
throw(-1);
}

vector<string> Tier_t::GetAllFreeSeats() const
{
    vector<string> temp;
    for(map<string,Seat_t*>::const_iterator it = m_seats.begin();it!=m_seats.end();it++)
    {
        if(it->second->GetStatus()==Seat_t::FREE)
            temp.push_back(it->first);
    }

return temp;
}

bool Tier_t::RealesSeat(const string& _seatNumber)
{
    Tier_t::SeatTeirStatus seatStatus= GetSeatStatus(_seatNumber);
    if(0 == m_passangers|| BAD_NUMBER == seatStatus)
        return false;
    m_seats[_seatNumber]->SetStatus(Seat_t::FREE);
    --m_passangers;
return true;
}

string Tier_t::GetSeatNumber(size_t _number)
{
    string str  = m_name.at(0)+ToString(_number);

return str;
}

string Tier_t::ToString(size_t _number)
{
    ostringstream str1;
    str1 <<_number;

return str1.str();
}
