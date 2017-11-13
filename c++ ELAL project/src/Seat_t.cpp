#include <iostream>
#include "Seat_t.h"

Seat_t::Seat_t()
{
    m_status=FREE;
    m_number = 0;
}

Seat_t::~Seat_t()
{
    m_status=FREE;
    m_number = 0;
}

void Seat_t::Print() const
{
        std::cout<<"seat number - "<<m_number<< "Seat Status - " <<m_status <<std::endl;
}
